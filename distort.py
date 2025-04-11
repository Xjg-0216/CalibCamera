'''
Descripttion: 
Author: xujg
version: 
Date: 2025-04-07 16:31:58
LastEditTime: 2025-04-07 17:16:02
'''
import cv2
import numpy as np
import os

# 相机内参矩阵（fx, fy, cx, cy）
K = np.array([[403.4939400055919, -0.4751870166436157, 642.6791700360116],
              [0, 402.7851301439473, 374.1042017684945],
              [0, 0, 1]])

# 畸变系数 (k1, k2, k3, k4)
D = np.array([-0.1770296893835301, 0.04466932306016785, 
              -0.05498019166148976, 0.03027856913317858])

# 图像文件夹路径
image_folder = '/home/xujg/fisheye_180_1280_720'  # 替换为你的图像文件夹路径

output_folder = '/home/xujg/fisheye_180_1280_720_res1'

os.makedirs(output_folder, exist_ok=True)

# 获取文件夹中所有图像文件
image_files = [f for f in os.listdir(image_folder) if f.endswith(('.jpg', '.png', '.jpeg'))]

# 遍历文件夹中的所有图像文件
for image_file in image_files:
    # 构造图像的完整路径
    image_path = os.path.join(image_folder, image_file)
    
    # 读取图像
    image = cv2.imread(image_path)

    # 获取图像大小
    h, w = image.shape[:2]

    # 获取新的相机内参矩阵（可以使用原始内参矩阵）
    new_K = K.copy()

    # 使用fisheye模块的undistortImage进行去畸变
    undistorted_image = cv2.fisheye.undistortImage(image, K, D, None, new_K)

    # map1, map2 = cv2.fisheye.initUndistortRectifyMap(K, D, None, new_K, image.shape[:2], cv2.CV_16SC2)
    # undistorted_image = cv2.remap(image, map1, map2, interpolation=cv2.INTER_LINEAR)

    # 拼接畸变图像和去畸变图像
    concatenated_image = cv2.hconcat([image, undistorted_image])
    # 获取两张图像的尺寸
    # height1, width1 = image.shape[:2]
    # height2, width2 = undistorted_image.shape[:2]

    # # 选择合适的画布大小，宽度是两图像宽度之和，高度是两者中的最大值
    # new_width = width1 + width2
    # new_height = max(height1, height2)

    # # 创建一个空白的画布，填充为黑色（可以根据需要修改背景颜色）
    # canvas = np.zeros((new_height, new_width, 3), dtype=np.uint8)

    # # 将原始图像和去畸变图像放置到画布上
    # canvas[:height1, :width1] = image  # 放置原始图像
    # canvas[:height2, width1:] = undistorted_image  # 放置去畸变图像

    # 保存拼接后的图像
    output_path = os.path.join(output_folder, f'concatenated_{image_file}')
    cv2.imwrite(output_path, concatenated_image)

# 等待键盘输入，关闭所有显示窗口
# cv2.waitKey(0)
# cv2.destroyAllWindows()
