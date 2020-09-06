#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

#define WINDOW_NAME "【滑动条的创建&线性混合示例】"

const int g_nMaxAlphaValue = 100;  // Alpha的最大值
int g_nAlphaValueSlider;           //滑动条对应的变量
double g_dAlphaValue;
double g_dBetaValue;

Mat g_src1;
Mat g_src2;
Mat g_dst;

void on_Trackbar(int, void*) {
  g_dAlphaValue = (double)g_nAlphaValueSlider / g_nMaxAlphaValue;
  g_dBetaValue = (1.0 - g_dAlphaValue);

  addWeighted(g_src1, g_dAlphaValue, g_src2, g_dBetaValue, 0.0, g_dst);

  imshow(WINDOW_NAME, g_dst);
}

int main(int argc, char** argv) {
  std::string name1 = "1.jpg";
  std::string name2 = "2.jpg";
  g_src1 = imread(name1);
  g_src2 = imread(name2);
  if (!g_src1.data || !g_src2.data) {
    std::cout << "read image error!\n";
    return -1;
  }

  g_nAlphaValueSlider = 70;

  cv::namedWindow(WINDOW_NAME, 1);

  char TrackbarName[50];
  sprintf(TrackbarName, "ֵ透明值 %d", g_nMaxAlphaValue);

  cv::createTrackbar(TrackbarName, WINDOW_NAME, &g_nAlphaValueSlider,
                     g_nMaxAlphaValue, on_Trackbar);

  on_Trackbar(g_nAlphaValueSlider, 0);

  cv::waitKey(0);

  return 0;
}
