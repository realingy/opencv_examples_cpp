#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

#include "path.h"

using namespace cv;
using namespace std;

#define WINDOW_NAME "【程序窗口】"

int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage, g_grayImage, g_dstImage;

void on_Threshold( int, void* );//回调函数

int main( )
{
	// system("color 1F"); 

	g_srcImage = imread(MediaPath + "lake.jpg");
	if(!g_srcImage.data ) { 
		printf("读取图片错误！ \n");
		return -1;
	}  

	imshow("原始图",g_srcImage);

	cvtColor( g_srcImage, g_grayImage, CV_RGB2GRAY );

	// namedWindow( WINDOW_NAME, WINDOW_AUTOSIZE );

	createTrackbar( "模式", WINDOW_NAME, &g_nThresholdType, 4, on_Threshold );
	createTrackbar( "参数值", WINDOW_NAME, &g_nThresholdValue, 255, on_Threshold );

	on_Threshold( 0, 0 );

	// 轮询等待用户按键，如果ESC键按下则退出程序
	while(1)
	{
		int key;
		key = waitKey( 20 );
		if( (char)key == 27 ){ 
			break;
		}
	}

}

void on_Threshold( int, void* )
{
	//调用阈值函数
	threshold(g_grayImage,g_dstImage,g_nThresholdValue,255,g_nThresholdType);

	imshow( WINDOW_NAME, g_dstImage );
}

