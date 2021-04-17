#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"

using namespace cv;

//��һ�����ֱ���x��y������������
//�ڶ��������ˮƽ�����ϵı�Ե���ں�Ϊ
//[-1  0 +1]
//[-2  0 +2]
//[-1  0 +1]
//����������ⴹֱ�����ϵı�Ե���ں�Ϊ
//[-1 -2 -1]
//[ 0  0  0]
//[+1 +2 +1]
//���Ĳ����ϲ��ݶ�

/*
int main()
{
	Mat grad_x, grad_y, dst;

	Mat src = imread(MediaPath + "girl2.jpg");

	Mat gray;
	cvtColor( src, gray, CV_BGR2GRAY );

	imshow("��ԭʼͼ��sobel��Ե���", src); 

	// ��X�����ݶ�
	// Sobel( src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT );
	Sobel( gray, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT );
	convertScaleAbs( grad_x, grad_x );
	imshow("��Ч��ͼ�� X����Sobel", grad_x); 

	// ��Y�����ݶ�
	Sobel(gray, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs( grad_y, grad_y );
	imshow("��Ч��ͼ��Y����Sobel", grad_y); 

	// �ϲ��ݶ�(����)
	addWeighted(grad_x, 0.5, grad_y, 0.5, 0, dst);
	imshow("��Ч��ͼ�����巽��Sobel", dst); 

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
			//ͨ��ָ�����ͼ����ÿһ������ 
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

	imshow("��ԭʼͼ��sobel��Ե���", src);

	SobelGradDirection(gray, grad_x, grad_y);
	imshow("��Ч��ͼ�� X����Sobel", grad_x);
	imshow("��Ч��ͼ��Y����Sobel", grad_y);

	// �ϲ��ݶ�(����)
	SobelAmplitude(grad_x, grad_y, dst);
	imshow("��Ч��ͼ�����巽��Sobel", dst);

	imwrite("sobel.jpg", dst);

	waitKey(0);
	return 0;
}

