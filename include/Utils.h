/*
 * @Descripttion: 
 * @Author: xujg
 * @version: 
 * @Date: 2025-06-05 10:17:24
 * @LastEditTime: 2025-06-05 10:39:55
 */
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

class Utils {
public:
    static void split_string(const std::string &str, std::vector<std::string> &str_splits, const std::string &seg);
    static void list_files(const std::string &folder, std::vector<cv::String> &files_list);
    static void show(const cv::Mat &img, const std::string &win_name);
    static void imwrite(const cv::Mat &img, const std::string &name);
};

#endif // UTILS_H
