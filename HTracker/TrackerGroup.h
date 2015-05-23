#pragma once
#include "FeatureTracker.h"

class TrackerGroup
{
public:
	TrackerGroup(void);
	~TrackerGroup(void);

	void kalmanUpdate();						// update all trackers's kalman
	FeatureTracker operator[](int i);
	void setThreshold();						// set threshold
	void match(Mat img, vector<Rect> rects);	// match
	void draw(Mat img);							// draw the rects of trackers
	void drawMap(Mat& background);				// draw map
	void eraseTracker(int i);					// erase i th trackers
	int size();									// return the size of trackers
	void resetIsMatch();						// set all trackers's isMatch to false 

	vector<FeatureTracker> trackers;
	vector<bool> isRectUsed;

	int noMatchThreshold;
	int rectDistThreshold;
	int noNeighborThreshold;
	int countNoNeighbor;
	
	// for map
	Point prev, pres;
	double deltaX, deltaY;
};

