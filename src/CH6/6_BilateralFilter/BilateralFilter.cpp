//����������˫���˲�bilateralFilter������ʹ��
#include "opencv2/core.hpp" 
#include "opencv2/highgui.hpp" 
#include "opencv2/imgproc.hpp" 
#include "path.h"

using namespace cv; 

int main()
{ 
	Mat image=imread(MediaPath + "8.jpg"); 

	imshow("˫���˲���ԭͼ��", image); 

	Mat out;
	bilateralFilter(image, out, 25, 25*2, 25/2); 

	imshow("˫���˲���Ч��ͼ��" , out); 

	waitKey(0);     
} 