#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include "path.h"

using namespace cv;
using namespace std;

string out_title = "Harris角点检测";
int thresh = 100;
int max_count = 255;
Mat src_img, gray_img;
void Harris_callback(int, void*);

int main()
{
	//src_img = imread("test11.png");
	const Mat src_img = imread(MediaPath + "1.jpg");
	if (src_img.empty())
	{
		printf("could not load image...\n");
		return -1;
	}
	namedWindow("原图：", CV_WINDOW_AUTOSIZE);
	imshow("原图：", src_img);
	//namedWindow(out_title, CV_WINDOW_AUTOSIZE);
	cvtColor(src_img, gray_img, CV_BGR2GRAY);

	Mat dst_img, norm_dst_img, scale_dst_img;
	dst_img = Mat::zeros(gray_img.size(), CV_32FC1);
	int  blockSize = 2;
	int ksize = 3;
	double k = 0.04;
	cornerHarris(gray_img, dst_img, blockSize, ksize, k, BORDER_DEFAULT);   //调用API
	normalize(dst_img, norm_dst_img, 0, 255, NORM_MINMAX, CV_32FC1, Mat());     // 调用归一化函数进行归一化处理
	convertScaleAbs(norm_dst_img, scale_dst_img);      //将图像转化为8位图
	Mat result_img = src_img.clone();
	for (int r = 0; r < result_img.rows; ++r)
	{
		uchar *ptr_row = scale_dst_img.ptr<uchar>(r);
		for (int c = 0; c < result_img.cols; ++c)
		{
			int value = int(ptr_row[c]);
			if (value > thresh)
			{
				circle(result_img, Point(c, r), 2, Scalar(0, 0, 255), 2, 8, 0);
			}
		}
	}
	imshow(out_title, result_img);
	//createTrackbar("阈值", out_title, &thresh, max_count, Harris_callback);
	//Harris_callback(0, 0);
	waitKey(0);
	return 0;
}

void Harris_callback(int, void*)
{
	Mat dst_img, norm_dst_img, scale_dst_img;
	dst_img = Mat::zeros(gray_img.size(), CV_32FC1);
	int  blockSize = 2;
	int ksize = 3;
	double k = 0.04;
	cornerHarris(gray_img, dst_img, blockSize, ksize, k, BORDER_DEFAULT);   //调用API
	normalize(dst_img, norm_dst_img, 0, 255, NORM_MINMAX, CV_32FC1, Mat());     // 调用归一化函数进行归一化处理
	convertScaleAbs(norm_dst_img, scale_dst_img);      //将图像转化为8位图
	Mat result_img = src_img.clone();
	for (int r = 0; r < result_img.rows; ++r)
	{
		uchar *ptr_row = scale_dst_img.ptr<uchar>(r);
		for (int c = 0; c < result_img.cols; ++c)
		{
			int value = int(ptr_row[c]);
			if (value > thresh)
			{
				circle(result_img, Point(c, r), 2, Scalar(0, 0, 255), 2, 8, 0);
			}
		}
	}
	imshow(out_title, result_img);
}

