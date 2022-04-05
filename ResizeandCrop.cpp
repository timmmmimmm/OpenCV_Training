#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

int main() {

	std::string path = "res/test.jpg";

	cv::Mat frame = cv::imread(path),
			resizedFrame;

	//cv::imshow("Base Image", frame);

	std::cout << frame.size() << std::endl;

	cv::resize(frame, resizedFrame, cv::Size(), 0.45, 0.45);

	cv::Rect rect(300, 300, 500, 500);

	auto croppedFrame = resizedFrame(rect);



	cv::imshow("800x800 version of Base Image", resizedFrame);
	cv::imshow("Cropped Resized Image", croppedFrame);
	

	cv::waitKey(0);



	return 0;
}