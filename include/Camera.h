/*
 * @Descripttion: 
 * @Author: xujg
 * @version: 
 * @Date: 2025-06-05 10:04:40
 * @LastEditTime: 2025-06-05 10:06:18
 */
#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include "CheckBoard.h"

class Camera {
public:
    cv::Mat cameraMatrix;
    cv::Mat distCoeffs;
    double calib_pro_error;

    std::vector<cv::Mat> _rVecs;
    std::vector<cv::Mat> _tVecs;

    void calib(CheckBoard &checkboard);
    cv::Mat rectify(cv::Mat &img) const;
    cv::Mat imread(const std::string &filename) const;
    void show_params() const;
};

#endif // CAMERA_H
