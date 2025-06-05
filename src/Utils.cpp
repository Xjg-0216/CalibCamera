/*
 * @Descripttion: 
 * @Author: xujg
 * @version: 
 * @Date: 2025-04-07 16:00:11
 * @LastEditTime: 2025-06-05 10:36:25
 */
#include "Utils.h"
#include <boost/algorithm/string.hpp>
#include <cassert>

void Utils::split_string(const std::string &str, std::vector<std::string> &str_splits, const std::string &seg) {
    boost::split(str_splits, str, boost::is_any_of(seg));
}

void Utils::list_files(const std::string &folder, std::vector<cv::String> &files_list) {
    cv::glob(folder, files_list);
    assert(!files_list.empty());
}

void Utils::show(const cv::Mat &img, const std::string &win_name) {
    cv::imshow(win_name, img);
    cv::waitKey(0);
    cv::destroyWindow(win_name);
}

void Utils::imwrite(const cv::Mat &img, const std::string &name) {
    cv::imwrite(name, img);
}

