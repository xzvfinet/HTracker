#pragma once
#include "stdafx.h"
#include "BriskMatcher.h"
#include "KalmanTest.h"
#include "Features.h"
#include "Matcher.h"

class FeatureTracker
{
public:
	FeatureTracker(void);
	~FeatureTracker(void);

	void compute(int feature, Mat img, Rect r);
	void computeBrisk(Mat img, Rect r);
	Rect getRect();									// get person1's rect
	double getHeight();		// get person1's height
	void setMatch(bool val);
	bool match(Mat img, Rect r);
	void forceMatch(Mat img, Rect r);
	void kalmanInit(Rect r);
	void kalmanPredict();
	void kalmanCorrect();
	void kalmanDraw(Mat img);
	bool isEmpty();

	BriskMatcher brisk;
	KalmanTest kalman;
	KalmanTest kalman_map;

	bool isPrepared;
	bool isMatch;

	int countNoMatch;
	int countMissing;
	int r,g,b;
};

