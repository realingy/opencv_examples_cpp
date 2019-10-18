//	�����ؼ��ǵ���
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include "path.h"
using namespace cv;
using namespace std;

#define WINDOW_NAME "�������ؼ��ǵ��⡿"

Mat g_srcImage, g_grayImage;
int g_maxCornerNumber = 33;
int g_maxTrackbarNumber = 500;
RNG g_rng(12345);//��ʼ�������������

void on_GoodFeaturesToTrack( int, void* )
{
	//��1���Ա���С�ڵ���1ʱ�Ĵ���
	if( g_maxCornerNumber <= 1 ) { g_maxCornerNumber = 1; }

	//��2��Shi-Tomasi�㷨��goodFeaturesToTrack�������Ĳ���׼��
	vector<Point2f> corners;
	double qualityLevel = 0.01;//�ǵ���ɽ��ܵ���С����ֵ
	double minDistance = 10;//�ǵ�֮�����С����
	int blockSize = 3;//���㵼������ؾ���ʱָ��������Χ
	double k = 0.04;//Ȩ��ϵ��
	Mat copy = g_srcImage.clone();	//����Դͼ��һ����ʱ�����У���Ϊ����Ȥ����

	//��3������Shi-Tomasi�ǵ���
	goodFeaturesToTrack( g_grayImage,//����ͼ��
		corners,//��⵽�Ľǵ���������
		g_maxCornerNumber,//�ǵ���������
		qualityLevel,//�ǵ���ɽ��ܵ���С����ֵ
		minDistance,//�ǵ�֮�����С����
		Mat(),//����Ȥ����
		blockSize,//���㵼������ؾ���ʱָ��������Χ
		false,//��ʹ��Harris�ǵ���
		k );//Ȩ��ϵ��

	//��4�����������Ϣ
	cout<<"\n\t>-------------�˴μ�⵽�Ľǵ�����Ϊ��"<<corners.size()<<endl;

	//��5�����Ƽ�⵽�Ľǵ�
	int r = 4;
	for( unsigned int i = 0; i < corners.size(); i++ )
	{ 
		//���������ɫ���Ƴ��ǵ�
		circle( copy, corners[i], r, Scalar(g_rng.uniform(0,255), g_rng.uniform(0,255),
			g_rng.uniform(0,255)), -1, 8, 0 ); 
	}

	//��6����ʾ�����£�����
	imshow( WINDOW_NAME, copy );

	//��7�������ؽǵ���Ĳ�������
	Size winSize = Size( 5, 5 );
	Size zeroZone = Size( -1, -1 );
	TermCriteria criteria = TermCriteria( TermCriteria::EPS + TermCriteria::MAX_ITER, 40, 0.001 );

	//��8������������ؽǵ�λ��
	cornerSubPix( g_grayImage, corners, winSize, zeroZone, criteria );

	//��9������ǵ���Ϣ
	for( int i = 0; i < corners.size(); i++ )
		{ cout<<" \t>>��ȷ�ǵ�����["<<i<<"]  ("<<corners[i].x<<","<<corners[i].y<<")"<<endl; }

}

int main(  )
{
	system("color 2F"); 

	g_srcImage = imread(MediaPath+"CH10/cornerSubPix.jpg", 1 );
	cvtColor( g_srcImage, g_grayImage, COLOR_BGR2GRAY );

	namedWindow( WINDOW_NAME, WINDOW_AUTOSIZE );
	createTrackbar( "���ǵ���", WINDOW_NAME, &g_maxCornerNumber, g_maxTrackbarNumber, on_GoodFeaturesToTrack );
	imshow( WINDOW_NAME, g_srcImage );
	on_GoodFeaturesToTrack( 0, 0 );

	waitKey(0);
	return(0);
}