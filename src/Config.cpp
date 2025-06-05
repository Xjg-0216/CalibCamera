/*
 * @Descripttion: 
 * @Author: xujg
 * @version: 
 * @Date: 2025-06-05 11:25:36
 * @LastEditTime: 2025-06-05 11:40:57
 */
#include "Config.h"

Config parseConfig(const std::string& filename) {
    Config config;

    try {
        // 加载 YAML 文件
        YAML::Node node = YAML::LoadFile(filename);

        // 提取配置信息
        if (node["imgs_path"]) {
            config.imgs_path = node["imgs_path"].as<std::string>();
        }

        if (node["points_per_col"]) {
            config.points_per_col = node["points_per_col"].as<int>();
        }

        if (node["points_per_row"]) {
            config.points_per_row = node["points_per_row"].as<int>();
        }


        if (node["square_size"]) {
            config.square_size = node["square_size"].as<float>();
        }
        
        if (node["detect_corners_imgs"]){
            config.detect_corners_imgs = node["detect_corners_imgs"].as<bool>();
        }


    } catch (const YAML::Exception& e) {
        std::cerr << "YAML Exception: " << e.what() << std::endl;
    }

    return config;
}