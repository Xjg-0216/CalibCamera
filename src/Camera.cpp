/*
 * @Descripttion: 
 * @Author: xujg
 * @version: 
 * @Date: 2025-05-16 16:57:08
 * @LastEditTime: 2025-06-05 13:25:27
 */
#include "Camera.h"
using namespace std;

void Camera::calib(CheckBoard &checkboard){
    cout << "\n开始标定：..." << endl;
    clock_t start = clock();
    calib_pro_error = cv::calibrateCamera(
                checkboard.corners_world_all,  // 世界坐标系点，vector<vector<cv::Point3f> >
                checkboard.corners_pixel_all,  // 图像坐标系点(对应的)，vector<vector<cv::Point2f> >
                checkboard.calib_images_size,  // 标定图像尺寸大小，cv::Size
                cameraMatrix,      // 相机内参矩阵
                distCoeffs,           // 畸变矩阵
                _rVecs,                  // 旋转向量
                _tVecs                   // 平移矩阵
    );
    clock_t end = clock();
    cout << "耗时:\t" << double(end - start) / CLOCKS_PER_SEC << " S" << endl;
    cout << "标定结束!" << endl;
}

cv::Mat Camera::rectify(cv::Mat &img) const {
    cv::Mat img_rectify;
    cv::undistort(img, img_rectify, cameraMatrix, distCoeffs);
    return img_rectify;
}

cv::Mat Camera::imread(const string &filename) const {
    cv::Mat img = cv::imread(filename);
    return rectify(img);
}

void Camera::show_params() const {
    cout << "-----------------------" << endl;
    cout << "重投影误差:" << calib_pro_error << endl;
    cout << "-----------------------" << endl;
    cout << "相机内参:\nM = [[fx, γ, u0], [0, fy, v0], [0, 0, 1]]" << endl;
    cout << "=" << cameraMatrix << endl;
    cout << "-----------------------" << endl;
    cout << "畸变系数:\n" << "k1, k2, p1, p2, k3" << endl;
    cout << "=" << distCoeffs << endl;
}
