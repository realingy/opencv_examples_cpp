#include "opencv2/core.hpp" 
#include "opencv2/highgui.hpp" 
#include "opencv2/imgproc.hpp" 
#include "path.h"
using namespace cv; 

int main( )
{ 
	std::string src = MediaPath + "5.jpg";
	Mat image=imread(src); 

	namedWindow("�����˲���ԭͼ��"); 
	imshow("�����˲���ԭͼ��", image); 

	Mat out; 
	boxFilter(image, out, -1, Size(5, 5), Point(-1, -1), true); //�����˲�

	namedWindow( "�����˲���Ч��ͼ��"); 
	imshow("�����˲���Ч��ͼ��",out); 

	waitKey( 0 );     
} 