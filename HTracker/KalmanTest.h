#pragma once
#include "stdafx.h"

class KalmanTest
{
public:
	KalmanTest(void);
	void init();
	void init(double, double);	// Process Noise Cov, Measurement Noise Cov
	void setStartPoint(Point p);
	void predict();
	void correction(cv::Point);
	void correction(cv::Rect);
	void draw(Mat image);

	~KalmanTest(void);

public:
	KalmanFilter KF;				//상태4, 측정2
	cv::Mat_<float> state;			//상태값 (x, y, Vx, Vy) 
	cv::Mat processNoise;			//노이즈 상태값4
	cv::Mat_<float> measurement;	//측정2
	cv::Mat prediction;
	cv::Mat estimated;
	cv::Point predictPt,
		measPt,
		statePt;
	int width, height;				//size of window(detected)

};

