#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include "path.h"

using namespace cv;
using namespace std;

/******************************************************************************************************************************************
Sobel算子是像素图像边缘检测中最重要的算子之一，在机器学习、数字媒体、计算机视觉等信息科技领域起着举足轻重的作用。
在技术上，它是一个离散的一阶差分算子，用来计算图像亮度函数的一阶梯度之近似值。在图像的任何一点使用此算子，将会产生该点对应的梯度矢量或是其法矢量。
******************************************************************************************************************************************/

/*********************************************************************************************************/
/*     用sobel算子对灰度图像进行滤波           */

int factorial(int n)
{
	// factorial()函数实现阶乘
	int fac = 1;
	if (n == 0)
	{
		return fac;
	}
	for (int i = 1; i <= n; ++i)
	{
		fac *= i;
	}
	return fac;
}

//  getPascalSmooth()函数用来创建sobel平滑算子
Mat getPascalSmooth(int n)
{
	Mat pascalSmooth = Mat::zeros(Size(n, 1), CV_32FC1);
	for (int i = 0; i < n; ++i)
	{
		pascalSmooth.at<float>(0, i) = float(factorial(n - 1) / (factorial(i)*factorial(n - 1 - i)));

	}
	return pascalSmooth;
}

//  getPascalDiff()函数用来创建sobel差分算子
Mat getPascalDiff(int n)
{
	Mat pascalDiff = Mat::zeros(Size(n, 1), CV_32FC1);
	Mat pascalSmooth_previous = getPascalSmooth(n - 1);
	for (int i = 0; i < n; ++i)
	{
		if (i == 0)
		{
			pascalDiff.at<float>(0, i) = 1;
		}
		else if (i == n - 1)
		{
			pascalDiff.at<float>(0, i) = -1;
		}
		else
		{
			pascalDiff.at<float>(0, i) = pascalSmooth_previous.at<float>(0, i) - pascalSmooth_previous.at<float>(0, i - 1);
		}
	}
	return  pascalDiff;
}

void conv2D(InputArray src, InputArray kernel, OutputArray dst, int ddepth, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//  conv2D()函数用来完成same卷积运算
	Mat kernelFlip;
	flip(kernel, kernelFlip, -1);    // 卷积运算的第一步，将卷积核逆时针翻转180°
	filter2D(src, dst, ddepth, kernelFlip, anchor, 0.0, borderType);   //卷积运算的第二步
}

void sepConv2D_Y_X(InputArray src, OutputArray  src_kerY_kerX, int ddepth, InputArray kernelY, InputArray kernelX, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	// 对于可分离的离散二维卷积，先进行垂直方向上的卷积，再进行水平方向上的卷积
	Mat src_kerY;
	conv2D(src, kernelY, src_kerY, ddepth, anchor, borderType);   // 输入矩阵与垂直方向上的卷积核的卷积
	conv2D(src_kerY, kernelX, src_kerY_kerX, ddepth, anchor, borderType);  // 把从上面得到的卷积结果和水平方向上的卷积核卷积
}

void sepConv2D_X_Y(InputArray src, OutputArray  src_kerX_kerY, int ddepth, InputArray kernelX, InputArray kernelY, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	// 对于可分离的离散二维卷积，先进行水平方向上的卷积，再进行垂直方向上的卷积
	Mat src_kerX;
	conv2D(src, kernelX, src_kerX, ddepth, anchor, borderType);   // 输入矩阵与水平方向上的卷积核的卷积
	conv2D(src_kerX, kernelY, src_kerX_kerY, ddepth, anchor, borderType);  // 把从上面得到的卷积结果和垂直方向上的卷积核卷积
}

// 自己实现Sobel算子
// sobel函数用来完成图像灰度矩阵与sobel核的卷积 
Mat sobel(Mat& image, int x_flag, int y_flag, int winSize, int borderType)
{
	CV_Assert(winSize >= 3 && winSize % 2 == 1);   // sobel卷积核的窗口大小为大于3的奇数
	Mat pascalSmooth = getPascalSmooth(winSize);   // sobel平滑算子
	//Mat pascalDiff = getPascalSmooth(winSize);     // sobel差分算子
	Mat pascalDiff = getPascalDiff(winSize);     // sobel差分算子
	Mat image_con_sobel;                           // 输出矩阵
	if (x_flag != 0)
	{
		sepConv2D_Y_X(image, image_con_sobel, CV_32FC1, pascalSmooth.t(), pascalDiff, Point(-1, -1), borderType);     //先进行一维垂直方向上的平滑，再进行一维水平方向上的差分，即图像与sobel_x进行卷积运算
	}
	if (x_flag == 0 && y_flag != 0)
	{
		sepConv2D_X_Y(image, image_con_sobel, CV_32FC1, pascalSmooth, pascalDiff.t(), Point(-1, -1), borderType);    //先进行一维水平方向上的平滑，再进行一维垂直方向上的差分,即图像与sobel_y进行卷积运算
	}
	return  image_con_sobel;
}
/********************************************************************************************************************/

// 主函数
int main()
{
	const Mat src_img = imread(MediaPath + "1.jpg");
	if (src_img.empty())
	{
		printf("could not load image...\n");
		return -1;
	}

	namedWindow("原图：", CV_WINDOW_AUTOSIZE);
	imshow("原图：", src_img);

	// 将彩色图转化为灰度图，调用OpenCV提供的cvtColor接口
	Mat gray_img;
	cvtColor(src_img, gray_img, CV_BGR2GRAY);
	namedWindow("灰度图", CV_WINDOW_AUTOSIZE);
	imshow("灰度图", gray_img);

	// 用sobel算子计算度图像的水平和垂直方向上的差分
	Mat image_con_sobel_Ix, image_con_sobel_Iy;
	//image_con_sobel_Ix = sobel(gray_img, 1, 0, 3, BORDER_DEFAULT); //库函数
	//image_con_sobel_Iy = sobel(gray_img, 0, 1, 3, BORDER_DEFAULT); //库函数
	Sobel(gray_img, image_con_sobel_Ix, CV_64F, 1, 0, 3);
	Sobel(gray_img, image_con_sobel_Iy, CV_64F, 0, 1, 3);

	// 水平方向和垂直方向上的边缘强度
	// 数据类型转换，边缘强度的灰度级显示
	Mat scale_sobel_Ix, scale_sobel_Iy;
	convertScaleAbs(image_con_sobel_Ix, scale_sobel_Ix);              //  转化为8位灰度级显示
	convertScaleAbs(image_con_sobel_Iy, scale_sobel_Iy);
	imshow("垂直方向的边缘", scale_sobel_Ix);
	imshow("水平方向的边缘", scale_sobel_Iy);

	waitKey(0);
	return 0;
}


