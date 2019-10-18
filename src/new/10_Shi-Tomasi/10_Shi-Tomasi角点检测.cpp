#include <opencv2/opencv.hpp>
#include <iostream>
#include "path.h"

using namespace cv;
using namespace std;

// 定义全局变量
int num_corners = 25;
int max_corners = 200;
const string output_title = "Shi-Tomasi检测";
void ShiTomasi_Demo(int, void*);                  // 回调函数声明
Mat src_img, gray_img;

//定义一个RNG类对象，便于后面使用rng.uniform(0, 255)来产生一个0-255之间
//的随机整数（下限值和上限值都是整数，则返回的随机数也是整数）
RNG rng;

// 主函数
int main()
{
	src_img = imread(MediaPath + "1.jpg");
	if (src_img.empty())
	{
		printf("could not load the image...\n");
		return -1;
	}
	namedWindow("原图", CV_WINDOW_AUTOSIZE);
	imshow("原图", src_img);
	cvtColor(src_img, gray_img, COLOR_BGR2GRAY);          //彩色图像转化为灰度图像
	namedWindow(output_title, CV_WINDOW_AUTOSIZE);
	createTrackbar("角点数目", output_title, &num_corners, max_corners, ShiTomasi_Demo);     //创建TrackBar
	ShiTomasi_Demo(0, 0);
	for (int i = 0; i < 20; ++i)
		cout << rng.uniform(0, 255) << endl;
	waitKey(0);
	return 0;
}

// 回调函数实现
void ShiTomasi_Demo(int, void*)
{
	if (num_corners < 5)
	{
		num_corners = 5;
	}
	vector<Point2f> corners; // 即vector中的每一个元素都是Point2f类型的，OpenCV中有定义：typedef Point_<float> Point2f; 
	double qualityLevel = 0.01;
	double minDistance = 10;
	int blockSize = 3;
	bool useHarris = false;
	double k = 0.04;
	Mat result_img = src_img.clone();
	goodFeaturesToTrack(gray_img, corners, num_corners, qualityLevel, minDistance, Mat(), blockSize, useHarris, k);
	printf("检测到角点的数目:  %d\n", corners.size()); // Vector对象的size()方法返回其中的元素个数

	for (auto t = 0; t < corners.size(); ++t) // 遍历检测到的每一个角点
	{
		circle(result_img, corners[t], 2, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2, 8, 0);
	}
	imshow(output_title, result_img);
}


