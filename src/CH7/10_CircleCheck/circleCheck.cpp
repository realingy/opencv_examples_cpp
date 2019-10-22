#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "path.h"
#include <iostream>

using namespace cv;
using namespace std;

#define WINDOW_NAME "�����򴰿ڡ�" //Ϊ���ڱ��ⶨ��ĺ� 

double area; //�������
int g_nThresholdValue = 131; //��ֵ����ֵ
int g_nThresholdType = 3;
double minarea = 378; //Ŀ��������С���ص����
double maxarea = 478; //Ŀ������������ص����
Moments mom; //������  

Mat image, gray, edge, dst, g_srcImage1, dst1, g_srcImage, g_grayImage, g_dstImage;

vector<vector<Point> > contours;   //��������  
vector<Point2d>  centers;    //������������   
vector<vector<Point> >::iterator itr;  //����������  
vector<Point2d>::iterator  itrc;    //�������������  
vector<vector<Point> > con;    //��ǰ����  
Point2d center;//��������

void on_Threshold(int, void*);//�ص�����

int main()
{
	g_srcImage = imread(MediaPath + "houghcircle.jpg");

	//resize(g_srcImage, g_srcImage1, Size(g_srcImage.cols / 4, g_srcImage.rows / 4), 0, 0, INTER_LINEAR);
	imshow("ԭʼͼ", g_srcImage);

	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);//�Ҷ�ת��

	namedWindow(WINDOW_NAME, WINDOW_NORMAL);

	createTrackbar("ģʽ",
		WINDOW_NAME, &g_nThresholdType,//��ֵ��ģʽ
		4, on_Threshold);

	createTrackbar("����ֵ",
		WINDOW_NAME, &g_nThresholdValue,//��ֵ����ֵ 
		255, on_Threshold);

	on_Threshold(0, 0);//�������ص�����

	while (1)
	{
		int key;
		key = waitKey(20);
		if ((char)key == 27) { break; }
	}

	waitKey(0);

	return 0;
}

void on_Threshold(int, void*)
{
	//������ֵ�������Ҷ�ͼ��ֵ��
	Mat xx;
	threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, CV_THRESH_BINARY);
	resize(g_dstImage, xx, Size(1000, 500));

	namedWindow("��ֵͼ", WINDOW_NORMAL);
	imshow("��ֵͼ", xx);

	//resize(g_dstImage, g_srcImage1, Size(g_dstImage.cols / 4, g_dstImage.rows / 4), 0, 0, INTER_LINEAR);
	//imshow("threshold", g_srcImage1);

	Mat element2 = getStructuringElement(MORPH_RECT, Size(10, 10));//����ģ��
	Mat erode1, erode2;
	dilate(g_dstImage, erode1, element2);//����
	dilate(erode1, erode2, element2);

	//resize(erode2, g_srcImage1, Size(erode2.cols / 4, erode2.rows / 4), 0, 0, INTER_LINEAR);
	//imshow("dilate", g_srcImage1);

	findContours(erode2, contours,
		CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);//�ҳ�����

	itr = contours.begin();     //ʹ�õ�����ȥ����Ŀ������  
	while (itr != contours.end())
	{
		area = contourArea(*itr);//�������

		if ((area < minarea) | (area > maxarea))
		{
			itr = contours.erase(itr);  //ɾ��
		}
		else
		{
			itr++;
		}
	}

	dst = Mat::zeros(erode2.rows, erode2.cols, CV_8UC3);//�����м���
	itr = contours.begin();
	while (itr != contours.end())
	{
		area = contourArea(*itr);
		con.push_back(*itr);

		//cout << "\nb " << area;
		drawContours(dst, con, -1, Scalar(255, 0, 0), 2);   //Ŀ��������ɫ����  
		mom = moments(*itr);   //��������
		center.x = (int)(mom.m10 / mom.m00);
		center.y = (int)(mom.m01 / mom.m00);
		char tam[10000];
		char sam[10000];
		sprintf(tam, "(%0.0f)", area);
		sprintf(sam, "(%0.0f,%0.0f)", center.x, center.y);
		putText(dst, tam, Point(center.x, center.y), FONT_HERSHEY_SIMPLEX, 2, Scalar(255, 0, 0), 5);//������
		putText(dst, sam, Point(center.x, center.y + 80), FONT_HERSHEY_SIMPLEX, 2, Scalar(0, 255, 0), 5);//�������
		//imwrite("20003.jpg", dst);
		//resize(dst, dst1, Size(dst.cols / 4, dst.rows / 4), 0, 0, INTER_LINEAR);
		//imshow("�м���", dst1);
		circle(g_srcImage, Point(center.x, center.y), 5, Scalar(0, 225, 0), 2, 3);//��Բ

		con.pop_back();

		itr++;
	}

	resize(g_srcImage, g_srcImage1, Size(g_srcImage.cols / 4, g_srcImage.rows / 4), 0, 0, INTER_LINEAR);

	//����Ч��ͼ
	imshow(WINDOW_NAME, g_srcImage1);

	//imwrite("s_pos71_run7_img190.jpg", g_srcImage);
}




