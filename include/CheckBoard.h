/*
 * @Descripttion: 
 * @Author: xujg
 * @version: 
 * @Date: 2025-06-05 10:09:58
 * @LastEditTime: 2025-06-05 11:18:05
 */
#ifndef CHECKBOARD_H
#define CHECKBOARD_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

class CheckBoard {
public:
    int points_per_col;
    int points_per_row;
    cv::Size patten_size;
    float square_size;

    std::vector<cv::String> calib_images;
    cv::Size calib_images_size;

    std::vector<std::vector<cv::Point3f>> corners_world_all;
    std::vector<std::vector<cv::Point2f>> corners_pixel_all;

public:
    CheckBoard(int points_per_col, int points_per_row, float square_size = -1);

    void detect_corners(const std::string &calib_folder, bool show = false);
    void show_params();

private:
    void _add_corners_world();
    bool _add_corners_pixel(const cv::Mat &img, cv::TermCriteria &criteria);
};

#endif // CHECKBOARD_H
