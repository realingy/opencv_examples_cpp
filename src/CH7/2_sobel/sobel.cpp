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

int main()
{
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y,dst;

	Mat src = imread(MediaPath + "girl2.jpg");

	imshow("��ԭʼͼ��sobel��Ե���", src); 

	// ��X�����ݶ�
	Sobel( src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT );
	convertScaleAbs( grad_x, abs_grad_x );
	imshow("��Ч��ͼ�� X����Sobel", abs_grad_x); 

	// ��Y�����ݶ�
	Sobel( src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT );
	convertScaleAbs( grad_y, abs_grad_y );
	imshow("��Ч��ͼ��Y����Sobel", abs_grad_y); 

	// �ϲ��ݶ�(����)
	addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst );
	imshow("��Ч��ͼ�����巽��Sobel", dst); 

	waitKey(0); 
	return 0; 
}



