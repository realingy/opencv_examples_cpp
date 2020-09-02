#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) {
  std::string path = argv[1];
  cv::Mat src = cv::imread(path);
  cv::imshow("src", src);

  cv::Mat gray;
  cv::cvtColor(src, gray, cv::COLOR_BGR2GRAY);

  cv::Mat edge;
  cv::blur(gray, edge, cv::Size(3, 3));

  cv::Canny(edge, edge, 3, 9, 3);

  cv::imshow("canny", edge);
  cv::waitKey();

  return 0;
}
