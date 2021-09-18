#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include<string>
#include<iostream>
#include<vector>

using namespace std;

int main() {

	string path = "./Resources/test.png";
	cv::Mat img = cv::imread(path);

	// ���������haar������ʽ���
	cv::CascadeClassifier faceCascade;
	faceCascade.load("./Resources/haarcascade_frontalface_default.xml");
	// ����һ������������ ��⵽��face��Rect
	vector<cv::Rect> faces;
	faceCascade.detectMultiScale(img, faces, 1.1, 10);
	
	// �����Ľ�����Ƴ���
	for (int i = 0; i < faces.size(); i++)
	{
		int x = faces[i].x;
		int y = faces[i].y;
		int w = faces[i].width;
		int h = faces[i].height;
		// cv::rectangle(img, cv::Point(x, y), cv::Point(x + w, y + h), cv::Scalar(0, 255, 255), 3);
		// cv::Rect ���� tl() �� br() ����ר�����ڷ��� ���ϣ����� ����
		cv::rectangle(img, faces[i].tl(), faces[i].br(), cv::Scalar(0, 255, 255), 3);
	}

	cv::imshow("img", img);
	cv::waitKey(0);
	return 0;
}