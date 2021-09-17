#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
#include<string>

using namespace std;
using namespace cv;

// ʵ���ϸо�c++��opencv�÷���python�еĻ���һ�£����Կ��������������api����ѧϰ


/// <summary>
/// 
/// </summary>
/// <returns></returns>
// ��ȡһ��ͼƬ��չʾ��������numpy����
Mat read_img() {
	string path = "Resources/test.png";
	Mat img = imread(path);
	imshow("image", img);
	waitKey(0);
	return img;
}


// ��ȡһ��������Ƶ������չʾ
void read_video() {
	// ʵ����һ��VideoCapture����
	VideoCapture cap("./Resources/test_video.mp4");
	Mat frame;
	while (true)
	{
		// cap.read ֱ�Ӱѽ��յ�ǰ֡�ı�������Ϊ��������read��������
		cap.read(frame);
		if (frame.dims == 0)
		{
			break;
		}
		imshow("video", frame);
		cv::waitKey(15);

	}
}

// ���ñ�������ͷ��ȡ��Ƶ
void read_capture() {
	// 0��ʾ���ص�0������ͷ
	VideoCapture cap(0);
	Mat frame;
	int key_code;
	while (true)
	{
		cap.read(frame);
		cv::imshow("capture", frame);
		key_code = waitKey(1);
		// 27�� esc���ļ���
		if (key_code == 27)
		{
			break;
		}
	}
	cap.release();
	destroyAllWindows();
}

int main() {
	// read_img();
	// read_video();
	read_capture();
}