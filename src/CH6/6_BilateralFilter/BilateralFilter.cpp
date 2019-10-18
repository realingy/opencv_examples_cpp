//程序描述：双边滤波bilateralFilter函数的使用
#include "opencv2/core.hpp" 
#include "opencv2/highgui.hpp" 
#include "opencv2/imgproc.hpp" 
#include "path.h"

using namespace cv; 

int main()
{ 
	Mat image=imread(MediaPath + "8.jpg"); 

	imshow("双边滤波【原图】", image); 

	Mat out;
	bilateralFilter(image, out, 25, 25*2, 25/2); 

	imshow("双边滤波【效果图】" , out); 

	waitKey(0);     
} 