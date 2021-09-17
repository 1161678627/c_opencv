#include<iostream>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<string>

using namespace std;
using namespace cv;

// c++�ƺ������÷���ֵ���������ϲ��ֱ�Ӵ���һ��ָ����Ϊ������Ȼ���ں����ھ͸�ֵ��


void processImg() {
	string path = "./Resources/test.png";
	Mat img = imread(path);
	Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;
	// תΪ�Ҷ�
	cvtColor(img, imgGray, COLOR_BGR2GRAY);

	// ��˹ģ���������Խ��Խģ��
	GaussianBlur(img, imgBlur, Size(7, 7), 5, 0);

	// ��Ե���---��Ե����ͼ����ģ������ͼ������һЩ�ݶ����Ե�����
	// ��ֵԽС����ԵԽ�࣬ģ���̶�Խ�󣬱�ԵԽ��
	Canny(imgBlur, imgCanny, 25, 75);

	// ����
	// ���͵ĵ�����������һ��array kernal��Ҫʹ��Mat��ʽ���壬ָ��һ��3*3�ľ��κ�
	// ���ͺ�Խ������Խ��
	Mat kernal = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernal);
	// ��ʴ��Խ������Խ��
	erode(imgDil, imgErode, kernal);

	/*imshow("img", img);
	imshow("imgGray", imgGray);
	imshow("imgBlur", imgBlur);*/
	imshow("imgCanny", imgCanny);
	imshow("imgDil", imgDil);
	imshow("imgErode", imgErode);
	waitKey(0);
}


int main() {
	processImg();
	return 0;
}