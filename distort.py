'''
Descripttion: 
Author: xujg
version: 
Date: 2025-04-08 10:49:38
LastEditTime: 2025-04-08 10:54:40
'''
import numpy as np
import cv2

# MATLAB 参数
mapping_coeffs = [404.2262, -0.0015, 2.1637e-06, -7.2493e-09]
distortion_center = [643.3867, 375.3531]
stretch_matrix = np.array([[1.0018, -0.0502], [0.0491, 1]])
image_size = (1280, 720)  # 注意是(w, h)

# 焦距近似等于 mapping_coeffs[0]
f = mapping_coeffs[0]

# 构造内参矩阵 K
K = np.array([
    [f * stretch_matrix[0, 0], f * stretch_matrix[0, 1], distortion_center[0]],
    [f * stretch_matrix[1, 0], f * stretch_matrix[1, 1], distortion_center[1]],
    [0, 0, 1]
])

# 畸变参数 D，fisheye 模型中一般是前4项
D = np.array(mapping_coeffs[:4])

# 加载原图
img = cv2.imread('/home/xujg/fisheye_180_1280_720/img_0901.jpg')

# 去畸变
new_K = cv2.fisheye.estimateNewCameraMatrixForUndistortRectify(K, D, image_size, np.eye(3))
map1, map2 = cv2.fisheye.initUndistortRectifyMap(K, D, np.eye(3), new_K, image_size, cv2.CV_16SC2)
undistorted = cv2.remap(img, map1, map2, interpolation=cv2.INTER_LINEAR)

cv2.imwrite('undistorted.jpg', undistorted)
