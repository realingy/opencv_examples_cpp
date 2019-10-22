// 创建轮廓边界框
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "path.h"

using namespace cv;
using namespace std;

#define WINDOW_NAME1 "【原始图窗口】" //为窗口标题定义的宏 
#define WINDOW_NAME2 "【效果图窗口】" //为窗口标题定义的宏 

Mat g_srcImage;
Mat g_grayImage;
int g_nThresh = 50; //阈值
int g_nMaxThresh = 255; //阈值最大值
RNG g_rng(12345); //随机数生成器

void on_ContoursChange(int, void* );

int main()
{
	g_srcImage = imread(MediaPath+"approxPolyDP.jpg", 1);
	if(!g_srcImage.data)
	{
		printf("读取图片错误！\n");
		return -1;
	}  

	cvtColor(g_srcImage, g_grayImage, CV_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3,3));

	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, g_srcImage);

	createTrackbar("阈值:", WINDOW_NAME1, &g_nThresh, g_nMaxThresh, on_ContoursChange);
	on_ContoursChange(0, 0);

	waitKey(0);

	return(0);
}

void on_ContoursChange(int, void* )
{
	// 定义一些参数
	Mat threshold_output;
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	// 使用Threshold检测边缘
	threshold(g_grayImage, threshold_output, g_nThresh, 255, THRESH_BINARY);

	// 找出轮廓
	findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	// 多边形逼近轮廓 + 获取矩形和圆形边界框
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());

	// 一个循环，遍历所有部分，进行本程序最核心的操作
	for(unsigned int i = 0; i < contours.size(); i++)
	{ 
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);//用指定精度逼近多边形曲线 
		boundRect[i] = boundingRect(Mat(contours_poly[i]));//计算点集的最外面（up-right）矩形边界
		minEnclosingCircle(contours_poly[i], center[i], radius[i]);//对给定的 2D点集，寻找最小面积的包围圆形 
	}

	// 绘制多边形轮廓 + 包围的矩形框 + 圆形框
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for(int unsigned i = 0; i<contours.size( ); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0,255), g_rng.uniform(0,255));//随机设置颜色
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());//绘制轮廓
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);//绘制矩形
		circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);//绘制圆
	}

	namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME2, drawing);
}


