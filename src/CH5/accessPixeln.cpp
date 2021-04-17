#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

using namespace std;

#define NTESTS 14
#define NITERATIONS 20

void colorReduce0(cv::Mat &image, int div = 64) {
  int rows = image.rows;
  int pixels = image.cols * image.channels();

  for (int j = 0; j < rows; j++) {
    uchar *data = image.ptr<uchar>(j);
    for (int i = 0; i < pixels; i++) {
      data[i] = data[i] / div * div + div / 2;
    }
  }
}

void colorReduce1(cv::Mat &image, int div = 64) {
  int rows = image.rows;
  int pixels = image.cols * image.channels();

  for (int j = 0; j < rows; j++) {
    uchar *data = image.ptr<uchar>(j);
    for (int i = 0; i < pixels; i++) {
      *data++ = *data / div * div + div / 2;
    }
  }
}

void colorReduce2(cv::Mat &image, int div = 64) {
  int rows = image.rows;
  int pixels = image.cols * image.channels();

  for (int j = 0; j < rows; j++) {
    uchar *data = image.ptr<uchar>(j);
    for (int i = 0; i < pixels; i++) {
      int v = *data;
      *data++ = v - v % div + div / 2;
    }
  }
}

void colorReduce3(cv::Mat &image, int div = 64) {
  int rows = image.rows;
  int pixels = image.cols * image.channels();
  int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));

  uchar mask = 0xFF << n;

  for (int j = 0; j < rows; j++) {
    uchar *data = image.ptr<uchar>(j);
    for (int i = 0; i < pixels; i++) {
      *data++ = *data & mask + div / 2;
    }
  }
}

void colorReduce4(cv::Mat &image, int div = 64) {
  int nl = image.rows;
  int nc = image.cols * image.channels();
  int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
  int step = image.step;

  uchar mask = 0xFF << n;  // e.g. div=16, mask= 0xF0

  uchar *data = image.data;

  for (int j = 0; j < nl; j++) {
    for (int i = 0; i < nc; i++) {
      *(data + i) = *data & mask + div / 2;
    }
    data += step;
  }
}

void colorReduce5(cv::Mat &image, int div = 64) {
  int nl = image.rows;
  int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));

  uchar mask = 0xFF << n;  // e.g. =16, mask= 0xF0

  for (int j = 0; j < nl; j++) {
    uchar *data = image.ptr<uchar>(j);

    for (int i = 0; i < image.cols * image.channels(); i++) {
      *data++ = *data & mask + div / 2;
    }
  }
}

void colorReduce6(cv::Mat &image, int div = 64) {
  int nl = image.rows;
  int nc = image.cols * image.channels();

  if (image.isContinuous()) {
    nc = nc * nl;
    nl = 1;
  }

  int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
  uchar mask = 0xFF << n;  // e.g. =16, mask= 0xF0

  for (int j = 0; j < nl; j++) {
    uchar *data = image.ptr<uchar>(j);
    for (int i = 0; i < nc; i++) {
      *data++ = *data & mask + div / 2;
    }
  }
}

void colorReduce7(cv::Mat &image, int div = 64) {
  int nl = image.rows;
  int nc = image.cols;

  if (image.isContinuous()) {
    nc = nc * nl;
    nl = 1;
  }

  int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
  uchar mask = 0xFF << n;  // e.g. =16, mask= 0xF0

  for (int j = 0; j < nl; j++) {
    uchar *data = image.ptr<uchar>(j);
    for (int i = 0; i < nc; i++) {
      *data++ = *data & mask + div / 2;
      *data++ = *data & mask + div / 2;
      *data++ = *data & mask + div / 2;
    }
  }
}

void colorReduce8(cv::Mat &image, int div = 64) {
  Mat_<Vec3b>::iterator it = image.begin<Vec3b>();
  Mat_<Vec3b>::iterator itend = image.end<Vec3b>();

  for (; it != itend; ++it) {
    (*it)[0] = (*it)[0] / div * div + div / 2;
    (*it)[1] = (*it)[1] / div * div + div / 2;
    (*it)[2] = (*it)[2] / div * div + div / 2;
  }
}

void colorReduce9(cv::Mat &image, int div = 64) {
  int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
  uchar mask = 0xFF << n;  // e.g. div=16, mask= 0xF0

  Mat_<Vec3b>::iterator it = image.begin<Vec3b>();
  Mat_<Vec3b>::iterator itend = image.end<Vec3b>();

  for (; it != itend; ++it) {
    (*it)[0] = (*it)[0] & mask + div / 2;
    (*it)[1] = (*it)[1] & mask + div / 2;
    (*it)[2] = (*it)[2] & mask + div / 2;
  }
}

void colorReduce10(cv::Mat &image, int div = 64) {
  Mat_<Vec3b> cimage = image;
  Mat_<Vec3b>::iterator it = cimage.begin();
  Mat_<Vec3b>::iterator itend = cimage.end();

  for (; it != itend; it++) {
    (*it)[0] = (*it)[0] / div * div + div / 2;
    (*it)[1] = (*it)[1] / div * div + div / 2;
    (*it)[2] = (*it)[2] / div * div + div / 2;
  }
}

void colorReduce11(cv::Mat &image, int div = 64) {
  int nl = image.rows;
  int nc = image.cols;

  for (int j = 0; j < nl; j++) {
    for (int i = 0; i < nc; i++) {
      image.at<Vec3b>(j, i)[0] = image.at<Vec3b>(j, i)[0] / div * div + div / 2;
      image.at<Vec3b>(j, i)[1] = image.at<Vec3b>(j, i)[1] / div * div + div / 2;
      image.at<Vec3b>(j, i)[2] = image.at<Vec3b>(j, i)[2] / div * div + div / 2;
    }
  }
}

void colorReduce12(const cv::Mat &image, cv::Mat &result, int div = 64) {
  int nl = image.rows;
  int nc = image.cols;

  result.create(image.rows, image.cols, image.type());

  nc = nc * nl;
  nl = 1;

  int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
  uchar mask = 0xFF << n;

  for (int j = 0; j < nl; j++) {
    uchar *data = result.ptr<uchar>(j);
    const uchar *idata = image.ptr<uchar>(j);
    for (int i = 0; i < nc; i++) {
      *data++ = (*idata++) & mask + div / 2;
      *data++ = (*idata++) & mask + div / 2;
      *data++ = (*idata++) & mask + div / 2;
    }
  }
}

void colorReduce13(cv::Mat &image, int div = 64) {
  int n = static_cast<int>(log(static_cast<double>(div)) / log(2.0));
  uchar mask = 0xFF << n;  // e.g. =16, mask= 0xF0

  image =
      (image & Scalar(mask, mask, mask)) + Scalar(div / 2, div / 2, div / 2);
}

std::string name = "1.jpg";
int main() {
  int64 t[NTESTS], tinit;
  cv::Mat image0;
  cv::Mat image1;
  cv::Mat image2;

  image0 = imread(name);
  if (!image0.data) return 0;

  for (int i = 0; i < NTESTS; i++) t[i] = 0;

  int n = NITERATIONS;
  for (int k = 0; k < n; k++) {
    cout << k << " of " << n << endl;

    image1 = imread(name);
    tinit = getTickCount();
    colorReduce0(image1);
    t[0] += getTickCount() - tinit;

    image1 = imread(name);
    tinit = getTickCount();
    colorReduce1(image1);
    t[1] += getTickCount() - tinit;

    image1 = imread(name);
    tinit = getTickCount();
    colorReduce2(image1);
    t[2] += getTickCount() - tinit;

    image1 = imread(name);
    tinit = getTickCount();
    colorReduce3(image1);
    t[3] += getTickCount() - tinit;

    image1 = imread(name);
    tinit = getTickCount();
    colorReduce4(image1);
    t[4] += getTickCount() - tinit;

    image1 = imread(name);
    tinit = getTickCount();
    colorReduce5(image1);
    t[5] += getTickCount() - tinit;

    image1 = imread(name);
    tinit = getTickCount();
    colorReduce6(image1);
    t[6] += getTickCount() - tinit;

    image1 = imread(name);
    tinit = getTickCount();
    colorReduce7(image1);
    t[7] += getTickCount() - tinit;

    image1 = imread(name);
    tinit = getTickCount();
    colorReduce8(image1);
    t[8] += getTickCount() - tinit;

    image1 = imread(name);
    tinit = getTickCount();
    colorReduce9(image1);
    t[9] += getTickCount() - tinit;

    image1 = imread(name);
    tinit = getTickCount();
    colorReduce10(image1);
    t[10] += getTickCount() - tinit;

    image1 = imread(name);
    tinit = getTickCount();
    colorReduce11(image1);
    t[11] += getTickCount() - tinit;

    image1 = imread(name);
    tinit = getTickCount();
    cv::Mat result;
    colorReduce12(image1, result);
    t[12] += getTickCount() - tinit;
    image2 = result;

    image1 = imread(name);
    tinit = getTickCount();
    colorReduce13(image1);
    t[13] += getTickCount() - tinit;
  }
  imshow("ԭʼͼ��", image0);
  imshow("���", image2);
  imshow("ͼ����", image1);

  cout << endl << "-------------------------------------------" << endl << endl;
  cout << "\n������һ������.ptr �� []�ķ�������ʱ��Ϊ "
       << 1000. * t[0] / getTickFrequency() / n << "ms" << endl;
  cout << "\n�������������� .ptr �� * ++ �ķ�������ʱ��Ϊ"
       << 1000. * t[1] / getTickFrequency() / n << "ms" << endl;
  cout << "\n��������������.ptr �� * ++ �Լ�ģ�����ķ�������ʱ��Ϊ"
       << 1000. * t[2] / getTickFrequency() / n << "ms" << endl;
  cout << "\n�������ġ�����.ptr �� * ++ �Լ�λ�����ķ�������ʱ��Ϊ"
       << 1000. * t[3] / getTickFrequency() / n << "ms" << endl;
  cout << "\n�������塿����ָ����������ķ�������ʱ��Ϊ"
       << 1000. * t[4] / getTickFrequency() / n << "ms" << endl;
  cout << "\n�������������� .ptr �� * ++�Լ�λ���㡢channels()�ķ�������ʱ��Ϊ"
       << 1000. * t[5] / getTickFrequency() / n << "ms" << endl;
  cout << "\n�������ߡ�����.ptr �� * ++ �Լ�λ����(continuous)�ķ�������ʱ��Ϊ"
       << 1000. * t[6] / getTickFrequency() / n << "ms" << endl;
  cout << "\n�������ˡ����� .ptr �� * ++ �Լ�λ���� "
          "(continuous+channels)�ķ�������ʱ��Ϊ"
       << 1000. * t[7] / getTickFrequency() / n << "ms" << endl;
  cout << "\n�������š�����Mat_ iterator �ķ�������ʱ��Ϊ"
       << 1000. * t[8] / getTickFrequency() / n << "ms" << endl;
  cout << "\n������ʮ������Mat_ iterator�Լ�λ����ķ�������ʱ��Ϊ"
       << 1000. * t[9] / getTickFrequency() / n << "ms" << endl;
  cout << "\n������ʮһ������Mat Iterator_�ķ�������ʱ��Ϊ"
       << 1000. * t[10] / getTickFrequency() / n << "ms" << endl;
  cout << "\n������ʮ�������ö�̬��ַ�������at �ķ�������ʱ��Ϊ"
       << 1000. * t[11] / getTickFrequency() / n << "ms" << endl;
  cout << "\n������ʮ��������ͼ�������������ķ�������ʱ��Ϊ"
       << 1000. * t[12] / getTickFrequency() / n << "ms" << endl;
  cout << "\n������ʮ�ġ����ò��������صķ�������ʱ��Ϊ"
       << 1000. * t[13] / getTickFrequency() / n << "ms" << endl;

  waitKey();
  return 0;
}
