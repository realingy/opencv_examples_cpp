// 实现多种重映射综合示例
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "path.h"
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME "【程序窗口】"        //为窗口标题定义的宏 

Mat g_srcImage, g_dstImage;
Mat g_map_x, g_map_y;

int update_map( int key);

int main( int argc, char** argv )
{
	system("color 5F"); 

	g_srcImage = imread( MediaPath+"1.jpg", 1 );
	if(!g_srcImage.data ) { printf("读取图片错误！\n"); return false; }  

	imshow("原始图",g_srcImage);

	// 创建和原始图一样的效果图，x重映射图，y重映射图
	g_dstImage.create( g_srcImage.size(), g_srcImage.type() );
	g_map_x.create( g_srcImage.size(), CV_32FC1 );
	g_map_y.create( g_srcImage.size(), CV_32FC1 );

	namedWindow( WINDOW_NAME, WINDOW_AUTOSIZE );
	imshow(WINDOW_NAME,g_srcImage);

	// 轮询按键，更新map_x和map_y的值，进行重映射操作并显示效果图
	while( 1 )
	{
		//获取键盘按键  
		int key = waitKey(0);  

		//判断ESC是否按下，若按下便退出  
		if( (key & 255) == 27 )  
		{  
			cout << "程序退出...........\n";  
			break;  
		}  

		//根据按下的键盘按键来更新 map_x & map_y的值. 然后调用remap( )进行重映射
		update_map(key);
		remap( g_srcImage, g_dstImage, g_map_x, g_map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0,0, 0) );

		//显示效果图
		imshow( WINDOW_NAME, g_dstImage );
	}
	return 0;
}

// 根据按键来更新map_x与map_x的值
int update_map( int key )
{
	for( int j = 0; j < g_srcImage.rows;j++)
	{ 
		for( int i = 0; i < g_srcImage.cols;i++)
		{
			switch(key)
			{
			case '1': // 键盘【1】键按下，进行第一种重映射操作
				if( i > g_srcImage.cols*0.25 && i < g_srcImage.cols*0.75 && j > g_srcImage.rows*0.25 && j < g_srcImage.rows*0.75)
				{
					g_map_x.at<float>(j,i) = static_cast<float>(2*( i - g_srcImage.cols*0.25 ) + 0.5);
					g_map_y.at<float>(j,i) = static_cast<float>(2*( j - g_srcImage.rows*0.25 ) + 0.5);
				}
				else
				{ 
					g_map_x.at<float>(j,i) = 0;
					g_map_y.at<float>(j,i) = 0;
				}
				break;
			case '2':// 键盘【2】键按下，进行第二种重映射操作
				g_map_x.at<float>(j,i) = static_cast<float>(i);
				g_map_y.at<float>(j,i) = static_cast<float>(g_srcImage.rows - j);
				break;
			case '3':// 键盘【3】键按下，进行第三种重映射操作
				g_map_x.at<float>(j,i) = static_cast<float>(g_srcImage.cols - i);
				g_map_y.at<float>(j,i) = static_cast<float>(j);
				break;
			case '4':// 键盘【4】键按下，进行第四种重映射操作
				g_map_x.at<float>(j,i) = static_cast<float>(g_srcImage.cols - i);
				g_map_y.at<float>(j,i) = static_cast<float>(g_srcImage.rows - j);
				break;
			} 
		}
	}
	return 1;
}

