#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>


#include <iostream>


int main() {

	cv::VideoCapture cap(0);

	/*std::string path = "res/test.jpg";*/
	//std::vector<cv::Rect> faces{};

	cv::Mat frame /*= cv::imread(path)*//*, resizedFrame{}*/;
	//cv::CascadeClassifier cascade;

	//cascade.load("res/haarcascade.xml");
	
	/*if (cascade.empty()) {
		std::cout << "XML file failed to load" << std::endl;
		return -1;
	}*/



	//cv::resize(frame, resizedFrame, cv::Size(0,0), 0.45, 0.45);

	while (true)
	{
		cap.read(frame);


		//cascade.detectMultiScale(/*resizedFrame*/frame, faces, 1.1, 3);

		//for (const auto& face : faces) {
		//	cv::rectangle(resizedFrame/*frame*/, face.tl(), face.br(), cv::Scalar(0, 0, 255), 3);
		//}


		cv::imshow("Base Frame", /*resizedFrame*/ frame);

		cv::waitKey(33);
	}
	

	return 0;
}