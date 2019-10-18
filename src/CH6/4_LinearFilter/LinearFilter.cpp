#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "path.h"
#include <iostream>

using namespace std;
using namespace cv;

Mat g_srcImage,g_dstImage1,g_dstImage2,g_dstImage3;//存储图片的Mat类型
int g_nBoxFilterValue=3;  //方框滤波参数值
int g_nMeanBlurValue=3;  //均值滤波参数值
int g_nGaussianBlurValue=3;  //高斯滤波参数值

static void on_BoxFilter(int, void *);		//均值滤波
static void on_MeanBlur(int, void *);		//均值滤波
static void on_GaussianBlur(int, void *);	//高斯滤波

int main()
{
	system("color 5F");  

	g_srcImage = imread(MediaPath + "7.jpg", 1);
	if(!g_srcImage.data) {return 0;}

	g_dstImage1 = g_srcImage.clone();
	g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();

	namedWindow("【<0>原图窗口】", 1);
	imshow("【<0>原图窗口】",g_srcImage);

	//=================【<1>方框滤波】==================
	namedWindow("【<1>方框滤波】", 1);
	createTrackbar("内核值：", "【<1>方框滤波】", &g_nBoxFilterValue, 40, on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);

	//=================【<2>均值滤波】==================
	namedWindow("【<2>均值滤波】", 1);
	createTrackbar("内核值：", "【<2>均值滤波】",&g_nMeanBlurValue, 40,on_MeanBlur );
	on_MeanBlur(g_nMeanBlurValue,0);

	//=================【<3>高斯滤波】=====================
	namedWindow("【<3>高斯滤波】", 1);
	createTrackbar("内核值：", "【<3>高斯滤波】",&g_nGaussianBlurValue, 40,on_GaussianBlur );
	on_GaussianBlur(g_nGaussianBlurValue,0);

	//输出一些帮助信息
	cout<<endl<<"\t运行成功，请调整滚动条观察图像效果~\n\n"
		<<"\t按下“q”键时，程序退出。\n";

	//按下“q”键时，程序退出
	while(char(waitKey(1)) != 'q') {}

	return 0;
}

//描述：方框滤波操作的回调函数
static void on_BoxFilter(int, void *)
{
	boxFilter( g_srcImage, g_dstImage1, -1,Size( g_nBoxFilterValue+1, g_nBoxFilterValue+1));
	imshow("【<1>方框滤波】", g_dstImage1);
}

//描述：均值滤波操作的回调函数
static void on_MeanBlur(int, void *)
{
	blur( g_srcImage, g_dstImage2, Size( g_nMeanBlurValue+1, g_nMeanBlurValue+1), Point(-1,-1));
	imshow("【<2>均值滤波】", g_dstImage2);
}

//描述：高斯滤波操作的回调函数
static void on_GaussianBlur(int, void *)
{
	GaussianBlur( g_srcImage, g_dstImage3, Size( g_nGaussianBlurValue*2+1, g_nGaussianBlurValue*2+1 ), 0, 0);
	imshow("【<3>高斯滤波】", g_dstImage3);
}

