// Harris�ǵ���
#include <opencv2/opencv.hpp>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "path.h"
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "�����򴰿�1��"        //Ϊ���ڱ��ⶨ��ĺ�  
#define WINDOW_NAME2 "�����򴰿�2��"        //Ϊ���ڱ��ⶨ��ĺ�  

Mat g_srcImage, g_srcImage1,g_grayImage;
int thresh = 30; //��ǰ��ֵ
int max_thresh = 175; //�����ֵ

void on_CornerHarris( int, void* );//�ص�����

int main( int argc, char** argv )
{
	system("color 3F");  

	g_srcImage = imread( MediaPath+"CH10/cornerHarris2.jpg", 1 );
	if(!g_srcImage.data ) { printf("��ȡͼƬ���� \n"); return -1; }  

	imshow("ԭʼͼ",g_srcImage);
	g_srcImage1=g_srcImage.clone( );

	cvtColor( g_srcImage1, g_grayImage, COLOR_BGR2GRAY );

	namedWindow( WINDOW_NAME1, WINDOW_AUTOSIZE );
	createTrackbar( "��ֵ: ", WINDOW_NAME1, &thresh, max_thresh, on_CornerHarris );

	on_CornerHarris( 0, 0 );

	waitKey(0);
	return(0);
}

void on_CornerHarris( int, void* )
{
	//---------------------------��1������һЩ�ֲ�����-----------------------------
	Mat dstImage;//Ŀ��ͼ
	Mat normImage;//��һ�����ͼ
	Mat scaledImage;//���Ա任��İ�λ�޷������͵�ͼ

	//---------------------------��2����ʼ��---------------------------------------
	//���㵱ǰ��Ҫ��ʾ������ͼ���������һ�ε��ô˺���ʱ���ǵ�ֵ
	dstImage = Mat::zeros( g_srcImage.size(), CV_32FC1 );
	g_srcImage1=g_srcImage.clone( );

	//---------------------------��3����ʽ���-------------------------------------
	//���нǵ���
	cornerHarris( g_grayImage, dstImage, 2, 3, 0.04, BORDER_DEFAULT );

	// ��һ����ת��
	normalize( dstImage, normImage, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
	convertScaleAbs( normImage, scaledImage );//����һ�����ͼ���Ա任��8λ�޷������� 

	//---------------------------��4�����л���-------------------------------------
	// ����⵽�ģ��ҷ�����ֵ�����Ľǵ���Ƴ���
	for( int j = 0; j < normImage.rows ; j++ )
	{ for( int i = 0; i < normImage.cols; i++ )
	{
		if( (int) normImage.at<float>(j,i) > thresh+80 )
		{
			circle( g_srcImage1, Point( i, j ), 5,  Scalar(10,10,255), 2, 8, 0 );
			circle( scaledImage, Point( i, j ), 5,  Scalar(0,10,255), 2, 8, 0 );
		}
	}
	}
	//---------------------------��4����ʾ����Ч��---------------------------------
	imshow( WINDOW_NAME1, g_srcImage1 );
	imshow( WINDOW_NAME2, scaledImage );

}


