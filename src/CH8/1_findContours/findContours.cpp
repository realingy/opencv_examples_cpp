// 基础轮廓查找—findContours+drawContours
#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "path.h"
using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
	Mat srcImage=imread(MediaPath+"findContours.jpg", 0);
	imshow("原始图",srcImage);

	Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);

	srcImage = srcImage > 119;
	imshow( "取阈值后的原始图", srcImage );

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	// 查找轮廓
	findContours( srcImage, contours, hierarchy,RETR_CCOMP, CHAIN_APPROX_SIMPLE );

	// 遍历所有顶层的轮廓， 以随机颜色绘制出每个连接组件颜色
	int index = 0;
	for( ; index >= 0; index = hierarchy[index][0] )
	{
		Scalar color( rand()&255, rand()&255, rand()&255 );
		drawContours( dstImage, contours, index, color, FILLED, 8, hierarchy );
	}

	imshow( "轮廓图", dstImage );

	waitKey(0);
	return 0;
}