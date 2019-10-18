#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"
using namespace cv;

int main()
{
	//����ԭʼͼ   
	Mat image = imread(MediaPath + "lemon.jpg");
	if( !image.data ) { printf("read source image failed��\n"); return 0; }

	//��ʾԭʼͼ  
	imshow("��ԭʼͼ����̬ѧ�ݶ�", image);  
	//�����
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));  
	//������̬ѧ����
	morphologyEx(image, image, MORPH_GRADIENT, element);

	imshow("��Ч��ͼ����̬ѧ�ݶ�", image);

	waitKey(0);  

	return 0;  
}
