#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) {
  cv::Mat dota = cv::imread(argv[1]);
  cv::Mat logo = cv::imread(argv[2]);

  cv::Mat roi = dota(cv::Rect(800, 350, logo.cols, logo.rows));

  cv::addWeighted(roi, 0.5, logo, 0.3, 0., roi);

  cv::imshow("ROI", dota);

  cv::waitKey();
}
