#pragma once
#include "Features.h"
#define BRUTEFORCE 1
#define FLANN 2

class Matcher
{
public:
	Matcher(void);
	~Matcher(void);
	
	// matcher init
	// 1:BruteForce, 2:Flann
	void init(int matcher);

	// matcher match
	// 1:BruteForce, 2:Flann
	void match(int matcher, Mat descriptors1, Mat descriptors2);
	vector<DMatch> getMatches();

	Features feature;
	int matcher;
	
// 	/***********************************/
// 	/* Features                        */
// 	/***********************************/
// 	vector<cv::KeyPoint> keypoints1, keypoints2;
// 	Mat descriptors1, descriptors2;
	
	/***********************************/
	/* Brute Force parameters          */
	/***********************************/
private:
	BFMatcher *bfm;
//	FlannBasedMatcher fbm;
	vector<DMatch> matches;
	int thrsh;
	int normType;
};

