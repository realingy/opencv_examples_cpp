#include "opencv2/highgui.hpp" 
#include "opencv2/imgproc.hpp" 
#include "path.h"
using namespace cv; 

int main()
{ 
	std::string src = MediaPath + "6.jpg";
	Mat srcImage=imread(src); 

	imshow( "��ֵ�˲���ԭͼ��", srcImage ); 

	Mat dstImage; 
	blur( srcImage, dstImage, Size(7, 7));  //��ֵ�˲��Ƿ����˲��Ĺ�һ����Ľ��

	imshow( "��ֵ�˲���Ч��ͼ��" ,dstImage ); 

	waitKey(0);     
} 