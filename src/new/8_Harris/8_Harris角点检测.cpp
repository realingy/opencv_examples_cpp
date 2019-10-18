#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include "path.h"

using namespace cv;
using namespace std;

/***************************************************
在图像中角点是一个重要的局部特征，它决定了图像中关键区域的形状，体现了图像中重要的特征信息，所以在目标识别、图像匹配、图像重构方面角点具有十分重要的意义。
图像中角点的数量远比总像素数小，如果通过角点就能完成一些功能的话，将极大地提高处理效率。 对角点的定义一般分为以下三种：图像边界曲线上具有极大曲率值的点；
图像中梯度值和梯度变化率都很高的点；图像边界方向变化不连续的点。 定义不同，角点的提取方法也不尽相同。目前，角点检测方法主要有２大类：
１）基于图像边缘轮廓特征的方法。此方法需要经过图像预分割、轮廓链码提取和角点检测，如基于边界曲率的角点检测，基于边界小波变换的角点检测以及基于边界链码的角点检测。
２）基于图像灰度信息的方法。此方法主要通过计算曲率及梯度进行角点检测，通过计算边缘的曲率来判断角点的存在性。典型代表有Harris算法、Susan算法、Moravec算法等。
****************************************************/


/************************************************/
void ConvertBGR_img2GRAY_img(const Mat &BGR_img, Mat &Gray_img)
{
	//这个函数实现将彩色图转化成灰度图,利用常用公式：Gray = R*0.299 + G*0.587 + B*0.114进行自编程实现
	//第一个参数BGR_img表示输入的彩色RGB图像的引用；    
	//第二个参数Gray_img表示转换后输出的灰度图像的引用；                  
	if (BGR_img.empty() || BGR_img.channels() != 3)
	{
		return;
	}
	Gray_img = Mat::zeros(BGR_img.size(), CV_8UC1);       //创建一张与输入图像同大小的单通道灰度图像  
	uchar *pointImage = BGR_img.data;                        //取出存储图像像素的数组的指针  
	uchar *pointImageGray = Gray_img.data;
	int height = BGR_img.rows;
	int width = BGR_img.cols;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			*(pointImageGray + i * Gray_img.step[0] + j * Gray_img.step[1]) = (uchar)(0.114*(pointImage + i * BGR_img.step[0] + j * BGR_img.step[1])[0] + 0.587*(pointImage + i * BGR_img.step[0] + j * BGR_img.step[1])[1] + 0.299*(pointImage + i * BGR_img.step[0] + j * BGR_img.step[1])[2]);
		}
	}
}
/**********************************************/

/*******************************************************/
//非极大值抑制和阈值检测
void LocalMaxValue(Mat &resultData, Mat &ResultImage, int kSize)
{
	int r = kSize / 2;
	for (int i = r; i < ResultImage.rows - r; i++)
	{
		for (int j = r; j < ResultImage.cols - r; j++)
		{
			if (resultData.at<double>(i, j) > resultData.at<double>(i - 1, j - 1) &&
				resultData.at<double>(i, j) > resultData.at<double>(i - 1, j) &&
				resultData.at<double>(i, j) > resultData.at<double>(i - 1, j + 1) &&
				resultData.at<double>(i, j) > resultData.at<double>(i, j - 1) &&
				resultData.at<double>(i, j) > resultData.at<double>(i, j + 1) &&
				resultData.at<double>(i, j) > resultData.at<double>(i + 1, j - 1) &&
				resultData.at<double>(i, j) > resultData.at<double>(i + 1, j) &&
				resultData.at<double>(i, j) > resultData.at<double>(i + 1, j + 1))
			{
				if ((int)resultData.at<double>(i, j) > 15000)
				{
					circle(ResultImage, Point(j, i), 5, Scalar(0, 0, 255), 2, 8, 0);
				}
			}
		}
	}
}
/*********************************************************/

//  主函数
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
	ConvertBGR_img2GRAY_img(src_img, gray_img);
	namedWindow("灰度图", CV_WINDOW_AUTOSIZE);
	imshow("灰度图", gray_img);

	// 第一步：用sobel算子计算度图像的水平和垂直方向上的差分
	Mat image_con_sobel_Ix, image_con_sobel_Iy;
	//image_con_sobel_Ix = sobel(gray_img,1,0, 3, BORDER_DEFAULT);
	//image_con_sobel_Iy = sobel(gray_img,0,1, 3, BORDER_DEFAULT);
	Sobel(gray_img, image_con_sobel_Ix, CV_64F, 1, 0, 3);
	Sobel(gray_img, image_con_sobel_Iy, CV_64F, 0, 1, 3);

	//imshow("x差分", image_con_sobel_Ix);
	//imshow("y差分", image_con_sobel_Iy);

	//convertScaleAbs(image_con_sobel_Ix, image_con_sobel_Ix);
	//convertScaleAbs(image_con_sobel_Iy, image_con_sobel_Iy);

	//  第二步：计算Ixx,Iyy,Ixy
	Mat image_con_sobel_Ixx, image_con_sobel_Iyy, image_con_sobel_Ixy;
	multiply(image_con_sobel_Ix, image_con_sobel_Ix, image_con_sobel_Ixx, 1.0, CV_64FC1);
	multiply(image_con_sobel_Iy, image_con_sobel_Iy, image_con_sobel_Iyy, 1.0, CV_64FC1);
	multiply(image_con_sobel_Ix, image_con_sobel_Iy, image_con_sobel_Ixy, 1.0, CV_64FC1);

	//第三步：对Ixx,Iyy,Ixy进行高斯平滑
	Mat blurimage_Ixx, blurimage_Iyy, blurimage_Ixy;
	GaussianBlur(image_con_sobel_Ixx, blurimage_Ixx, Size(3, 3), 5);
	GaussianBlur(image_con_sobel_Iyy, blurimage_Iyy, Size(3, 3), 5);
	GaussianBlur(image_con_sobel_Ixy, blurimage_Ixy, Size(3, 3), 5);

	//第四步：计算响应函数,为避免K值的随机性，我采用另外一种响应函数表达式
	Mat Response_data;
	Response_data = (blurimage_Ixx.mul(blurimage_Iyy) - blurimage_Ixy.mul(blurimage_Ixy)) / (blurimage_Ixx + blurimage_Iyy);

	//第五步：非极大值抑制和阀值检测    
	Mat ResultImage = gray_img.clone();
	LocalMaxValue(Response_data, ResultImage, 3);
	namedWindow("结果", CV_WINDOW_AUTOSIZE);
	imshow("结果", ResultImage);
	waitKey(0);
	return 0;
}