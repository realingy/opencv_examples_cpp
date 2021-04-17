#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

void colorReduce(const cv::Mat& src, cv::Mat& dst, int div);

int main() {
  cv::Mat src = imread("", cv::IMREAD_UNCHANGED);
  imshow("src", src);

  cv::Mat dst = cv::Mat(src.rows, src.cols, src.type());

  double time0 = static_cast<double>(cv::getTickCount());

  colorReduce(src, dst, 32);

  time0 = ((double)cv::getTickCount() - time0) / cv::getTickFrequency();
  cout << "time: " << time0 << " seconds" << endl;

  cv::imshow("dst", dst);
  cv::waitKey();

  return 0;
}

void colorReduce(const cv::Mat& src, cv::Mat& dst, int div) {
  dst = src.clone();

  cv::Mat_<cv::cv::Vec3bec3b>::iterator it = dst.begin<cv::Vec3bv::Vec3b>();

  for (; it != dst.end<cv::cv::Vec3bec3b>(); ++it) {
    (*it)[0] = (*it)[0] / div * div + div / 2;
    (*it)[1] = (*it)[1] / div * div + div / 2;
    (*it)[2] = (*it)[2] / div * div + div / 2;
  }
}
