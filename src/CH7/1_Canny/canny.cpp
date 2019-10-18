#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"

using namespace cv;

int main()
{
	Mat srcImage = imread(MediaPath + "orange.jpg");
	Mat srcImage1 = srcImage.clone();

	imshow("【原始图】Canny边缘检测", srcImage); 

	Mat dstImage,edge,grayImage;

	dstImage.create( srcImage1.size(), srcImage1.type() );
	cvtColor( srcImage1, grayImage, COLOR_BGR2GRAY );

	// 先用使用3x3内核来降噪
	blur( grayImage, edge, Size(3,3) );

	// 运行Canny算子
	Canny(edge, edge, 3, 9, 3);

	// 将g_dstImage内的所有元素设置为0
	dstImage = Scalar::all(0);

	// 使用Canny算子输出的边缘图g_cannyDetectedEdges作为掩码，来将原图g_srcImage拷到目标图g_dstImage中
	srcImage1.copyTo(dstImage, edge);

	imshow("【效果图】Canny边缘检测", dstImage); 

	waitKey(0); 

	return 0; 
}
