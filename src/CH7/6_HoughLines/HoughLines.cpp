#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"

using namespace cv;
using namespace std;

//霍夫线变换进行线检测
/********************************************************************************************
void HoughLines(InputArray image, //输入图像，8位单通道的二值图像；输入图像可能被函数修改。
	OutputArray lines, //直线的输出向量，每一条直线由两个元素的向量（rho,theta）表示
	double rho, double theta, //直线搜索时的步进尺寸
	int threshold, //最小投票数
	double srn = 0, double stn = 0, //默认
	double min_theta = 0, double max_theta = CV_PI); //默认
********************************************************************************************/

int main()
{
	Mat srcImage = imread(MediaPath + "cbd.jpg");
	imshow("【原始图】", srcImage);  

	Mat midImage, dstImage;

	Canny(srcImage, midImage, 50, 200, 3); //进行一此canny边缘检测
	cvtColor(midImage, dstImage, CV_GRAY2BGR); //转化边缘检测后的图为灰度图

	// 进行霍夫线变换
	vector<Vec2f> lines; //定义一个矢量结构lines用于存放得到的线段矢量集合
	HoughLines(midImage, lines, 1, CV_PI/180, 150, 0, 0);

	// 依次在图中绘制出每条线段
	for( size_t i = 0; i < lines.size(); i++ )
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000*(-b));
		pt1.y = cvRound(y0 + 1000*(a));
		pt2.x = cvRound(x0 - 1000*(-b));
		pt2.y = cvRound(y0 - 1000*(a));
		line( dstImage, pt1, pt2, Scalar(55,100,195), 1, LINE_AA);
	}

	imshow("【边缘检测后的图】", midImage);  

	imshow("【效果图】", dstImage);  

	waitKey(0);

	return 0;  
}

