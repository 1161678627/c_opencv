#include<iostream>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
using namespace std;


/*
ɫ����H�������Ͷȣ�S�������ȣ�V��, H:  0�� 180, S:  0�� 255, V:  0�� 255
*/

// ��֪ӳ���hsvɫ�� ָ����ɫ��ɸѡ����
void inRangeHsvColor() {
	// hsvɫ���ɸѡ����
	int hmin = 0, smin = 110, vmin = 153;
	int hmax = 19, smax = 240, vmax = 255;
	// ͼƬ��ɫɸѡһ��˼·����BGR����ת����HSV���򣻢���hsvɫ���ӳ����ͼƬ��ɫ����hsv���ˣ��۵õ����˺���ɫ���������ͼ��������ԭͼ��ɸѡָ��ԭʼ��ɫ����

	string path = "Resources/lambo.png";
	cv::Mat img = cv::imread(path);
	cv::imshow("img", img);

	// hsv�ռ�ת�����Ա���ɸѡ��ɫ����,��Ϊhsvɫ��ռ��������ģ�ת�����ͼƬ��ɫ��Ƚ����
	cv::Mat imgHsv;
	cv::cvtColor(img, imgHsv, cv::COLOR_BGR2HSV);

	// ɸѡ��ɫ
	cv::Mat mask;	// ���ڱ��� ͨ����ɫɸѡ������ɰ棬
	// ������ɫɸѡ�����������---�� imgHsv ͼƬ�϶�Ҫ�����ĵ�ǰ��ɫ���������޶�
	cv::Scalar lower(hmin, smin, vmin);
	cv::Scalar upper(hmax, smax, vmax);
	// ͨ����ɫɸѡ������Ϊ��ɫ���룬����Ϊ��ɫ���룬�����Ϳ�����ԭͼ��ɸѡ����Ӧ��ɫ��������
	cv::inRange(imgHsv, lower, upper, mask);

	cv::imshow("imgHsv", imgHsv);
	cv::imshow("mask", mask);

	// ɸѡ����֮��ʹ��ԭͼ��mask�� �� ���㣬��ԭͼ��ȡ�� ������Ϊ��ɫ���������
	cv::Mat imgCrop;
	cv::bitwise_and(img, img, imgCrop, mask);
	cv::imshow("imgCrop", imgCrop);
	cv::waitKey(0);
}


// ����hsvɫ�����ɫɸѡ����������������ȷ���ģ����ѵ����������һ��ʹ�ÿ��Զ�̬�϶���trackbarsʱʱ�϶������ٶ�λĳ����ɫ��hsv������
void selectBestHsvLimitValue(string path) {

	int hmin = 0, smin = 0, vmin = 0;
	int hmax = 180, smax = 255, vmax = 255;
	cv::Mat img = cv::imread(path);
	// cv::imshow("img", img);

	// hsv�ռ�ת�����Ա���ɸѡ��ɫ����,��Ϊhsvɫ��ռ��������ģ�ת�����ͼƬ��ɫ��Ƚ����
	cv::Mat imgHsv;
	cv::cvtColor(img, imgHsv, cv::COLOR_BGR2HSV);

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
		// ������ɫɸѡ�����������---�� imgHsv ͼƬ�϶�Ҫ�����ĵ�ǰ��ɫ���������޶�
		cv::Scalar lower(hmin, smin, vmin);
		cv::Scalar upper(hmax, smax, vmax);
		// ɸѡ��ɫ
		// ͨ����ɫɸѡ������Ϊ��ɫ���룬����Ϊ��ɫ���룬�����Ϳ�����ԭͼ��ɸѡ����Ӧ��ɫ��������
		cv::inRange(imgHsv, lower, upper, mask);

		cv::imshow("imgHsv", imgHsv);
		cv::imshow("mask", mask);
		int keyCode = cv::waitKey(1);
		if (keyCode == 27)
		{
			break;
		}
	}
	
}

int main() {

	inRangeHsvColor();
	// selectBestHsvLimitValue("Resources/shapes.png");
	return 0;
}