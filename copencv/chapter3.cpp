#include<opencv2/imgproc.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<string>
#include<iostream>
#include <typeinfo> 

using namespace std;

void main() {
	string path = "./Resources/test.png";
	cv::Mat img = cv::imread(path);

	// �鿴ͼƬsize
	// img.size(),���ص���cv::size���ͣ��ܹ�ֱ�����Ӧ����������<<�����
	cout << typeid(img.size()).name() << endl;
	cout << img.size() << endl;
	cv::imshow("img", img);

	// resizeͼƬ
	cv::Mat imgResize;
	// ��һ�ַ�ʽ ����cv::Size(500, 500)��Ŀ��size
	cv::resize(img, imgResize, cv::Size(500, 500));
	// �ڶ��ַ�ʽ��ָ���������ű���---c++û��ʹ���β�����ֵ�ķ�ʽ���Ҳ�����������������
	cv::resize(img, imgResize, cv::Size(), 0.5, 0.5);
	cv::imshow("imgResize", imgResize);

	// cropͼƬ cv::Rect roi(x1, y1, w, h);
	cv::Rect roi(100, 100, 500, 200);
	cv::Mat imgCrop;
	// ֱ�Ӹ�img���洫һ��Rect���󣬱�ʾ���õ����򼴿ɣ�����ֻ��xy���꣬����ͨ����
	imgCrop = img(roi);

	cv::imshow("imgCrop", imgCrop);

	cv::waitKey(0);
}