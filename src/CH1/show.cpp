#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) {
  std::string path = argv[1];
  cv::Mat img = cv::imread(path);
  if (nullptr == img.data) {
    std::cout << "open image error!";
  }
  cv::imshow("src", img);
  cv::waitKey(0);
}
