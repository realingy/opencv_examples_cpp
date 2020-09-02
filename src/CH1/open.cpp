#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) {
  std::string name = argv[1];
  cv::VideoCapture capture;
  capture.open(name);
  if (!capture.isOpened()) {
    std::cout << "video can't opened!" << name << std::endl;
  }

  while (1) {
    cv::Mat frame;
    capture >> frame;
    if (frame.empty()) break;
    cv::imshow("video capture", frame);
    cv::waitKey(30);
  }

  return 0;
}
