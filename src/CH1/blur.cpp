#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

int main(int argc, char *argv[]) {
  std::string path = argv[1];
  cv::Mat src = cv::imread(path);
  if (nullptr == src.data) {
    cout << "open image failed!\n";
  }
  cv::imshow("src", src);

  cv::Mat dst;
  cv::blur(src, dst, cv::Size(8, 8));
  cv::imshow("blur", dst);
  cv::waitKey(0);

  return 0;
}
