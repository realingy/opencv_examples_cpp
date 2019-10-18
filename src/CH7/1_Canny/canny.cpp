#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"

using namespace cv;

int main()
{
	Mat srcImage = imread(MediaPath + "orange.jpg");
	Mat srcImage1 = srcImage.clone();

	imshow("��ԭʼͼ��Canny��Ե���", srcImage); 

	Mat dstImage,edge,grayImage;

	dstImage.create( srcImage1.size(), srcImage1.type() );
	cvtColor( srcImage1, grayImage, COLOR_BGR2GRAY );

	// ����ʹ��3x3�ں�������
	blur( grayImage, edge, Size(3,3) );

	// ����Canny����
	Canny(edge, edge, 3, 9, 3);

	// ��g_dstImage�ڵ�����Ԫ������Ϊ0
	dstImage = Scalar::all(0);

	// ʹ��Canny��������ı�Եͼg_cannyDetectedEdges��Ϊ���룬����ԭͼg_srcImage����Ŀ��ͼg_dstImage��
	srcImage1.copyTo(dstImage, edge);

	imshow("��Ч��ͼ��Canny��Ե���", dstImage); 

	waitKey(0); 

	return 0; 
}
