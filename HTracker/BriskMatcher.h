#pragma once
#include "stdafx.h"
#include "Features.h"
#include "Matcher.h"
#include "Aperson.h"

class BriskMatcher
{
public:
	BriskMatcher(void);
	~BriskMatcher(void);

	void init(int thrshNumber, int distanceThreshold);
	void compute(Mat image, Rect r);
	void computeTarget(Mat image, Rect r);
	bool match(Mat image, Rect r);
	void forceMatch(Mat image, Rect r);
	void inputPerson();
	void putHeight(double height);

	/***********************************/
	/* BRISK parameters                */
	/***********************************/
	Features feature;
	// Aperson includes keypoints, descriptors, image, rect
	Aperson person1, person2;
	Rect prevRect;

	/***********************************/
	/* Matcher parameters              */
	/***********************************/
	Matcher matcher;
	vector<DMatch> matches;
	int thrshNumber;
	int distanceThreshold;

};

