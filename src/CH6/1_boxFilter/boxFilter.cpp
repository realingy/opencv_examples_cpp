#include "opencv2/core.hpp" 
#include "opencv2/highgui.hpp" 
#include "opencv2/imgproc.hpp" 
#include "path.h"
using namespace cv; 

int main( )
{ 
	std::string src = MediaPath + "5.jpg";
	Mat image=imread(src); 

	namedWindow("方框滤波【原图】"); 
	imshow("方框滤波【原图】", image); 

	Mat out; 
	boxFilter(image, out, -1, Size(5, 5), Point(-1, -1), true); //方框滤波

	namedWindow( "方框滤波【效果图】"); 
	imshow("方框滤波【效果图】",out); 

	waitKey( 0 );     
} 