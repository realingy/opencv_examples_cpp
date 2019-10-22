#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "path.h"
#include <iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME "【程序窗口】" //为窗口标题定义的宏 

double area; //轮廓面积
int g_nThresholdValue = 131; //二值化阈值
int g_nThresholdType = 3;
double minarea = 378; //目标轮廓最小像素点个数
double maxarea = 478; //目标轮廓最大像素点个数
Moments mom; //轮廓矩  

Mat image, gray, edge, dst, g_srcImage1, dst1, g_srcImage, g_grayImage, g_dstImage;

vector<vector<Point> > contours;   //轮廓数组  
vector<Point2d>  centers;    //轮廓质心坐标   
vector<vector<Point> >::iterator itr;  //轮廓迭代器  
vector<Point2d>::iterator  itrc;    //质心坐标迭代器  
vector<vector<Point> > con;    //当前轮廓  
Point2d center;//质心坐标

void on_Threshold(int, void*);//回调函数

int main()
{
	g_srcImage = imread(MediaPath + "houghcircle.jpg");

	//resize(g_srcImage, g_srcImage1, Size(g_srcImage.cols / 4, g_srcImage.rows / 4), 0, 0, INTER_LINEAR);
	imshow("原始图", g_srcImage);

	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);//灰度转换

	namedWindow(WINDOW_NAME, WINDOW_NORMAL);

	createTrackbar("模式",
		WINDOW_NAME, &g_nThresholdType,//二值化模式
		4, on_Threshold);

	createTrackbar("参数值",
		WINDOW_NAME, &g_nThresholdValue,//二值化阈值 
		255, on_Threshold);

	on_Threshold(0, 0);//滑动条回调函数

	while (1)
	{
		int key;
		key = waitKey(20);
		if ((char)key == 27) { break; }
	}

	waitKey(0);

	return 0;
}

void on_Threshold(int, void*)
{
	//调用阈值函数，灰度图二值化
	Mat xx;
	threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, CV_THRESH_BINARY);
	resize(g_dstImage, xx, Size(1000, 500));

	namedWindow("二值图", WINDOW_NORMAL);
	imshow("二值图", xx);

	//resize(g_dstImage, g_srcImage1, Size(g_dstImage.cols / 4, g_dstImage.rows / 4), 0, 0, INTER_LINEAR);
	//imshow("threshold", g_srcImage1);

	Mat element2 = getStructuringElement(MORPH_RECT, Size(10, 10));//膨胀模板
	Mat erode1, erode2;
	dilate(g_dstImage, erode1, element2);//膨胀
	dilate(erode1, erode2, element2);

	//resize(erode2, g_srcImage1, Size(erode2.cols / 4, erode2.rows / 4), 0, 0, INTER_LINEAR);
	//imshow("dilate", g_srcImage1);

	findContours(erode2, contours,
		CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);//找出轮廓

	itr = contours.begin();     //使用迭代器去除非目标轮廓  
	while (itr != contours.end())
	{
		area = contourArea(*itr);//计算面积

		if ((area < minarea) | (area > maxarea))
		{
			itr = contours.erase(itr);  //删除
		}
		else
		{
			itr++;
		}
	}

	dst = Mat::zeros(erode2.rows, erode2.cols, CV_8UC3);//保存中间结果
	itr = contours.begin();
	while (itr != contours.end())
	{
		area = contourArea(*itr);
		con.push_back(*itr);

		//cout << "\nb " << area;
		drawContours(dst, con, -1, Scalar(255, 0, 0), 2);   //目标区域蓝色绘制  
		mom = moments(*itr);   //计算质心
		center.x = (int)(mom.m10 / mom.m00);
		center.y = (int)(mom.m01 / mom.m00);
		char tam[10000];
		char sam[10000];
		sprintf(tam, "(%0.0f)", area);
		sprintf(sam, "(%0.0f,%0.0f)", center.x, center.y);
		putText(dst, tam, Point(center.x, center.y), FONT_HERSHEY_SIMPLEX, 2, Scalar(255, 0, 0), 5);//标出面积
		putText(dst, sam, Point(center.x, center.y + 80), FONT_HERSHEY_SIMPLEX, 2, Scalar(0, 255, 0), 5);//标出质心
		//imwrite("20003.jpg", dst);
		//resize(dst, dst1, Size(dst.cols / 4, dst.rows / 4), 0, 0, INTER_LINEAR);
		//imshow("中间结果", dst1);
		circle(g_srcImage, Point(center.x, center.y), 5, Scalar(0, 225, 0), 2, 3);//画圆

		con.pop_back();

		itr++;
	}

	resize(g_srcImage, g_srcImage1, Size(g_srcImage.cols / 4, g_srcImage.rows / 4), 0, 0, INTER_LINEAR);

	//更新效果图
	imshow(WINDOW_NAME, g_srcImage1);

	//imwrite("s_pos71_run7_img190.jpg", g_srcImage);
}




