#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "path.h"

using namespace cv;

int main()
{
	Mat image = imread(MediaPath + "lemon.jpg");
	if( !image.data ) { printf("read source image failed��\n"); return 0; }

	imshow("��ԭʼͼ����ʴ", image);
	//�����
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));  
	//������̬ѧ����
	morphologyEx(image, image, MORPH_ERODE, element);

	imshow("��Ч��ͼ����ʴ", image);  

	waitKey(0);  

	return 0;  
}
