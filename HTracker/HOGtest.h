#include "stdafx.h"
#pragma once
class HOGtest
{
public:
	HOGtest(void);
	HOGtest(Mat img);		// constructor for parallel process
	~HOGtest(void);

	void init();
	void detect(Mat& image);	// position of person is in 
	void show(Mat& image);	// draw the rectangle

	HOGDescriptor hog;
	vector<float> descriptorVector;
	Mat roi;
	vector<cv::Rect> found, found_filtered;
	vector<Point> found_h, found_h_filtered;

	HOGDescriptor* hogg;

	/**********************************************/
	/* detect variables                           */
	/**********************************************/
	int groupThreshold;
	Size padding;
	Size winStride;
	double hitThreshold; // 0 and should be specified in the detector coeifficients(as the last free coefficient).
	double scale;
};

