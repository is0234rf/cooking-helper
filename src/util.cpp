//
// Created by dr-darao on 18/01/16.
//

#include <vector>
#include "util.h"

/**------------------------------------------------------------*
 * @fn          OpenCVのピクチャーインピクチャ
 * @brief       画像内に画像を貼り付ける（位置を座標で指定）
 * @par[in ]    srcImg  背景画像
 * @par[in ]    smallImg    前景画像
 * @par[in ]    p0  前景画像の左上座標
 * @par[in ]    p1  前景画像の右下座標
 *------------------------------------------------------------*/
void util::PinP_point(cv::Mat &srcImg, const cv::Mat &smallImg, const cv::Point2f p0)
{
  //３組の対応点を作成
  std::vector<cv::Point2f> src, dst;
  src.push_back(cv::Point2f(0, 0));
  src.push_back(cv::Point2f(smallImg.cols, 0));
  src.push_back(cv::Point2f(smallImg.cols, smallImg.rows));

  cv::Point2f p1(p0.x + smallImg.size().width, p0.y + smallImg.size().height);
  dst.push_back(p0);
  dst.push_back(cv::Point2f(p1.x, p0.y));
  dst.push_back(p1);

  //前景画像の変形行列
  cv::Mat mat = cv::getAffineTransform(src, dst);

  //アフィン変換の実行
  cv::warpAffine(smallImg, srcImg, mat, srcImg.size(), CV_INTER_LINEAR, cv::BORDER_TRANSPARENT);
}
