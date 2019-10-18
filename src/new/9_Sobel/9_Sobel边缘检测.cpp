#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include "path.h"

using namespace cv;
using namespace std;

/******************************************************************************************************************************************
Sobel����������ͼ���Ե���������Ҫ������֮һ���ڻ���ѧϰ������ý�塢������Ӿ�����Ϣ�Ƽ��������ž������ص����á�
�ڼ����ϣ�����һ����ɢ��һ�ײ�����ӣ���������ͼ�����Ⱥ�����һ���ݶ�֮����ֵ����ͼ����κ�һ��ʹ�ô����ӣ���������õ��Ӧ���ݶ�ʸ�������䷨ʸ����
******************************************************************************************************************************************/

/*********************************************************************************************************/
/*     ��sobel���ӶԻҶ�ͼ������˲�           */

int factorial(int n)
{
	// factorial()����ʵ�ֽ׳�
	int fac = 1;
	if (n == 0)
	{
		return fac;
	}
	for (int i = 1; i <= n; ++i)
	{
		fac *= i;
	}
	return fac;
}

//  getPascalSmooth()������������sobelƽ������
Mat getPascalSmooth(int n)
{
	Mat pascalSmooth = Mat::zeros(Size(n, 1), CV_32FC1);
	for (int i = 0; i < n; ++i)
	{
		pascalSmooth.at<float>(0, i) = float(factorial(n - 1) / (factorial(i)*factorial(n - 1 - i)));

	}
	return pascalSmooth;
}

//  getPascalDiff()������������sobel�������
Mat getPascalDiff(int n)
{
	Mat pascalDiff = Mat::zeros(Size(n, 1), CV_32FC1);
	Mat pascalSmooth_previous = getPascalSmooth(n - 1);
	for (int i = 0; i < n; ++i)
	{
		if (i == 0)
		{
			pascalDiff.at<float>(0, i) = 1;
		}
		else if (i == n - 1)
		{
			pascalDiff.at<float>(0, i) = -1;
		}
		else
		{
			pascalDiff.at<float>(0, i) = pascalSmooth_previous.at<float>(0, i) - pascalSmooth_previous.at<float>(0, i - 1);
		}
	}
	return  pascalDiff;
}

void conv2D(InputArray src, InputArray kernel, OutputArray dst, int ddepth, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	//  conv2D()�����������same�������
	Mat kernelFlip;
	flip(kernel, kernelFlip, -1);    // �������ĵ�һ�������������ʱ�뷭ת180��
	filter2D(src, dst, ddepth, kernelFlip, anchor, 0.0, borderType);   //�������ĵڶ���
}

void sepConv2D_Y_X(InputArray src, OutputArray  src_kerY_kerX, int ddepth, InputArray kernelY, InputArray kernelX, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	// ���ڿɷ������ɢ��ά������Ƚ��д�ֱ�����ϵľ�����ٽ���ˮƽ�����ϵľ��
	Mat src_kerY;
	conv2D(src, kernelY, src_kerY, ddepth, anchor, borderType);   // ��������봹ֱ�����ϵľ���˵ľ��
	conv2D(src_kerY, kernelX, src_kerY_kerX, ddepth, anchor, borderType);  // �Ѵ�����õ��ľ�������ˮƽ�����ϵľ���˾��
}

void sepConv2D_X_Y(InputArray src, OutputArray  src_kerX_kerY, int ddepth, InputArray kernelX, InputArray kernelY, Point anchor = Point(-1, -1), int borderType = BORDER_DEFAULT)
{
	// ���ڿɷ������ɢ��ά������Ƚ���ˮƽ�����ϵľ�����ٽ��д�ֱ�����ϵľ��
	Mat src_kerX;
	conv2D(src, kernelX, src_kerX, ddepth, anchor, borderType);   // ���������ˮƽ�����ϵľ���˵ľ��
	conv2D(src_kerX, kernelY, src_kerX_kerY, ddepth, anchor, borderType);  // �Ѵ�����õ��ľ������ʹ�ֱ�����ϵľ���˾��
}

// �Լ�ʵ��Sobel����
// sobel�����������ͼ��ҶȾ�����sobel�˵ľ�� 
Mat sobel(Mat& image, int x_flag, int y_flag, int winSize, int borderType)
{
	CV_Assert(winSize >= 3 && winSize % 2 == 1);   // sobel����˵Ĵ��ڴ�СΪ����3������
	Mat pascalSmooth = getPascalSmooth(winSize);   // sobelƽ������
	//Mat pascalDiff = getPascalSmooth(winSize);     // sobel�������
	Mat pascalDiff = getPascalDiff(winSize);     // sobel�������
	Mat image_con_sobel;                           // �������
	if (x_flag != 0)
	{
		sepConv2D_Y_X(image, image_con_sobel, CV_32FC1, pascalSmooth.t(), pascalDiff, Point(-1, -1), borderType);     //�Ƚ���һά��ֱ�����ϵ�ƽ�����ٽ���һάˮƽ�����ϵĲ�֣���ͼ����sobel_x���о������
	}
	if (x_flag == 0 && y_flag != 0)
	{
		sepConv2D_X_Y(image, image_con_sobel, CV_32FC1, pascalSmooth, pascalDiff.t(), Point(-1, -1), borderType);    //�Ƚ���һάˮƽ�����ϵ�ƽ�����ٽ���һά��ֱ�����ϵĲ��,��ͼ����sobel_y���о������
	}
	return  image_con_sobel;
}
/********************************************************************************************************************/

// ������
int main()
{
	const Mat src_img = imread(MediaPath + "1.jpg");
	if (src_img.empty())
	{
		printf("could not load image...\n");
		return -1;
	}

	namedWindow("ԭͼ��", CV_WINDOW_AUTOSIZE);
	imshow("ԭͼ��", src_img);

	// ����ɫͼת��Ϊ�Ҷ�ͼ������OpenCV�ṩ��cvtColor�ӿ�
	Mat gray_img;
	cvtColor(src_img, gray_img, CV_BGR2GRAY);
	namedWindow("�Ҷ�ͼ", CV_WINDOW_AUTOSIZE);
	imshow("�Ҷ�ͼ", gray_img);

	// ��sobel���Ӽ����ͼ���ˮƽ�ʹ�ֱ�����ϵĲ��
	Mat image_con_sobel_Ix, image_con_sobel_Iy;
	//image_con_sobel_Ix = sobel(gray_img, 1, 0, 3, BORDER_DEFAULT); //�⺯��
	//image_con_sobel_Iy = sobel(gray_img, 0, 1, 3, BORDER_DEFAULT); //�⺯��
	Sobel(gray_img, image_con_sobel_Ix, CV_64F, 1, 0, 3);
	Sobel(gray_img, image_con_sobel_Iy, CV_64F, 0, 1, 3);

	// ˮƽ����ʹ�ֱ�����ϵı�Եǿ��
	// ��������ת������Եǿ�ȵĻҶȼ���ʾ
	Mat scale_sobel_Ix, scale_sobel_Iy;
	convertScaleAbs(image_con_sobel_Ix, scale_sobel_Ix);              //  ת��Ϊ8λ�Ҷȼ���ʾ
	convertScaleAbs(image_con_sobel_Iy, scale_sobel_Iy);
	imshow("��ֱ����ı�Ե", scale_sobel_Ix);
	imshow("ˮƽ����ı�Ե", scale_sobel_Iy);

	waitKey(0);
	return 0;
}


