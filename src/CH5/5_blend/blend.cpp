#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "path.h"
#include <iostream>

using namespace cv;
using namespace std;

bool  ROI_AddImage();
bool  LinearBlending();
bool  ROI_LinearBlending();

int main(void)
{
    system("color 6F");

    if(ROI_AddImage() && LinearBlending() && ROI_LinearBlending())
    {
        cout<<endl<<"success, the dst is generated!";
    }
    waitKey(0);
    return 0;
}

//利用感兴趣区域ROI实现图像叠加
bool  ROI_AddImage()
{
	string src = MediaPath + "dota_pa.jpg";
	string logo = MediaPath + "dota_logo.jpg";
    Mat srcImage1= imread(src);
    Mat logoImage= imread(logo);
    if( !srcImage1.data )
        return false;
    if( !logoImage.data )
        return false;

    Mat imageROI= srcImage1(Rect(200, 250, logoImage.cols, logoImage.rows));

#if 0
    Mat mask= imread(logo,0);
    logoImage.copyTo(imageROI,mask);
#else
    logoImage.copyTo(imageROI);
#endif

    namedWindow("<1>Blending By ROI");
    imshow("<1>Blending By ROI", srcImage1);

    return true;
}

//利用cv::addWeighted()函数实现图像线性混合
bool  LinearBlending()
{
    double alpha = 0.5;
    double beta = 1 - alpha;

	string bkg = MediaPath + "mogu.jpg";
	string logo = MediaPath + "rain.jpg";
    Mat srcImage1 = imread(bkg);
    Mat srcImage2 = imread(logo);

    if( !srcImage1.data )
        return false;
    if( !srcImage2.data )
        return false;

    Mat dstImage;
    addWeighted( srcImage1, alpha, srcImage2, beta, 50.0, dstImage);

    imshow( "<2>Linear Blending src1", srcImage1 );
    imshow( "<2>Linear Blending src2", srcImage2 );
    imshow( "<3>Linear Blending dst", dstImage );

    return true;
}

//线性混合实现函数,指定区域线性图像混合.利用cv::addWeighted()函数结合定义感兴趣区域ROI，实现自定义区域的线性混合
bool  ROI_LinearBlending()
{
	string src = MediaPath + "dota_pa.jpg";
	string logo = MediaPath + "dota_logo.jpg";
    Mat srcImage = imread(src, 1);
    Mat logoImage = imread(logo);

    if(!srcImage.data)
        return false;
    if(!logoImage.data)
        return false;

    Mat imageROI;
    //方法一
    imageROI= srcImage(Rect(200, 250, logoImage.cols, logoImage.rows));
    //方法二
    //imageROI= srcImage4(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols));

    addWeighted(imageROI, 0.5, logoImage, 0.2, 0., imageROI);

    imshow("<4>Blending Mix", srcImage);

    return true;
}
