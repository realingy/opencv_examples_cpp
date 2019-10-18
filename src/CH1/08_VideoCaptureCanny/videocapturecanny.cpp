#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
    VideoCapture capture(0);
    Mat edge;

    while(1)
    {
        Mat frame;
        capture>>frame;
        cvtColor(frame,edge,COLOR_BGR2GRAY);
        blur(edge,edge,Size(7,7));

//        Canny(edge,edge,0,30,0);
        Canny(edge,edge,3,9,3);
        imshow("canny video capture",edge);
        waitKey(30);
    }

    return 0;
}
