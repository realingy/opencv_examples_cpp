#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "path.h"
#include <iostream>

using namespace std;
using namespace cv;

Mat g_srcImage,g_dstImage1,g_dstImage2,g_dstImage3;//�洢ͼƬ��Mat����
int g_nBoxFilterValue=3;  //�����˲�����ֵ
int g_nMeanBlurValue=3;  //��ֵ�˲�����ֵ
int g_nGaussianBlurValue=3;  //��˹�˲�����ֵ

static void on_BoxFilter(int, void *);		//��ֵ�˲�
static void on_MeanBlur(int, void *);		//��ֵ�˲�
static void on_GaussianBlur(int, void *);	//��˹�˲�

int main()
{
	system("color 5F");  

	g_srcImage = imread(MediaPath + "7.jpg", 1);
	if(!g_srcImage.data) {return 0;}

	g_dstImage1 = g_srcImage.clone();
	g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();

	namedWindow("��<0>ԭͼ���ڡ�", 1);
	imshow("��<0>ԭͼ���ڡ�",g_srcImage);

	//=================��<1>�����˲���==================
	namedWindow("��<1>�����˲���", 1);
	createTrackbar("�ں�ֵ��", "��<1>�����˲���", &g_nBoxFilterValue, 40, on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);

	//=================��<2>��ֵ�˲���==================
	namedWindow("��<2>��ֵ�˲���", 1);
	createTrackbar("�ں�ֵ��", "��<2>��ֵ�˲���",&g_nMeanBlurValue, 40,on_MeanBlur );
	on_MeanBlur(g_nMeanBlurValue,0);

	//=================��<3>��˹�˲���=====================
	namedWindow("��<3>��˹�˲���", 1);
	createTrackbar("�ں�ֵ��", "��<3>��˹�˲���",&g_nGaussianBlurValue, 40,on_GaussianBlur );
	on_GaussianBlur(g_nGaussianBlurValue,0);

	//���һЩ������Ϣ
	cout<<endl<<"\t���гɹ���������������۲�ͼ��Ч��~\n\n"
		<<"\t���¡�q����ʱ�������˳���\n";

	//���¡�q����ʱ�������˳�
	while(char(waitKey(1)) != 'q') {}

	return 0;
}

//�����������˲������Ļص�����
static void on_BoxFilter(int, void *)
{
	boxFilter( g_srcImage, g_dstImage1, -1,Size( g_nBoxFilterValue+1, g_nBoxFilterValue+1));
	imshow("��<1>�����˲���", g_dstImage1);
}

//��������ֵ�˲������Ļص�����
static void on_MeanBlur(int, void *)
{
	blur( g_srcImage, g_dstImage2, Size( g_nMeanBlurValue+1, g_nMeanBlurValue+1), Point(-1,-1));
	imshow("��<2>��ֵ�˲���", g_dstImage2);
}

//��������˹�˲������Ļص�����
static void on_GaussianBlur(int, void *)
{
	GaussianBlur( g_srcImage, g_dstImage3, Size( g_nGaussianBlurValue*2+1, g_nGaussianBlurValue*2+1 ), 0, 0);
	imshow("��<3>��˹�˲���", g_dstImage3);
}

