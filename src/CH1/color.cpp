#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) {
  std::string path = argv[1];
  cv::Mat src = cv::imread(path);
  imshow("src", src);

  cv::Mat dst;
  cv::cvtColor(src, dst, 10);

  cv::imshow("dst", dst);
  cv::waitKey();

  return 0;
}
