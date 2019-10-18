#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"

using namespace cv;

int main()
{
	Mat src, src_gray, dst, abs_dst;

	src = imread(MediaPath + "lady.jpg");

	imshow("��ԭʼͼ��ͼ��Laplace�任", src); 

	// ʹ�ø�˹�˲���������
	GaussianBlur(src, src, Size(3,3), 0, 0, BORDER_DEFAULT);

	cvtColor(src, src_gray, COLOR_RGB2GRAY);

	// ʹ��Laplace����
	Laplacian(src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);

	// �������ֵ���������ת����8λ
	convertScaleAbs(dst, abs_dst);

	imshow("��Ч��ͼ��ͼ��Laplace�任", abs_dst);

	waitKey(0); 

	return 0; 
}