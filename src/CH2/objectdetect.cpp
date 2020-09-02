#include <stdio.h>

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>

using namespace std;

void detectAndDisplay(cv::Mat frame);

cv::String face_cascade_name =
    "D:\\project_opencv\\CH2\\objectdetect\\objectdetect\\haarcascade_"
    "frontalface_alt.xml";
cv::String eyes_cascade_name =
    "D:\\project_opencv\\CH2\\objectdetect\\objectdetect\\haarcascade_eye_tree_"
    "eyeglasses.xml";
// String face_cascade_name = "haarcascade_frontalface_alt.xml";
// String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
cv::CascadeClassifier face_cascade;
cv::CascadeClassifier eyes_cascade;
string window_name = "Capture - Face detection";
cv::RNG rng(12345);

int main(void) {
  cv::VideoCapture capture;
  cv::Mat frame;

  //  -- 1. 加载级联（cascades）
  if (!face_cascade.load(face_cascade_name)) {
    printf("--(!)Error loading\n");
    return -1;
  };
  if (!eyes_cascade.load(eyes_cascade_name)) {
    printf("--(!)Error loading\n");
    return -1;
  };

  //  -- 2. 读取视频
  capture.open(0);
  //  ShowHelpText();
  if (capture.isOpened()) {
    for (;;) {
      capture >> frame;
      //      -- 3. 对当前帧使用分类器（Apply the classifier to the frame）
      if (!frame.empty()) {
        detectAndDisplay(frame);
      } else {
        printf(" --(!) No captured frame -- Break!");
        break;
      }
#if 0
          int c = waitKey(10);
          if( (char)c == 'c' ) { break; }
#endif
      cv::waitKey(30);
    }
  }
  return 0;
}

void detectAndDisplay(cv::Mat frame) {
  std::vector<cv::Rect> faces;
  cv::Mat frame_gray;

  cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
  equalizeHist(frame_gray, frame_gray);

  // -- 人脸检测
  // 此句代码的OpenCV2版为：
  // face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2,
  // 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) ); 此句代码的OpenCV3版为：
  //   face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2,
  //   0|CASCADE_SCALE_IMAGE, Size(30, 30) );
  face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2,
                                0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

  for (size_t i = 0; i < faces.size(); i++) {
    cv::Point center(faces[i].x + faces[i].width / 2,
                     faces[i].y + faces[i].height / 2);
    ellipse(frame, center, cv::Size(faces[i].width / 2, faces[i].height / 2), 0,
            0, 360, cv::Scalar(255, 0, 255), 2, 8, 0);

    cv::Mat faceROI = frame_gray(faces[i]);
    std::vector<cv::Rect> eyes;

    //-- 在脸中检测眼睛
    //此句代码的OpenCV2版为：
    // eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0
    // |CV_HAAR_SCALE_IMAGE, Size(30, 30) ); 此句代码的OpenCV3版为：
    //      eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2,
    //      0|CASCADE_SCALE_IMAGE, Size(30, 30) );
    eyes_cascade.detectMultiScale(
        faceROI, eyes, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

    for (size_t j = 0; j < eyes.size(); j++) {
      cv::Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2,
                           faces[i].y + eyes[j].y + eyes[j].height / 2);
      int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);
      circle(frame, eye_center, radius, cv::Scalar(255, 0, 0), 3, 8, 0);
    }
  }
  //-- 显示最终效果图
  cv::imshow(window_name, frame);
}
