#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"

using namespace cv;

//��һ����ʹ�ø�˹ƽ���˲��������߾�ֵ�˲���������ƽ��ȥ�루���һ���������ϸ�ڣ�
//�ڶ����������ݶȷ�ֵ�ͷ���
//���������Ǽ���ֵ����
//���Ĳ����ͺ���ֵ(�Ƽ��ĸߵ���ֵ��Ϊ2:1����3:1)

int main()
{
	Mat srcImage = imread(MediaPath + "orange.jpg");

	imshow("��ԭʼͼ��Canny��Ե���", srcImage); 

	Mat edge,grayImage;

	Mat dstImage( srcImage.size(), srcImage.type() );
	// ��g_dstImage�ڵ�����Ԫ������Ϊ0
	dstImage = Scalar::all(0);

	// ת���ɻҶ�ͼ
	cvtColor( srcImage, grayImage, CV_BGR2GRAY );

	// ƽ������
	blur( grayImage, edge, Size(3,3) );

	// ����Canny����
	Canny(edge, edge, 3, 9);

	// ʹ��Canny��������ı�Եͼ��Ϊ���룬��ԭͼ����Ŀ��ͼ��
	srcImage.copyTo(dstImage, edge);

	imshow("��Ч��ͼ��Canny��Ե���", dstImage); 

	waitKey(0); 

	return 0; 
}
