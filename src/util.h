//
// Created by dr-darao on 18/01/16.
//

#ifndef COOKING_HELPER_UTIL_H_H
#define COOKING_HELPER_UTIL_H_H

#include <opencv/cv.hpp>


namespace util {
  /**------------------------------------------------------------*
   * @fn          OpenCVのピクチャーインピクチャ
   * @brief       画像内に画像を貼り付ける（位置を座標で指定）
   * @par[in ]    srcImg  背景画像
   * @par[in ]    smallImg    前景画像
   * @par[in ]    p0  前景画像の左上座標
   * @par[in ]    p1  前景画像の右下座標
   *------------------------------------------------------------*/
  void PinP_point(cv::Mat &srcImg, const cv::Mat &smallImg, const cv::Point2f p0);
};
#endif //COOKING_HELPER_UTIL_H_H
