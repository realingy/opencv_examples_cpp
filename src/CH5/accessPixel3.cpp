#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

void colorReduce(const cv::Mat& inputImage, cv::Mat& dst, int div);

int main() {
  cv::Mat src = cv::imread("", cv::IMREAD_UNCHANGED);
  imshow("src", src);

  cv::Mat dst;
  dst.create(src.rows, src.cols, src.type());

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
  int rowNumber = dst.rows;
  int colNumber = dst.cols;

  for (int i = 0; i < rowNumber; i++) {
    for (int j = 0; j < colNumber; j++) {
      dst.at<cv::cv::Vec3bec3b>(i, j)[0] =
          dst.at<cv::cv::Vec3bec3b>(i, j)[0] / div * div + div / 2;
      dst.at<cv::cv::Vec3bec3b>(i, j)[1] =
          dst.at<cv::cv::Vec3bec3b>(i, j)[1] / div * div + div / 2;
      dst.at<cv::cv::Vec3bec3b>(i, j)[2] =
          dst.at<cv::cv::Vec3bec3b>(i, j)[2] / div * div + div / 2;
    }
  }
}
