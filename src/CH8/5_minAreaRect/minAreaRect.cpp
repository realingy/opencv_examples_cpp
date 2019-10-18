// ������Χ�����ľ��α߽�
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
using namespace cv;
using namespace std;

int main(  )
{
	system("color 1F"); 

	Mat image(600, 600, CV_8UC3);
	RNG& rng = theRNG();

	while(1)
	{
		//������ʼ��
		int count = rng.uniform(3, 103);//������ɵ������
		vector<Point> points;//��ֵ

		//������ɵ�����
		for(int  i = 0; i < count; i++ )
		{
			Point point;
			point.x = rng.uniform(image.cols/4, image.cols*3/4);
			point.y = rng.uniform(image.rows/4, image.rows*3/4);

			points.push_back(point);
		}

		//�Ը����� 2D �㼯��Ѱ����С����İ�Χ����
		RotatedRect box = minAreaRect(Mat(points));
		Point2f vertex[4];
		box.points(vertex);

		//���Ƴ������ɫ�ĵ�
		image = Scalar::all(0);
		for( int i = 0; i < count; i++ )
			circle( image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA );

		//���Ƴ���С����İ�Χ����
		for( int i = 0; i < 4; i++ )
			line(image, vertex[i], vertex[(i+1)%4], Scalar(100, 200, 211), 2, LINE_AA);

		//��ʾ����
		imshow("���ΰ�Χʾ��", image);

		//����ESC,Q,����q�������˳�
		char key = (char)waitKey();
		if( key == 27 || key == 'q' || key == 'Q' ) // 'ESC'
			break;
	}

	return 0;
}
