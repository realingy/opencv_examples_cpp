#include <ctype.h>

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/video/tracking.hpp>

using namespace std;

cv::Mat image;
bool backprojMode = false;
bool selectObject = false;
int trackObject = 0;
bool showHist = true;
cv::Point origin;
cv::Rect selection;
int vmin = 10, vmax = 256, smin = 30;

static void onMouse(int event, int x, int y, int, void*) {
  if (selectObject) {
    selection.x = MIN(x, origin.x);
    selection.y = MIN(y, origin.y);
    selection.width = std::abs(x - origin.x);
    selection.height = std::abs(y - origin.y);

    selection &= cv::Rect(0, 0, image.cols, image.rows);
  }

  switch (event) {
    case cv::EVENT_LBUTTONDOWN:
      origin = cv::Point(x, y);
      selection = cv::Rect(x, y, 0, 0);
      selectObject = true;
      break;
    case cv::EVENT_LBUTTONUP:
      selectObject = false;
      if (selection.width > 0 && selection.height > 0) trackObject = -1;
      break;
  }
}

const char* keys = {"{1|  | 0 | camera number}"};

int main(int argc, const char** argv) {
  cv::VideoCapture cap;
  cv::Rect trackWindow;
  int hsize = 16;
  float hranges[] = {0, 180};
  const float* phranges = hranges;

  cap.open(0);

  if (!cap.isOpened()) {
    cout << "不能初始化摄像头\n";
  }

  cv::namedWindow("Histogram", 0);
  cv::namedWindow("CamShift Demo", 0);
  cv::setMouseCallback("CamShift Demo", onMouse, 0);
  cv::createTrackbar("Vmin", "CamShift Demo", &vmin, 256, 0);
  cv::createTrackbar("Vmax", "CamShift Demo", &vmax, 256, 0);
  cv::createTrackbar("Smin", "CamShift Demo", &smin, 256, 0);

  cv::Mat frame, hsv, hue, mask, hist,
      histimg = cv::Mat::zeros(200, 320, CV_8UC3), backproj;
  bool paused = false;

  for (;;) {
    if (!paused) {
      cap >> frame;
      if (frame.empty()) break;
    }

    frame.copyTo(image);

    if (!paused) {
      cvtColor(image, hsv, cv::COLOR_BGR2HSV);

      if (trackObject) {
        int _vmin = vmin, _vmax = vmax;

        cv::inRange(hsv, cv::Scalar(0, smin, MIN(_vmin, _vmax)),
                    cv::Scalar(180, 256, MAX(_vmin, _vmax)), mask);
        int ch[] = {0, 0};
        hue.create(hsv.size(), hsv.depth());
        mixChannels(&hsv, 1, &hue, 1, ch, 1);

        if (trackObject < 0) {
          cv::Mat roi(hue, selection), maskroi(mask, selection);
          calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
          normalize(hist, hist, 0, 255, cv::NORM_MINMAX);

          trackWindow = selection;
          trackObject = 1;

          histimg = cv::Scalar::all(0);
          int binW = histimg.cols / hsize;
          cv::Mat buf(1, hsize, CV_8UC3);
          for (int i = 0; i < hsize; i++)
            buf.at<cv::Vec3b>(i) =
                cv::Vec3b(cv::saturate_cast<uchar>(i * 180. / hsize), 255, 255);

          cv::cvtColor(buf, buf, cv::COLOR_HSV2BGR);

          for (int i = 0; i < hsize; i++) {
            int val =
                cv::saturate_cast<int>(hist.at<float>(i) * histimg.rows / 255);
            rectangle(histimg, cv::Point(i * binW, histimg.rows),
                      cv::Point((i + 1) * binW, histimg.rows - val),
                      cv::Scalar(buf.at<cv::Vec3b>(i)), -1, 8);
          }
        }

        calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
        backproj &= mask;
        cv::RotatedRect trackBox = CamShift(
            backproj, trackWindow,
            cv::TermCriteria(cv::TermCriteria::EPS | cv::TermCriteria::COUNT,
                             10, 1));

        if (trackWindow.area() <= 1) {
          int cols = backproj.cols, rows = backproj.rows,
              r = (MIN(cols, rows) + 5) / 6;
          trackWindow = cv::Rect(trackWindow.x - r, trackWindow.y - r,
                                 trackWindow.x + r, trackWindow.y + r) &
                        cv::Rect(0, 0, cols, rows);
        }

        if (backprojMode) {
          cvtColor(backproj, image, cv::COLOR_GRAY2BGR);
        }

        ellipse(image, trackBox, cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
      }
    } else if (trackObject < 0)
      paused = false;

    if (selectObject && selection.width > 0 && selection.height > 0) {
      cv::Mat roi(image, selection);
      cv::bitwise_not(roi, roi);
    }

    cv::imshow("CamShift Demo", image);
    cv::imshow("Histogram", histimg);

    char c = (char)cv::waitKey(10);
    if (c == 27) break;
    switch (c) {
      case 'b':
        backprojMode = !backprojMode;
        break;
      case 'c':
        trackObject = 0;
        histimg = cv::Scalar::all(0);
        break;
      case 'h':
        showHist = !showHist;
        if (!showHist)
          cv::destroyWindow("Histogram");
        else
          cv::namedWindow("Histogram", 1);
        break;
      case 'p':
        paused = !paused;
        break;
      default:;
    }
  }

  return 0;
}
