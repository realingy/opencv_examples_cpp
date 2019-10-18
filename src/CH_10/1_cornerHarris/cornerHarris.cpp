// cornerHarris����
#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc.hpp>  
#include "path.h"
using namespace cv;  

int main()  
{  
	//�ԻҶ�ģʽ����ͼ����ʾ
	Mat srcImage = imread(MediaPath+"CH10/cornerHarris.jpg", 0);  

	imshow("ԭʼͼ", srcImage);  

	//����Harris�ǵ����ҳ��ǵ�
	Mat cornerStrength;  
	cornerHarris(srcImage, cornerStrength, 2, 3, 0.01);

	//�ԻҶ�ͼ������ֵ�������õ���ֵͼ����ʾ  
	Mat harrisCorner;  
	threshold(cornerStrength, harrisCorner, 0.00001, 255, THRESH_BINARY);  

	imshow("�ǵ����Ķ�ֵЧ��ͼ", harrisCorner);  

	waitKey(0);  
	return 0;  
}  
