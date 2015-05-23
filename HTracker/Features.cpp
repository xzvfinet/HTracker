#include "stdafx.h"
#include "Features.h"

Features::Features(void)
{
}


Features::~Features(void)
{
}


void Features::init(int feature)
{
	this->feature = feature;
	switch(feature) {
	case SIFTf:
		sift_nfeatures=0;
		sift_nOctaveLayers=3;
		sift_contrastThreshold=0.04;
		sift_edgeThreshold=10;
		sift_sigma=1.6;				// if decrease, more points. 1.6
		sift = new SIFT(sift_nfeatures, sift_nOctaveLayers, sift_contrastThreshold, sift_edgeThreshold, sift_sigma);
		SIFT;
		break;
	case BRISKf:
		// parameters can be modified in main
// 		brisk_thresh = 15;			// IMPORTANT this value is important for brisk. default: 30
// 		brisk_octaves = 3;
// 		brisk_patternScale = 1.0f;
		brisk = preLoadedBrisk;
		break;
	}
}

void Features::compute( int feature, Mat &img, vector<KeyPoint> &keypoints, Mat &descriptors )
{
	if(this->feature != feature) {
		cout<<"you should call init() before compute"<<endl;
		return;
	}
	switch(feature) {
	case SIFTf:
		sift->detect(img, keypoints);
		sift->compute(img, keypoints, descriptors);
		break;
	case BRISKf:
		brisk->detect(img, keypoints);
		brisk->compute(img, keypoints, descriptors);
		break;
	default:
		cout<<"wrong feature"<<endl;
		break;
	}
}