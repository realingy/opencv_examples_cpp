// 霍夫线变换综合示例
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"
using namespace std;
using namespace cv;

Mat g_srcImage, g_dstImage,g_midImage; //原始图、中间图和效果图
vector<Vec4i> g_lines; //定义一个矢量结构g_lines用于存放得到的线段矢量集合
//变量接收的TrackBar位置参数
int g_nthreshold=100;

static void on_HoughLines(int, void*);//回调函数

int main( )
{
	system("color 4F");  

	Mat g_srcImage = imread(MediaPath + "1.jpg");

	imshow("【原始图】", g_srcImage);  

	namedWindow("【效果图】",1);
	createTrackbar("值", "【效果图】",&g_nthreshold,200,on_HoughLines);

	// 进行边缘检测和转化为灰度图
	Canny(g_srcImage, g_midImage, 50, 200, 3);//进行一次canny边缘检测
	cvtColor(g_midImage,g_dstImage, COLOR_GRAY2BGR);//转化边缘检测后的图为灰度图

	// 调用一次回调函数，调用一次HoughLinesP函数
	on_HoughLines(g_nthreshold,0);
	HoughLinesP(g_midImage, g_lines, 1, CV_PI/180, 80, 50, 10 );

	imshow("【效果图】", g_dstImage);  

	waitKey(0);  

	return 0;  
}

//【顶帽运算/黑帽运算】窗口的回调函数
static void on_HoughLines(int, void*)
{
	Mat dstImage=g_dstImage.clone();
	Mat midImage=g_midImage.clone();

	//调用HoughLinesP函数
	vector<Vec4i> mylines;
	HoughLinesP(midImage, mylines, 1, CV_PI/180, g_nthreshold+1, 50, 10 );

	//循环遍历绘制每一条线段
	for( size_t i = 0; i < mylines.size(); i++ )
	{
		Vec4i l = mylines[i];
		line( dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23,180,55), 1, LINE_AA);
	}
	imshow("【效果图】",dstImage);
}
