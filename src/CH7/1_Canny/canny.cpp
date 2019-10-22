#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"

using namespace cv;

//第一步、使用高斯平滑滤波器（或者均值滤波器）进行平滑去噪（而且还可以抑制细节）
//第二步、计算梯度幅值和方向
//第三步、非极大值抑制
//第四步、滞后阈值(推荐的高低阈值比为2:1或者3:1)

int main()
{
	Mat srcImage = imread(MediaPath + "orange.jpg");

	imshow("【原始图】Canny边缘检测", srcImage); 

	Mat edge,grayImage;

	Mat dstImage( srcImage.size(), srcImage.type() );
	// 将g_dstImage内的所有元素设置为0
	dstImage = Scalar::all(0);

	// 转换成灰度图
	cvtColor( srcImage, grayImage, CV_BGR2GRAY );

	// 平滑降噪
	blur( grayImage, edge, Size(3,3) );

	// 运行Canny算子
	Canny(edge, edge, 3, 9);

	// 使用Canny算子输出的边缘图作为掩码，将原图拷到目标图中
	srcImage.copyTo(dstImage, edge);

	imshow("【效果图】Canny边缘检测", dstImage); 

	waitKey(0); 

	return 0; 
}
