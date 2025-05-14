import cv2
import numpy as np

# 读取图像
img = cv2.imread("/home/xujg/code/CalibCamera/frame_4008.jpg")  # 替换为你的图像路径
if img is None:
    raise FileNotFoundError("请检查图像路径是否正确")

h, w = img.shape[:2]

# 初始内参
K = np.array([[403.4939400055919, 0, 642.6791700360116],
              [0, 402.7851301439473, 374.1042017684945],
              [0, 0, 1]], dtype=np.float32)

K_new = np.array([[403.4939400055919 * 0.6, 0, 642.6791700360116],
              [0, 402.7851301439473 * 0.6, 374.1042017684945],
              [0, 0, 1]], dtype=np.float32)

# 初始畸变系数
D = np.zeros((4, 1), dtype=np.float32)

# 参数范围（用于滑动条）
k_min, k_max, step = -0.5, 0.5, 0.01
trackbar_range = int((k_max - k_min) / step)

# 创建窗口
cv2.namedWindow("Undistorted", cv2.WINDOW_NORMAL)

# 创建滑动条
def create_param_trackbars():
    for i, k in enumerate(["k1", "k2", "k3", "k4"]):
        cv2.createTrackbar(k, "Undistorted", int((0 - k_min) / step), trackbar_range, lambda x: None)

create_param_trackbars()

def get_trackbar_val(name):
    raw = cv2.getTrackbarPos(name, "Undistorted")
    return k_min + raw * step

while True:
    # 更新畸变系数
    for i, k in enumerate(["k1", "k2", "k3", "k4"]):
        D[i, 0] = get_trackbar_val(k)

    # 生成映射
    map1, map2 = cv2.fisheye.initUndistortRectifyMap(K, D, np.eye(3), K_new, (w, h), cv2.CV_16SC2)
    undistorted = cv2.remap(img, map1, map2, interpolation=cv2.INTER_LINEAR)

    # 显示参数文本
    param_text = f"k1={D[0,0]:.3f}  k2={D[1,0]:.3f}  k3={D[2,0]:.3f}  k4={D[3,0]:.3f}"
    cv2.putText(undistorted, param_text, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 0), 2)

    # 显示图像
    cv2.imshow("Undistorted", undistorted)

    key = cv2.waitKey(30)
    if key == 27:  # ESC键退出
        break

cv2.destroyAllWindows()
