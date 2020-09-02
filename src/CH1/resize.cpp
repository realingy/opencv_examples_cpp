#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) {
  std::string path = argv[1];
  cv::Mat src = cv::imread(path);
  cv::Mat dst, dstImage2;

  imshow("src", src);

  cv::Mat dst1, dst2;
  cv::resize(src, dst1, cv::Size(src.cols / 2, src.rows / 2), 0, 0, 3);
  cv::resize(src, dst2, cv::Size(src.cols * 2, src.rows * 2), 0, 0, 3);

  imshow("resuce", dst1);
  imshow("magnify", dst2);

  cv::waitKey();
  return 0;
}
