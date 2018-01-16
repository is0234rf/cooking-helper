#include <stdio.h>
#include <array>
#include <vector>
#include <iostream>
#include <opencv/cv.h>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include "util.h"

#define IMAGE_NUM  (1)         /* 画像数 */
#define PAT_ROW    (10)          /* パターンの行数 */
#define PAT_COL    (7)         /* パターンの列数 */
#define CHESS_SIZE (0.02423)       /* パターン1マスの1辺サイズ[m] */

void run(cv::Mat src);

int main (int argc, char *argv[])
{
  cv::VideoCapture cap(0);
  cv::namedWindow("window", CV_WINDOW_NORMAL);
  cv::setWindowProperty("window", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
  while(1) {
    cv::Mat frame;
    cap >> frame;
    run(frame);
    cv::imshow("window", frame);

    int keycode = cv::waitKey(1);
    if (keycode == 113) break;
  }

  cv::destroyAllWindows();
  return 0;
}

void run(cv::Mat src) {
  std::vector<cv::Mat> src_img{ src };
  // (3)チェスボード（キャリブレーションパターン）のコーナー検出
  int found_count = 0;
  cv::Size pattern_size = cv::Size(PAT_COL, PAT_ROW);
  std::vector<std::vector<cv::Point2f>> image_points;
  std::vector<std::vector<cv::Point3f>> object_points;

  for (auto &img : src_img) {
    std::vector<cv::Point2f> corners;
    bool found = cv::findChessboardCorners(img, pattern_size, corners);

    if (found) {
      found_count++;
    } else {
      return;
    }

    cv::drawChessboardCorners(src_img[0], pattern_size, corners, found);
    std::vector<cv::Point3f> obj;
    for (int i = 0; i < PAT_ROW; i++) {
      for (int j = 0; j < PAT_COL; j++) {
        obj.push_back(cv::Point3f((double) j * CHESS_SIZE, (double) i * CHESS_SIZE, 0));
      }
    }

    object_points.push_back(obj);
    image_points.push_back(corners);
  }

  if (found_count != IMAGE_NUM) {
    return;
  }

  // (5)内部パラメータ，歪み係数の推定
  cv::Mat camera_matrix;
  cv::Mat dist_coeffs;
  std::vector<cv::Mat> rvecs, tvecs;
  int flag = 0;
  flag |= CV_CALIB_FIX_K4;
  flag |= CV_CALIB_FIX_K5;

  cv::calibrateCamera(object_points, image_points, src_img[0].size(), camera_matrix, dist_coeffs, rvecs, tvecs, flag);

  std::vector<cv::Point2f> projected_points;
  std::vector<cv::Scalar> colors{
    cv::Scalar(200,0,0),
    cv::Scalar(0,200,0),
    cv::Scalar(0,0,200)
  };

  cv::projectPoints(object_points[0], rvecs.front(), tvecs.front(), camera_matrix, dist_coeffs, projected_points);
  for (int i = 0; i < object_points[0].size(); i++) {
    cv::circle(src_img[0], projected_points[i], 5, colors[i % 3], -1, CV_AA);
  }
  cv::putText(src_img[0], "OpenCV", projected_points[0], cv::FONT_HERSHEY_SCRIPT_COMPLEX, 1.2, cv::Scalar(0,0,200), 2, CV_AA);

}
