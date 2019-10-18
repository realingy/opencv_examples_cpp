#include "opencv2/core.hpp" 
#include "opencv2/highgui.hpp" 
#include "opencv2/imgproc.hpp" 
#include "path.h"

using namespace cv; 

int main()
{ 
	Mat image=imread(MediaPath + "5.jpg"); 

	imshow("中值滤波【原图】", image); 

	Mat out; 
	medianBlur(image, out, 7);

	imshow("中值滤波【效果图】", out); 

	waitKey(0);     
} 