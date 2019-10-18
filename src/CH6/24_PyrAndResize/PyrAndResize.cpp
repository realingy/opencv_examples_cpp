#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"

using namespace std;
using namespace cv;

#define WINDOW_NAME "【程序窗口】"		//为窗口标题定义的宏

Mat g_srcImage, g_dstImage, g_tmpImage;

int main( )
{
	g_srcImage = imread(MediaPath + "car.jpg");
	if( !g_srcImage.data ) { printf("Oh，no，读取srcImage错误~！\n"); return false; }

	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME, g_srcImage);

	g_tmpImage = g_srcImage;
	g_dstImage = g_tmpImage;

	int key =0;

	//轮询获取按键信息
	while(1)
	{
		key=waitKey(9) ;//读取键值到key变量中

		//根据key变量的值，进行不同的操作
		switch(key)
		{
			//======================【程序退出相关键值处理】=======================  
		case 27://按键ESC
			return 0;
			break; 
		case 'q'://按键Q
			return 0;
			break; 
			//======================【图片放大相关键值处理】=======================  
		case 'a'://按键A按下，调用pyrUp函数
			pyrUp( g_tmpImage, g_dstImage, Size( g_tmpImage.cols*2, g_tmpImage.rows*2 ) );
			printf( ">检测到按键【A】被按下，开始进行基于【pyrUp】函数的图片放大：图片尺寸×2 \n" );		
			break; 
		case 'w'://按键W按下，调用resize函数
			resize(g_tmpImage,g_dstImage,Size( g_tmpImage.cols*2, g_tmpImage.rows*2 ));
			printf( ">检测到按键【W】被按下，开始进行基于【resize】函数的图片放大：图片尺寸×2 \n" );		
			break; 
		case '1'://按键1按下，调用resize函数
			resize(g_tmpImage,g_dstImage,Size( g_tmpImage.cols*2, g_tmpImage.rows*2 ));
			printf( ">检测到按键【1】被按下，开始进行基于【resize】函数的图片放大：图片尺寸×2 \n" );
			break; 
		case '3': //按键3按下，调用pyrUp函数
			pyrUp( g_tmpImage, g_dstImage, Size( g_tmpImage.cols*2, g_tmpImage.rows*2 ));
			printf( ">检测到按键【3】被按下，开始进行基于【pyrUp】函数的图片放大：图片尺寸×2 \n" );
			break; 
			//======================【图片缩小相关键值处理】=======================  
		case 'd': //按键D按下，调用pyrDown函数
			pyrDown( g_tmpImage, g_dstImage, Size( g_tmpImage.cols/2, g_tmpImage.rows/2 ));
			printf( ">检测到按键【D】被按下，开始进行基于【pyrDown】函数的图片缩小：图片尺寸/2\n" );
			break; 
		case  's' : //按键S按下，调用resize函数
			resize(g_tmpImage,g_dstImage, Size( g_tmpImage.cols/2, g_tmpImage.rows/2));
			printf(">检测到按键【S】被按下，开始进行基于【resize】函数的图片缩小：图片尺寸/2\n");
			break; 
		case '2'://按键2按下，调用resize函数
			resize(g_tmpImage,g_dstImage, Size( g_tmpImage.cols/2, g_tmpImage.rows/2 ));
			printf(">检测到按键【2】被按下，开始进行基于【resize】函数的图片缩小：图片尺寸/2\n");
			break; 
		case '4': //按键4按下，调用pyrDown函数
			pyrDown(g_tmpImage, g_dstImage, Size( g_tmpImage.cols/2, g_tmpImage.rows/2 ));
			printf(">检测到按键【4】被按下，开始进行基于【pyrDown】函数的图片缩小：图片尺寸/2\n");
			break; 
		}

		imshow( WINDOW_NAME, g_dstImage );

		g_tmpImage = g_dstImage;
	}

	return 0;
}

