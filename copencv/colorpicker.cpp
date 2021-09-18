#include<iostream>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
using namespace std;


// ����hsvɫ�����ɫɸѡ����������������ȷ���ģ����ѵ����������һ��ʹ�ÿ��Զ�̬�϶���trackbarsʱʱ�϶������ٶ�λĳ����ɫ��hsv������
void selectBestHsvLimitValue(cv::VideoCapture cap) {

	cv::Mat img;
	int hmin = 0, smin = 0, vmin = 0;
	int hmax = 180, smax = 255, vmax = 255;
	
	// cv::imshow("img", img);

	// hsv�ռ�ת�����Ա���ɸѡ��ɫ����,��Ϊhsvɫ��ռ��������ģ�ת�����ͼƬ��ɫ��Ƚ����
	cv::Mat imgHsv;

	cv::Mat mask;	// ���ڱ��� ͨ����ɫɸѡ������ɰ棬


	// ����һ���´��ڣ�����Ƕ�� hsv ֵ���϶�bar��һ����ȫ���������Ĵ���
	// ��һ������Ϊ�����������ڰ��϶�bar���ڶ��������Ǵ��ڴ�Сsize
	cv::namedWindow("Trackbars", (300, 600));
	// ��һ������Ϊ �϶�������֣��ڶ�������Ϊ�϶��������ĸ�������������������Ϊ���϶�����Ƶ�ֵ����һ��int�����ý����������ĸ�����Ϊ�϶���ȡֵ����
	cv::createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	cv::createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	cv::createTrackbar("Sat Min", "Trackbars", &smin, 255);
	cv::createTrackbar("Sat Max", "Trackbars", &smax, 255);
	cv::createTrackbar("Val Min", "Trackbars", &vmin, 255);
	cv::createTrackbar("Val Max", "Trackbars", &vmax, 255);

	// ��forѭ���������϶�������hsvȡֵ��Ȼ��ˢ��չʾ���Ӷ������ж�����ʵ�ֵ
	while (true)
	{
		cap.read(img);
		cv::cvtColor(img, imgHsv, cv::COLOR_BGR2HSV);
		// ������ɫɸѡ�����������---�� imgHsv ͼƬ�϶�Ҫ�����ĵ�ǰ��ɫ���������޶�
		cv::Scalar lower(hmin, smin, vmin);
		cv::Scalar upper(hmax, smax, vmax);
		// ɸѡ��ɫ
		// ͨ����ɫɸѡ������Ϊ��ɫ���룬����Ϊ��ɫ���룬�����Ϳ�����ԭͼ��ɸѡ����Ӧ��ɫ��������
		cv::inRange(imgHsv, lower, upper, mask);

		cv::imshow("img", img);
		// cv::imshow("imgHsv", imgHsv);
		cv::imshow("mask", mask);
		int keyCode = cv::waitKey(1);
		if (keyCode == 27)
		{
			break;
		}
	}

}


int main() {
	cv::VideoCapture cap(0);
	selectBestHsvLimitValue(cap);
	cap.release();
	cv::destroyAllWindows();
	return 0;
}