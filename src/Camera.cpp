/*
 * @Descripttion: 
 * @Author: xujg
 * @version: 
 * @Date: 2025-05-16 16:57:08
 * @LastEditTime: 2025-06-05 10:05:41
 */
#include "Camera.h"
using namespace std;

void Camera::calib(CheckBoard &checkboard){
    cout << "\n开始标定：..." << endl;
    clock_t start = clock();
    calib_pro_error = cv::fisheye::calibrate(
        checkboard.corners_world_all,
        checkboard.corners_pixel_all,
        checkboard.calib_images_size,
        cameraMatrix,
        distCoeffs,
        _rVecs,
        _tVecs,
        cv::fisheye::CALIB_RECOMPUTE_EXTRINSIC + cv::CALIB_USE_LU,
        cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 20, 1e-6)
    );
    clock_t end = clock();
    cout << "耗时:\t" << double(end - start) / CLOCKS_PER_SEC << " S" << endl;
    cout << "标定结束!" << endl;
}

cv::Mat Camera::rectify(cv::Mat &img) const {
    cv::Mat img_rectify;
    cv::fisheye::undistortImage(img, img_rectify, cameraMatrix, distCoeffs);
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
    cout << "畸变系数:\nk1, k2, k3, k4" << endl;
    cout << "=" << distCoeffs << endl;
}
