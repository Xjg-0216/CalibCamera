/*
 * @Descripttion: 
 * @Author: xujg
 * @version: 
 * @Date: 2025-05-16 16:57:08
 * @LastEditTime: 2025-06-05 11:20:46
 */
#include "CheckBoard.h"
#include "Utils.h"

using namespace std;

CheckBoard::CheckBoard(int points_per_col, int points_per_row, float square_size) {
    assert(points_per_col > 0);
    assert(points_per_row > 0);

    this->points_per_col = points_per_col;
    this->points_per_row = points_per_row;
    this->patten_size = cv::Size(this->points_per_row, this->points_per_col);

    if (square_size != -1) {
        assert(square_size > 0);
        this->square_size = square_size;
    }
}

void CheckBoard::detect_corners(const string &calib_folder, bool show) {
    calib_images.clear();
    corners_world_all.clear();
    corners_pixel_all.clear();

    Utils::list_files(calib_folder, calib_images);
    calib_images_size = cv::imread(calib_images[0]).size();

    cout << "开始检测角点!" << endl;
    cout << "-----------------------" << endl;

    for (int idx = 0; idx < calib_images.size(); ++idx) {
        _add_corners_world();
    }

    cv::TermCriteria criteria = cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 30, 0.1);
    vector<int> idxs_delete;

    for (int idx = 0; idx < calib_images.size(); ++idx) {
        string filename = calib_images[idx];
        cv::Mat img = cv::imread(filename);
        bool found = _add_corners_pixel(img, criteria);

        if (!found) {
            idxs_delete.emplace_back(idx);
            cout << "失败:\t" << filename << endl;
            continue;
        } else {
            cout << "成功:\t" << filename << endl;
        }
        cv::drawChessboardCorners(img, patten_size, corners_pixel_all.back(), found);
        vector<string> str_splits;
        Utils::split_string(calib_images[idx], str_splits, "/");
        if (show) {
            Utils::show(img, str_splits.back());
        }
        Utils::imwrite(img, str_splits.back());
    }

    // 删除失败项
    for (int i = idxs_delete.size() - 1; i >= 0; --i) {
        int idx = idxs_delete[i];
        calib_images.erase(calib_images.begin() + idx);
        corners_world_all.erase(corners_world_all.begin() + idx);
    }
}

void CheckBoard::show_params() {
    cout << "标定板尺寸(points_per_row, points_per_col):\t" << patten_size << endl;
    cout << "棋盘格大小:\t" << square_size << endl;
}

void CheckBoard::_add_corners_world() {
    if (corners_world_all.empty()) {
        vector<cv::Point3f> cornersWorld;
        for (int row = 0; row < points_per_col; ++row) {
            for (int col = 0; col < points_per_row; ++col) {
                cornersWorld.emplace_back(float(col) * square_size, float(row) * square_size, 0.f);
            }
        }
        corners_world_all.emplace_back(cornersWorld);
    } else {
        corners_world_all.emplace_back(corners_world_all[0]);
    }
}

bool CheckBoard::_add_corners_pixel(const cv::Mat &img, cv::TermCriteria &criteria) {
    assert(calib_images_size == img.size());
    vector<cv::Point2f> corners_pixel;
    bool found = cv::findChessboardCorners(img, patten_size, corners_pixel);
    if (found) {
        cv::Mat img_gray;
        cv::cvtColor(img, img_gray, cv::COLOR_BGR2GRAY);
        cv::cornerSubPix(img_gray, corners_pixel, cv::Size(5, 5), cv::Size(-1, -1), criteria);
        corners_pixel_all.emplace_back(corners_pixel);
    }
    return found;
}
