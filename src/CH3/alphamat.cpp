#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <vector>


using namespace std;

void createAlphaMat(cv::Mat &src) {
  for (int i = 0; i < src.rows; ++i) {
    for (int j = 0; j < src.cols; ++j) {
      cv::Vec4b &rgba = src.at<cv::Vec4b>(i, j);
      rgba[0] = UCHAR_MAX;
      rgba[1] = cv::saturate_cast<uchar>((float(src.cols - j)) /
                                         ((float)src.cols) * UCHAR_MAX);
      rgba[2] = cv::saturate_cast<uchar>((float(src.rows - i)) /
                                         ((float)src.rows) * UCHAR_MAX);
      rgba[3] = cv::saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
    }
  }
}

int main(int argc, char *argv[]) {
  // cv::Mat src(cv::Size(480, 640), cv::CV_8UC4);
  cv::Mat src(480, 640, CV_8UC4);
  createAlphaMat(src);

  cout << CV_VERSION;

  std::vector<int> compression_params;
  //  OpenCV2
  //  compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
  //  OpenCV3
  compression_params.push_back(cv::IMWRITE_PNG_COMPRESSION);
  compression_params.push_back(9);

  try {
    cv::imwrite("透明Alpha值图.png", src, compression_params);
    cv::imshow("生成的png图", src);
    fprintf(stdout,
            "PNG图片文件的alpha数据保存完毕~"
            "\n可以在工程目录下查看由imwrite函数生成的图片\n");
    cv::waitKey(0);
  } catch (runtime_error &ex) {
    fprintf(stderr, "图像转换成PNG格式发生错误：%s\n", ex.what());
    return 1;
  }

  return 0;
}
