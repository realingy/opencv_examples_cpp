#include "opencv2/core.hpp" 
#include "opencv2/highgui.hpp" 
#include "opencv2/imgproc.hpp" 
#include "path.h"

using namespace cv; 

int main()
{ 
	Mat image=imread(MediaPath + "5.jpg"); 

	imshow("��ֵ�˲���ԭͼ��", image); 

	Mat out; 
	medianBlur(image, out, 7);

	imshow("��ֵ�˲���Ч��ͼ��", out); 

	waitKey(0);     
} 