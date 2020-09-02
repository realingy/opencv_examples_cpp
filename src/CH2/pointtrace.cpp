#include <ctype.h>

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/tracking.hpp>

using namespace std;

cv::Point2f point;
bool addRemovePt = false;

static void onMouse(int event, int x, int y, int /*flags*/, void* /*param*/) {
  //此句代码的OpenCV2版为：
  // if( event == CV_EVENT_LBUTTONDOWN )
  //此句代码的OpenCV3版为：
  if (event == cv::EVENT_LBUTTONDOWN) {
    point = cv::Point2f((float)x, (float)y);
    addRemovePt = true;
  }
}

int main(int argc, char** argv) {
  cv::VideoCapture cap;

  //此句代码的OpenCV2版为：
  // TermCriteria termcrit(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 20, 0.03);
  //此句代码的OpenCV3版为：
  cv::TermCriteria termcrit(cv::TermCriteria::MAX_ITER | cv::TermCriteria::EPS,
                            20, 0.03);
  cv::Size subPixWinSize(10, 10), winSize(31, 31);

  const int MAX_COUNT = 500;
  bool needToInit = false;
  bool nightMode = false;

  cap.open(0);

  if (!cap.isOpened()) {
    cout << "Could not initialize capturing...\n";
    return 0;
  }

  cv::namedWindow("LK Demo", 1);
  cv::setMouseCallback("LK Demo", onMouse, 0);

  cv::Mat gray, prevGray, image;
  vector<cv::Point2f> points[2];
  vector<cv::Point2f> features;

  for (;;) {
    cv::Mat frame;
    cap >> frame;
    if (frame.empty()) break;

    frame.copyTo(image);
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    if (nightMode) image = cv::Scalar::all(0);

    if (needToInit) {
      // 自动初始化
      // goodFeaturesToTrack(gray, points[0], MAX_COUNT, 0.01, 10, Mat(), 3, 0,
      // 0.04);
      //********************************************************
      goodFeaturesToTrack(gray, features, MAX_COUNT, 0.01, 10);
      points[0].insert(points[0].end(), features.begin(), features.end());
      //********************************************************
      cornerSubPix(gray, points[1], subPixWinSize, cv::Size(-1, -1), termcrit);
      addRemovePt = false;
    } else if (!points[0].empty()) {
      vector<uchar> status;
      vector<float> err;
      if (prevGray.empty()) gray.copyTo(prevGray);
      calcOpticalFlowPyrLK(prevGray, gray, points[0], points[1], status, err,
                           winSize, 3, termcrit, 0, 0.001);
      size_t i, k;
      for (i = k = 0; i < points[1].size(); i++) {
        if (addRemovePt) {
          if (norm(point - points[1][i]) <= 5) {
            addRemovePt = false;
            continue;
          }
        }

        if (!status[i]) continue;

        points[1][k++] = points[1][i];
        circle(image, points[1][i], 3, cv::Scalar(0, 255, 0), -1, 8);
      }
      points[1].resize(k);
    }

    if (addRemovePt && points[1].size() < (size_t)MAX_COUNT) {
      vector<cv::Point2f> tmp;
      tmp.push_back(point);

      //此句代码的OpenCV2版为：
      // cornerSubPix( gray, tmp, winSize, cvSize(-1,-1), termcrit);
      //此句代码的OpenCV3版为：
      cornerSubPix(gray, tmp, winSize, cv::Size(-1, -1), termcrit);
      points[1].push_back(tmp[0]);
      addRemovePt = false;
    }

    needToInit = false;
    imshow("LK Demo", image);

    char c = (char)cv::waitKey(10);
    if (c == 27) break;
    switch (c) {
      case 'r':
        needToInit = true;
        break;
      case 'c':
        points[0].clear();
        points[1].clear();
        break;
      case 'n':
        nightMode = !nightMode;
        break;
    }

    std::swap(points[1], points[0]);
    cv::swap(prevGray, gray);
  }

  return 0;
}
