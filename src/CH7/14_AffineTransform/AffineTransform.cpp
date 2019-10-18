#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "path.h"
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "��ԭʼͼ���ڡ�"					//Ϊ���ڱ��ⶨ��ĺ� 
#define WINDOW_NAME2 "������Warp���ͼ��"				//Ϊ���ڱ��ⶨ��ĺ� 
#define WINDOW_NAME3 "������Warp��Rotate���ͼ��"     //Ϊ���ڱ��ⶨ��ĺ� 

int main(  )
{
	system("color 1F"); 

	Point2f srcTriangle[3];
	Point2f dstTriangle[3];

	//����һЩMat����
	Mat rotMat( 2, 3, CV_32FC1 );
	Mat warpMat( 2, 3, CV_32FC1 );
	Mat srcImage, dstImage_warp, dstImage_warp_rotate;

	srcImage = imread( MediaPath+"1.jpg", 1 );
	if(!srcImage.data ) { printf("��ȡͼƬ���� \n"); return -1; } 
	// ����Ŀ��ͼ��Ĵ�С��������Դͼ��һ��
	dstImage_warp = Mat::zeros( srcImage.rows, srcImage.cols, srcImage.type() );

	// ����Դͼ���Ŀ��ͼ���ϵ�������Լ������任
	srcTriangle[0] = Point2f( 0,0 );
	srcTriangle[1] = Point2f( static_cast<float>(srcImage.cols - 1), 0 );
	srcTriangle[2] = Point2f( 0, static_cast<float>(srcImage.rows - 1 ));

	dstTriangle[0] = Point2f( static_cast<float>(srcImage.cols*0.0), static_cast<float>(srcImage.rows*0.33));
	dstTriangle[1] = Point2f( static_cast<float>(srcImage.cols*0.65), static_cast<float>(srcImage.rows*0.35));
	dstTriangle[2] = Point2f( static_cast<float>(srcImage.cols*0.15), static_cast<float>(srcImage.rows*0.6));

	// ��÷���任
	warpMat = getAffineTransform( srcTriangle, dstTriangle );

	// ��Դͼ��Ӧ�øո���õķ���任
	warpAffine( srcImage, dstImage_warp, warpMat, dstImage_warp.size() );

	// ��ͼ��������ź�����ת
	// ������ͼ���е�˳ʱ����ת50����������Ϊ0.6����ת����
	Point center = Point( dstImage_warp.cols/2, dstImage_warp.rows/2 );
	double angle = -50.0;
	double scale = 0.6;
	// ͨ���������תϸ����Ϣ�����ת����
	rotMat = getRotationMatrix2D( center, angle, scale );
	// ��ת�����ź��ͼ��
	warpAffine( dstImage_warp, dstImage_warp_rotate, rotMat, dstImage_warp.size() );

	imshow( WINDOW_NAME1, srcImage );
	imshow( WINDOW_NAME2, dstImage_warp );
	imshow( WINDOW_NAME3, dstImage_warp_rotate );

	// �ȴ��û������ⰴ���˳�����
	waitKey(0);

	return 0;
}



