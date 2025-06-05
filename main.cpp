/*
 * @Descripttion: 
 * @Author: xujg
 * @version: 
 * @Date: 2025-04-07 16:00:11
 * @LastEditTime: 2025-06-05 11:34:22
 */
#include "CheckBoard.h"
#include "Camera.h"
#include "Utils.h"
#include <opencv2/opencv.hpp>
#include "Config.h"

using namespace std;

void test(CheckBoard &checkboard,
          Camera &camera,
          const string &file){
    cv::Mat img_original = cv::imread(file);
    cv::Mat img_rectify_1 = camera.rectify(img_original);
    cv::Mat img_rectify_2= camera.imread(file);

    Utils::show(img_original, "original");
    Utils::show(img_rectify_1, "img_rectify_1");
    Utils::show(img_rectify_2, "img_rectify_2");

    Utils::show(img_rectify_1 - img_original, "img_rectify_1 - img_original");
    Utils::show(img_rectify_2 - img_original, "img_rectify_2 - img_original");
    Utils::show(img_rectify_2 - img_rectify_1, "img_rectify_2 - img_rectify_1");
}


int main(int argc, char **argv) {

    std::string filename = argv[1];
    Config config = parseConfig(filename);

    const string &model_path = config.imgs_path;

    CheckBoard checkboard(config.points_per_col, config.points_per_row, config.square_size);
    checkboard.detect_corners(model_path, config.detect_corners_imgs);
    checkboard.show_params();

    Camera camera;
    camera.calib(checkboard);
    camera.show_params();

    // test(checkboard, camera, "/home/flyman/Desktop/CalibCamera/data/left0000.jpg");
    return 0;
}