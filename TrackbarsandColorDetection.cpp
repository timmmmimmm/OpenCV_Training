#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


#include <iostream>



int main() {

	cv::VideoCapture cap(1);

	/*std::string path = "res/lambo.jpg";*/

	cv::Mat frame /*= cv::imread(path)*/,
			frameHSV,
			frameO;

	


	int hueMin = 0, saturationMin = 0, valueMin = 0,
		hueMax = 179, saturationMax = 255, valueMax = 255;


	/*cv::imshow("Original Frame", frame);
	cv::imshow("HSV Frame", frameHSV);*/

	cv::namedWindow("Trackbars", (640, 200));
	cv::createTrackbar("Hue min", "Trackbars", &hueMin, 179);
	cv::createTrackbar("Hue max", "Trackbars", &hueMax, 179);
	cv::createTrackbar("Saturation min", "Trackbars", &saturationMin, 255);
	cv::createTrackbar("Saturation max", "Trackbars", &saturationMax, 255);
	cv::createTrackbar("Value min", "Trackbars", &valueMin, 255);
	cv::createTrackbar("Value max", "Trackbars", &valueMax, 255);

	while (true)
	{
		cap.read(frame);

		cv::cvtColor(frame, frameHSV, cv::COLOR_BGR2HSV);

		cv::Scalar lover(hueMin, saturationMin, valueMin),
			upper(hueMax, saturationMax, valueMax);

		cv::inRange(frameHSV, lover, upper, frameO);

		cv::imshow("Base Frame", frame);
		cv::imshow("Masked Frame", frameO);

		std::cout << hueMin << ", " << hueMax << ", " << saturationMin << ", "
			<< saturationMax << ", " << valueMin << ", " << valueMax << std::endl;

		//hMin, hMax, satMin, satMax, vMin, vMax

		cv::waitKey(33);
	}
	

	return 0;
}