#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>


#include <iostream>








/// <summary>
/// Showing an image
/// </summary>


//int main()
//{
//	std::string path = "res/test.jpg";
//
//	cv::Mat pic = cv::imread(path);
//
//	cv::imshow("baseimage", pic);
//	cv::waitKey(0);
//
//	return 0;
//}



/// <summary>
/// Showing video
/// </summary>


//




/// Capturing wideo and displaying it


int main() {


	cv::VideoCapture cap(1);	//For some reason my cam isnt 0

	cv::Mat frame;


	while (true) {

		cap.read(frame);

		cv::imshow("test_vid.mp4", frame);

		cv::waitKey(1);

	}

	return 0;
}
