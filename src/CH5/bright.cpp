//说明：图像对比度、亮度值调整

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "path.h"


using namespace std;
using namespace cv;

void ContrastAndBright(int, void *);
int g_nBrightValue;    //亮度值
int g_nContrastValue;  //对比度
Mat g_srcImage, g_dstImage;

int main() {
  string src = MediaPath + "3.jpg";
  g_srcImage = imread(src);
  if (!g_srcImage.data) return -1;

  g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

  g_nContrastValue = 80;
  g_nBrightValue = 80;

  namedWindow("effect");
  imshow("effect", g_srcImage);

  createTrackbar("Contras", "effect", &g_nContrastValue, 300, ContrastAndBright,
                 &g_srcImage);
  createTrackbar("Bright", "effect", &g_nBrightValue, 200, ContrastAndBright,
                 &g_srcImage);

  ContrastAndBright(g_nContrastValue, 0);
  ContrastAndBright(g_nBrightValue, 0);

  while (char(waitKey(1)) != 'q') {
  }
  return 0;
}

//改变图像对比度和亮度值的回调函数
void ContrastAndBright(int, void *) {
  for (int y = 0; y < g_srcImage.rows; y++) {
    for (int x = 0; x < g_srcImage.cols; x++) {
      for (int c = 0; c < 3; c++) {
        g_dstImage.at<cv::Vec3b>(y, x)[c] = saturate_cast<uchar>(
            (g_nContrastValue * 0.01) * (g_srcImage.at<cv::Vec3b>(y, x)[c]) +
            g_nBrightValue);
      }
    }
  }

  imshow("effect", g_dstImage);
}
