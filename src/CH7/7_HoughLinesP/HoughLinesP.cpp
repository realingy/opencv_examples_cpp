#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"

using namespace cv;
using namespace std;

int main()
{
	Mat srcImage = imread(MediaPath + "cbd.jpg");
	imshow("【原始图】", srcImage);  

	Mat midImage,dstImage;

	Canny(srcImage, midImage, 50, 200, 3); //进行一此canny边缘检测
	cvtColor(midImage,dstImage, CV_GRAY2BGR); //转化边缘检测后的图为灰度图

	// 进行霍夫线变换
	vector<Vec4i> lines; //定义一个矢量结构lines用于存放得到的线段矢量集合
	HoughLinesP(midImage, lines, 1, CV_PI/180, 80, 50, 10);

	// 依次在图中绘制出每条线段
	for(size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186,88,255), 1, LINE_AA);
	}

	imshow("【边缘检测后的图】", midImage);  
	imshow("【效果图】", dstImage);  

	waitKey(0);

	return 0;
}


