// Phat Phan, Nick Nigro, Yuriy Dubiy
// La Salle University
// 09/28/2018
// Motion detecting from camera
// Using OpenCV open source library
// original idea: track moving things then shoot it down.


#include <iostream>;
#include <opencv2/opencv.hpp>;
#include <opencv2/highgui/highgui.hpp>;
#include <opencv2/imgproc/imgproc.hpp>;
//#include "camShow.cpp";
//#include "pch.h";

using namespace cv;
using namespace std;
using namespace cv::ml;

// main method
int main(int argc, char** argv)
{
	/*
	int inputcam;
	printf("Enter camera number: ");
	scanf_s("%d",&inputcam);
	
	
	//showcam(inputcam);
	
	
	
	// the number inside cap is the camera any extenal camera, the number goes up
	VideoCapture cap(inputcam);

	// Mat class, look them up. All kind of fun thing in there
	Mat image1, image2;
	Mat grayscale1, grayscale2;
	Mat absOut, thresholdImg;

	//check cam
	if (!cap.isOpened())
	{
		cout << "Cannot open the web cam" << endl;
		return -1;
	}

	namedWindow("original", 1); // for edited video
	namedWindow("threshold", 1); // threshold video
	while (true)
	{
		bool bSuccess1 = cap.read(image1); // read a new frame from video

		if (!bSuccess1) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		cvtColor(image1, grayscale1, COLOR_BGR2GRAY); // convert to gray scale

		bool bSuccess2 = cap.read(image2); // read a new frame from video bud need little bit wait for next frame

		if (!bSuccess2) //if not success, break loop
		{
			cout << "Cannot read a frame from video stream" << endl;
			break;
		}

		cvtColor(image2, grayscale2, COLOR_BGR2GRAY); // convert to gray scale
		absdiff(grayscale1, grayscale2, absOut); //input need to be in grayscale

		//blur(thresholdImg, thresholdImg, Size(0,0));	//smooth effect, only use if you have external graphic card

		threshold(absOut, thresholdImg, 30, 255, THRESH_BINARY);	//only black and white

		erode(thresholdImg, thresholdImg, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));	//noise reduction 
		dilate(thresholdImg, thresholdImg, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));	//noise reduction 

		// I need to know more about this class.
		Moments mome = moments(thresholdImg);
		double dM01 = mome.m01;
		double dM10 = mome.m10;
		double dArea = mome.m00;

		int posX = dM10 / dArea;
		int posY = dM01 / dArea;

		
		// this is painting. paint whatever on the moving object, paint in the ass. we should look at the library.
		if (posX >= 0 && posY >= 0)	//paint cross
		{

			// strigger should happen when the paint start
			// which mean usual thing moving on screen
			line(image1, Point(posX + 30, posY), Point(posX - 30, posY), Scalar(0, 0, 255), 2);
			line(image1, Point(posX, posY + 30), Point(posX, posY - 30), Scalar(0, 0, 255), 2);

			//circle
			circle(image1, Point(posX,posY), 20, (255,0,0) , 1, 8, 0);
		}

		// show image
		imshow("threshold", thresholdImg);
		imshow("original", image1);

		// use esc to cancel
		if (waitKey(30) == 27) //wait for 'esc' key press
		{
			cout << "esc key is pressed" << endl;
			break;
		}
	}//end while loop

	
	return 0;
	
*/
	//int inputcam;
	//printf("Enter camera number: ");
	//scanf_s("%d", &inputcam);


	//showcam(inputcam);



	// the number inside cap is the camera any extenal camera, the number goes up
	//VideoCapture cap(inputcam);


/*
	/// Use the cmdlineparser to process input arguments
	CommandLineParser parser(argc, argv,
		"{ help h            |      | show this message }"
		"{ video v           |      | (required) path to video }"

	);

	/// If help is entered
	if (parser.has("help")) {
		parser.printMessage();
		return 0;
	}

	/// Parse arguments
	string video_location(parser.get<string>("video"));
	if (video_location.empty()) {
		parser.printMessage();
		return -1;
	}
*/


	/// Create a videoreader interface
	VideoCapture cap(1);
	Mat current_frame;
	//cap >> current_frame;
	/// Set up the pedestrian detector --> let us take the default one
	HOGDescriptor hog;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

	/// Set up tracking vector
	vector<Point> track;

	while (true) {

		/// Grab a single frame from the video
		cap>>current_frame;

		/// Check if the frame has content
		if (current_frame.empty()) {
			cerr << "Video has ended or bad frame was read. Quitting." << endl;
			return 0;
		}

		/// run the detector with default parameters. to get a higher hit-rate
		/// (and more false alarms, respectively), decrease the hitThreshold and
		/// groupThreshold (set groupThreshold to 0 to turn off the grouping completely).

		///image, vector of rectangles, hit threshold, win stride, padding, scale, group th
		Mat img = current_frame.clone();
		resize(img, img, Size(img.cols * 2, img.rows * 2));

		vector<Rect> found;
		vector<double> weights;

		hog.detectMultiScale(img, found, weights);

		/// draw detections and store location
		for (size_t i = 0; i < found.size(); i++)
		{
			Rect r = found[i];
			rectangle(img, found[i], cv::Scalar(0, 0, 255), 3);
			stringstream temp;
			temp << weights[i];
			putText(img, temp.str(), Point(found[i].x, found[i].y + 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255));
			track.push_back(Point(found[i].x + found[i].width / 2, found[i].y + found[i].height / 2));
		}

		/// plot the track so far
		for (size_t i = 1; i < track.size(); i++) {
			line(img, track[i - 1], track[i], Scalar(255, 255, 0), 2);
		}

		/// Show
		imshow("detected person", img);
		waitKey(1);
	}

	return 0;

	//source from StevenPuttemans 

	
	/* http://answers.opencv.org/question/179816/human-detection-and-tracking-opencv-c */

	

}//end main