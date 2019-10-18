#include <opencv2/opencv.hpp>
//#include <opencv2/xfeatures2d.hpp>
#include <iostream>

using namespace cv;
//using namespace cv::xfeatures2d;         // 不要忘了导入扩展模块
using namespace std;

Mat src_img, gray_img;
const string output_name = "SURF特征检测";
int minHessian = 100;                // 定义SURF中的hessian阈值特征点检测算子
int max_value = 500;
void SURF_detect_func(int, void *);

int main()
{
	src_img = imread("test3.png");
	if (src_img.empty())
	{
		printf("could not load the image...\n");
		return -1;
	}
	namedWindow("原图", CV_WINDOW_AUTOSIZE);
	imshow("原图", src_img);
	cvtColor(src_img, gray_img, COLOR_BGR2GRAY);
	namedWindow(output_name, CV_WINDOW_AUTOSIZE);
	createTrackbar("hessian阈值", output_name, &minHessian, max_value, SURF_detect_func);
	SURF_detect_func(0, 0);

	waitKey(0);
	return 0;
}

void SURF_detect_func(int, void *)
{
	// SURF特征检测
//	Ptr<SURF> detector = SURF::create(minHessian);
	vector<KeyPoint> keypoints;
//	detector->detect(gray_img, keypoints, Mat());      // 检测src_img图像中的SURF特征
  // 绘制关键点
	Mat keypoint_img;
	drawKeypoints(gray_img, keypoints, keypoint_img, Scalar::all(-1), DrawMatchesFlags::DEFAULT);  // Scalar::all(-1)这是一种技巧，就是当用一个负数作为关键点颜色，表示每次随机选取颜色。
	imshow(output_name, keypoint_img);
}
