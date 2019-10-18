// Harris角点检测
#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "path.h"
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "【程序窗口1】"        //为窗口标题定义的宏  
#define WINDOW_NAME2 "【程序窗口2】"        //为窗口标题定义的宏  

Mat g_srcImage, g_srcImage1,g_grayImage;
int thresh = 30; //当前阈值
int max_thresh = 175; //最大阈值

void on_CornerHarris( int, void* );//回调函数

int main( int argc, char** argv )
{
	system("color 3F");  

	g_srcImage = imread( MediaPath+"CH10/cornerHarris2.jpg", 1 );
	if(!g_srcImage.data ) { printf("读取图片错误！ \n"); return -1; }  

	imshow("原始图",g_srcImage);
	g_srcImage1=g_srcImage.clone( );

	cvtColor( g_srcImage1, g_grayImage, COLOR_BGR2GRAY );

	namedWindow( WINDOW_NAME1, WINDOW_AUTOSIZE );
	createTrackbar( "阈值: ", WINDOW_NAME1, &thresh, max_thresh, on_CornerHarris );

	on_CornerHarris( 0, 0 );

	waitKey(0);
	return(0);
}

void on_CornerHarris( int, void* )
{
	//---------------------------【1】定义一些局部变量-----------------------------
	Mat dstImage;//目标图
	Mat normImage;//归一化后的图
	Mat scaledImage;//线性变换后的八位无符号整型的图

	//---------------------------【2】初始化---------------------------------------
	//置零当前需要显示的两幅图，即清除上一次调用此函数时他们的值
	dstImage = Mat::zeros( g_srcImage.size(), CV_32FC1 );
	g_srcImage1=g_srcImage.clone( );

	//---------------------------【3】正式检测-------------------------------------
	//进行角点检测
	cornerHarris( g_grayImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT );

	// 归一化与转换
	normalize( dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
	convertScaleAbs( normImage, scaledImage );//将归一化后的图线性变换成8位无符号整型 

	//---------------------------【4】进行绘制-------------------------------------
	// 将检测到的，且符合阈值条件的角点绘制出来
	for( int j = 0; j < normImage.rows ; j++ )
	{ for( int i = 0; i < normImage.cols; i++ )
	{
		if( (int) normImage.at<float>(j,i) > thresh+80 )
		{
			circle( g_srcImage1, Point( i, j ), 5,  Scalar(10,10,255), 2, 8, 0 );
			circle( scaledImage, Point( i, j ), 5,  Scalar(0,10,255), 2, 8, 0 );
		}
	}
	}
	//---------------------------【4】显示最终效果---------------------------------
	imshow( WINDOW_NAME1, g_srcImage1 );
	imshow( WINDOW_NAME2, scaledImage );

}


