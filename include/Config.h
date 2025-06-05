/*
 * @Descripttion: 
 * @Author: xujg
 * @version: 
 * @Date: 2025-06-05 11:21:04
 * @LastEditTime: 2025-06-05 11:24:47
 */
#ifndef CONFIG_H
#define CONFIG_H
#include<cstring>
#include <iostream>
#include <yaml-cpp/yaml.h>

struct Config {
    std::string imgs_path;
    bool detect_corners_imgs;
    int points_per_col; // 列的内角点数量
    int points_per_row; // 行的内焦点数量
    float square_size; // 实际大小(单位毫米)

};


Config parseConfig(const std::string& filename);

#endif