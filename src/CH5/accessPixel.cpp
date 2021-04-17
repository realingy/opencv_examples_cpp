#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

void colorReduce(const cv::Mat& src, cv::Mat& dst, int div);

int main() {
  cv::Mat src = imread("", cv::IMREAD_UNCHANGED);
  imshow("src", src);

  cv::Mat dst;
  dst.create(src.rows, src.cols, src.type());

  double time0 = static_cast<double>(cv::getTickCount());

  colorReduce(src, dst, 10);

  time0 = ((double)cv::getTickCount() - time0) / cv::getTickFrequency();
  cout << "interval: " << time0 << "s" << endl;

  imshow("dst", dst);
  cv::waitKey();
}

void colorReduce(const cv::Mat& src, cv::Mat& dst, int div) {
  dst = src.clone();
  int row = dst.rows;
  int col = dst.cols * dst.channels();

  for (int i = 0; i < row; i++) {
    uchar* data = dst.ptr<uchar>(i);
    for (int j = 0; j < col; j++) {
      data[j] = data[j] / div * div + div / 2;
    }
  }
}
