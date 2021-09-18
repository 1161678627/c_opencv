#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>
#include<vector>

using namespace std;

int main() {

	// ��Ȼ������Ե�������ͷ��ȡ��Ƶ����Ȼ��дһ��ѭ��ר�����������ÿ����Ƶ֡ �Ƿ��г���
	// ��⵽�����Ժ��ٰѳ����͵����������ȥʶ���ƺż���

	string path = "Resources/plate.jpg";
	cv::Mat img = cv::imread(path);

	// ������⳵�Ƶļ����
	cv::CascadeClassifier plateCascade;
	plateCascade.load("./Resources/haarcascade_russian_plate_number.xml");

	// �����ų��Ƽ����������
	vector<cv::Rect> plates;

	// ��ʼ���
	plateCascade.detectMultiScale(img, plates, 1.1, 10);

	cout << plates.size() << "xxxxxxxxxxxxxxxxxxxxxxxx" << endl;

	for (int i = 0; i < plates.size(); i++)
	{
		// ���г��ƺŵ�roi�����ȡ����
		cv::Mat imgPlate = img(plates[i]);

		// �����䱣������
		cv::imwrite("./Resources/Plates/" + to_string(i) + ".jpg", imgPlate);

		// ���ƾ�����ԭͼ��
		cv::rectangle(img, plates[i].tl(), plates[i].br(), cv::Scalar(0, 0, 255), 3);
	}
	
	cv::imshow("image", img);
	cv::waitKey(0);
	return 0;
}