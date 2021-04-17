#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"

using namespace cv;

//第一步、分别在x和y两个方向上求导
//第二步、检测水平方向上的边缘，内核为
//[-1  0 +1]
//[-2  0 +2]
//[-1  0 +1]
//第三步、检测垂直方向上的边缘，内核为
//[-1 -2 -1]
//[ 0  0  0]
//[+1 +2 +1]
//第四步、合并梯度

/*
int main()
{
	Mat grad_x, grad_y, dst;

	Mat src = imread(MediaPath + "girl2.jpg");

	Mat gray;
	cvtColor( src, gray, CV_BGR2GRAY );

	imshow("【原始图】sobel边缘检测", src); 

	// 求X方向梯度
	// Sobel( src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT );
	Sobel( gray, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT );
	convertScaleAbs( grad_x, grad_x );
	imshow("【效果图】 X方向Sobel", grad_x); 

	// 求Y方向梯度
	Sobel(gray, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs( grad_y, grad_y );
	imshow("【效果图】Y方向Sobel", grad_y); 

	// 合并梯度(近似)
	addWeighted(grad_x, 0.5, grad_y, 0.5, 0, dst);
	imshow("【效果图】整体方向Sobel", dst); 

	imwrite("sobel.jpg", dst);

	waitKey(0); 
	return 0; 
}
*/

void SobelGradDirection(const Mat imageSource, Mat& imageSobelX, Mat& imageSobelY)
{
	imageSobelX = Mat::zeros(imageSource.size(), CV_32SC1);
	imageSobelY = Mat::zeros(imageSource.size(), CV_32SC1);
	uchar* P = imageSource.data;
	uchar* PX = imageSobelX.data;
	uchar* PY = imageSobelY.data;

	int step = imageSource.step;
	int stepXY = imageSobelX.step;
	int k = 0;
	int m = 0;
	int n = 0;

	for (int i = 1; i < (imageSource.rows - 1); i++)
	{
		for (int j = 1; j < (imageSource.cols - 1); j++)
		{
			//通过指针遍历图像上每一个像素 
			double gradY = P[(i - 1) * step + j + 1] + P[i * step + j + 1] * 2 + P[(i + 1) * step + j + 1] - P[(i - 1) * step + j - 1] - P[i * step + j - 1] * 2 - P[(i + 1) * step + j - 1];
			PY[i * stepXY + j * (stepXY / step)] = abs(gradY);

			double gradX = P[(i + 1) * step + j - 1] + P[(i + 1) * step + j] * 2 + P[(i + 1) * step + j + 1] - P[(i - 1) * step + j - 1] - P[(i - 1) * step + j] * 2 - P[(i - 1) * step + j + 1];
			PX[i * stepXY + j * (stepXY / step)] = abs(gradX);
		}
	}
	convertScaleAbs(imageSobelX, imageSobelX);
	convertScaleAbs(imageSobelY, imageSobelY);
}

void SobelAmplitude(const Mat imageGradX, const Mat imageGradY, Mat& SobelAmpXY)
{
	SobelAmpXY = Mat::zeros(imageGradX.size(), CV_32FC1);
	for (int i = 0; i < SobelAmpXY.rows; i++)
	{
		for (int j = 0; j < SobelAmpXY.cols; j++)
		{
			SobelAmpXY.at<float>(i, j) = sqrt(imageGradX.at<uchar>(i, j) * imageGradX.at<uchar>(i, j) + imageGradY.at<uchar>(i, j) * imageGradY.at<uchar>(i, j));
		}
	}
	convertScaleAbs(SobelAmpXY, SobelAmpXY);
}

int main()
{
	Mat grad_x, grad_y, dst;

	Mat src = imread(MediaPath + "girl2.jpg");

	Mat gray;
	cvtColor( src, gray, CV_BGR2GRAY );

	imshow("【原始图】sobel边缘检测", src);

	SobelGradDirection(gray, grad_x, grad_y);
	imshow("【效果图】 X方向Sobel", grad_x);
	imshow("【效果图】Y方向Sobel", grad_y);

	// 合并梯度(近似)
	SobelAmplitude(grad_x, grad_y, dst);
	imshow("【效果图】整体方向Sobel", dst);

	imwrite("sobel.jpg", dst);

	waitKey(0);
	return 0;
}

