// 霍夫圆变换-检测圆
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"
using namespace cv;
using namespace std;

int main( )
{
	Mat srcImage = imread(MediaPath + "houghcircle.jpg");
	Mat midImage,dstImage;
	if ( !srcImage.data )
	{
		cout << "图像打开错误!\n";
		return -1;
	}

	imshow("【原始图】", srcImage);  

	cvtColor(srcImage,midImage, COLOR_BGR2GRAY); //转化边缘检测后的图为灰度图
	GaussianBlur( midImage, midImage, Size(9, 9), 2, 2 );

	// 进行霍夫圆变换
	vector<Vec3f> circles;
	HoughCircles( midImage, circles, HOUGH_GRADIENT,1.5, 10, 200, 100, 0, 0 );

	// 依次在图中绘制出圆
	for( size_t i = 0; i < circles.size(); i++ )
	{
		//参数定义
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//绘制圆心
		circle( srcImage, center, 3, Scalar(0,255,0), -1, 8, 0 );
		//绘制圆轮廓
		circle( srcImage, center, radius, Scalar(155,50,255), 3, 8, 0 );
	}

	imshow("【效果图】", srcImage);  

	waitKey(0);  

	return 0;  
}
