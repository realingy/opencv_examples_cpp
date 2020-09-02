#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) {
  cv::VideoCapture capture(0);

  while (1) {
    cv::Mat frame;     //定义frame存储视屏帧
    capture >> frame;  //读取当前帧
    cv::flip(frame, frame, 1);
    cv::imshow("video capture", frame);  //显示当前帧
    cv::waitKey(30);                     //延时
  }

  return 0;
}
