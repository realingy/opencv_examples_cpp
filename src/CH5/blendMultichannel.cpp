#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "path.h"
#include <iostream>

using namespace cv;
using namespace std;

//分离颜色通道&多通道图像混合

bool  MultiChannelBlending();

int main()
{
    //system("color 9F");

    if(MultiChannelBlending())
        cout<<"Blending Successfully!";

    waitKey(0);
    return 0;
}

//多通道混合的实现函数
bool  MultiChannelBlending()
{
    //	描述：多通道混合-蓝色分量部分
    string src = MediaPath + "dota_pa.jpg";
    string logo = MediaPath + "dota_logo.jpg";
    Mat srcImage= imread(src);
    Mat logoImage= imread(logo, 0);

    if( !logoImage.data )
        return false;
    if( !srcImage.data )
        return false;

    vector<Mat> channels;
    split(srcImage, channels); //分离色彩通道

    //Mat splitChannel = channels.at(0); //蓝色通道
    //Mat splitChannel = channels.at(1); //绿色通道
    Mat splitChannel = channels.at(2); //红色通道

    Mat ROI = splitChannel(Rect(450, 150, logoImage.cols, logoImage.rows));
    addWeighted(ROI, 1.0, logoImage, 0.5, 0., ROI);

    merge(channels, srcImage);

    imshow("src blur channel+logo", srcImage);

    return true;
}
