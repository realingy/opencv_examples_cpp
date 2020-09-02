#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc, char *argv[]) {
  std::string path = argv[1];
  cv::Mat src = cv::imread(path);
  cv::imshow("src", src);

  cv::Mat dst;
  cv::GaussianBlur(src, dst, cv::Size(7, 7), 1000);

  cv::imshow("gaussblur", dst);
  cv::waitKey(0);

  return 0;
}
