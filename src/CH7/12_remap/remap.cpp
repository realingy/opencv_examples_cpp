// remap�����÷�ʾ��
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "path.h"
using namespace cv;

int main()
{
	Mat srcImage, dstImage;
	Mat map_x, map_y;

	srcImage = imread(MediaPath+"1.jpg", 1);
	if(!srcImage.data ) { printf("��ȡͼƬ���� \n"); return -1; }  

	imshow("ԭʼͼ",srcImage);

	dstImage.create( srcImage.size(), srcImage.type() );
	map_x.create( srcImage.size(), CV_32FC1 );
	map_y.create( srcImage.size(), CV_32FC1 );

	// �������أ��ı�map_x & map_y��ֵ
	for( int j = 0; j < srcImage.rows;j++)
	{ 
		for( int i = 0; i < srcImage.cols;i++)
		{
			//�ı�map_x & map_y��ֵ. 
			map_x.at<float>(j,i) = static_cast<float>(i);
			map_y.at<float>(j,i) = static_cast<float>(srcImage.rows - j);
		} 
	}

	// ������ӳ�����
	remap( srcImage, dstImage, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0,0, 0) );

	imshow( "�����򴰿ڡ�", dstImage );
	waitKey();

	return 0;
}

