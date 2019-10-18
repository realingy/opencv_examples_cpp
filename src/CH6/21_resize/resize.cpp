#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include "path.h"
using namespace cv;

int main()
{
	Mat srcImage = imread(MediaPath + "kid.jpg");
	if(!srcImage.data) {printf("read source image failed��\n"); return 0;}

	Mat tmpImage,dstImage1,dstImage2;//��ʱ������Ŀ��ͼ�Ķ���
	tmpImage=srcImage;//��ԭʼͼ������ʱ����

	//��ʾԭʼͼ  
	imshow("��ԭʼͼ��", srcImage);  

	//���гߴ��������
	resize(tmpImage,dstImage1,Size( tmpImage.cols/2, tmpImage.rows/2 ),(0,0),(0,0),3);
	resize(tmpImage,dstImage2,Size( tmpImage.cols*2, tmpImage.rows*2 ),(0,0),(0,0),3);

	imshow("��Ч��ͼ��֮һ", dstImage1);  
	imshow("��Ч��ͼ��֮��", dstImage2);  

	waitKey(0);  
	return 0;  
}
