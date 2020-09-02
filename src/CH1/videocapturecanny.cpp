#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) {
  cv::VideoCapture capture(0);
  cv::Mat edge;

  while (1) {
    cv::Mat frame;
    capture >> frame;
    cv::flip(frame, frame, 1);
    cv::cvtColor(frame, edge, cv::COLOR_BGR2GRAY);
    cv::blur(edge, edge, cv::Size(7, 7));

    Canny(edge, edge, 3, 9, 3);
    cv::imshow("canny video capture", edge);
    cv::waitKey(30);
  }

  return 0;
}
