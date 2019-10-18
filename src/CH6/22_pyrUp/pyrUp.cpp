#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"
using namespace cv;

int main( )
{
	//����ԭʼͼ
	Mat srcImage = imread(MediaPath + "kid.jpg");
	if(!srcImage.data) {printf("read source image failed��\n"); return 0;}

	Mat tmpImage,dstImage;//��ʱ������Ŀ��ͼ�Ķ���
	tmpImage=srcImage;//��ԭʼͼ������ʱ����

	//��ʾԭʼͼ  
	imshow("��ԭʼͼ��", srcImage);  
	//��������ȡ������
	pyrUp( tmpImage, dstImage, Size( tmpImage.cols*2, tmpImage.rows*2 ) );

	imshow("��Ч��ͼ��", dstImage);  

	waitKey(0);  

	return 0;  
}
