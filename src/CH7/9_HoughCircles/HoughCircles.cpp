// ����Բ�任-���Բ
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"
using namespace cv;
using namespace std;

//����Բ�任����Բ���
/**********************************************************************************************
CV_EXPORTS_W void HoughCircles( InputArray image,
								OutputArray circles,
								int method,
								double dp,
								double minDist,
								double param1 = 100,
								double param2 = 100,
								int minRadius = 0,
								int maxRadius = 0 );
**********************************************************************************************/

int main()
{
	Mat srcImage = imread(MediaPath + "houghcircle.jpg");
	Mat midImage,dstImage;
	if ( !srcImage.data )
	{
		cout << "ͼ��򿪴���!\n";
		return -1;
	}

	imshow("��ԭʼͼ��", srcImage);  

	cvtColor(srcImage,midImage, COLOR_BGR2GRAY); //ת����Ե�����ͼΪ�Ҷ�ͼ
	GaussianBlur( midImage, midImage, Size(9, 9), 2, 2 );

	// ���л���Բ�任
	vector<Vec3f> circles;
	HoughCircles( midImage, circles, HOUGH_GRADIENT,1.5, 10, 200, 100, 0, 0 );

	// ������ͼ�л��Ƴ�Բ
	for( size_t i = 0; i < circles.size(); i++ )
	{
		//��������
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//����Բ��
		circle( srcImage, center, 3, Scalar(0,255,0), -1, 8, 0 );
		//����Բ����
		circle( srcImage, center, radius, Scalar(155,50,255), 3, 8, 0 );
	}

	imshow("��Ч��ͼ��", srcImage);  

	waitKey(0);  

	return 0;  
}
