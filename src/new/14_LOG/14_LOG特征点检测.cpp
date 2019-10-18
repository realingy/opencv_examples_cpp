#include <opencv2/opencv.hpp>
#include <iostream>
#include "path.h"
 
using namespace cv;
using namespace std;
 
int main( )
{
	Mat src_img = imread(MediaPath + "3.jpg");
	if (src_img.empty()) 
	{
		printf("could not load the image...\n");
		return -1;
	}
	namedWindow("原图", CV_WINDOW_AUTOSIZE);
	imshow("原图", src_img);
 
	// HOG-SVM行人检测
	HOGDescriptor hog = HOGDescriptor();
	hog.setSVMDetector(hog.getDefaultPeopleDetector());
 
	vector<Rect> foundLocations;
	hog.detectMultiScale(src_img, foundLocations, 0, Size(8, 8), Size(32, 32), 1.05, 2);
	Mat result_img = src_img.clone();
	for (auto t = 0; t < foundLocations.size(); ++t)
	{
		rectangle(result_img, foundLocations[t], Scalar(0, 0, 255), 2, 8, 0);
	}
	namedWindow("HOG-SVM Detector", CV_WINDOW_AUTOSIZE);
	imshow("HOG-SVM Detector", result_img);
 
	waitKey(0);
	return 0;
}
 
