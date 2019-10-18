#include "opencv2/highgui.hpp" 
#include "opencv2/imgproc.hpp" 
#include "path.h"
using namespace cv; 

int main()
{ 
	std::string src = MediaPath + "6.jpg";
	Mat srcImage=imread(src); 

	imshow( "均值滤波【原图】", srcImage ); 

	Mat dstImage; 
	blur( srcImage, dstImage, Size(7, 7));  //均值滤波是方框滤波的归一化后的结果

	imshow( "均值滤波【效果图】" ,dstImage ); 

	waitKey(0);     
} 