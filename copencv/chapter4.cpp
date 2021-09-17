#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>

#include<iostream>

using namespace std;

int main() {

	// ����һ���հף���ɫ������ͼƬ��������Mat�Ĺ��캯��
	// CV_8UC3,8λ�޷�������3ͨ��ͼƬ,c++�Դ����������ͣ����ü�cv��ǰ׺
	cv::Mat img(512, 512, CV_8UC3, cv::Scalar(255, 255, 255));

	// ����һ���µ�ͼƬimg2����
	cv::Mat img2;
	img.copyTo(img2);

	// ��һ��Բ,ֱ����img���滭,������� д cv::FILLED ��ʾ����ڲ�
	cv::circle(img, cv::Point(127, 127), 100, cv::Scalar(0, 255, 0), 3, 6);

	// ��һ�����ο�
	cv::rectangle(img, cv::Point(200, 200), cv::Point(400, 400), cv::Scalar(255, 0, 0), cv::FILLED);
	
	// ����
	cv::line(img, cv::Point(100, 100), cv::Point(300, 300), cv::Scalar(0, 0, 255), 3);

	// д����
	cv::putText(img, "zhaokun test", cv::Point(100, 100), cv::FONT_HERSHEY_DUPLEX, 0.75, cv::Scalar(0, 0, 0), 2);

	cv::imshow("img", img);
	cv::waitKey(0);
}