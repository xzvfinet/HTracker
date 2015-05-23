#pragma once
#define SIFTf 1
#define BRISKf 2

extern BRISK *preLoadedBrisk;

class Features
{
public:
	Features(void);
	~Features(void);

	// init
	// feature
	// 1:SIFT, 2:BRISK
	void init(int feature);
	void initBrisk();

	// compute and save the features of image
	// feature
	// 1:SIFT, 2:BRISK
	void compute(int feature, Mat &img, vector<KeyPoint> &keypoints, Mat &descriptors);
	void computeBrisk(Mat &img, vector<KeyPoint> &keypoints, Mat &descriptors);

private:
	/***********************************/
	/* Features                        */
	/***********************************/
	int feature;

	/***********************************/
	/* SIFT parameters                 */
	/***********************************/
	SIFT *sift;
	Mat sift_mask;
	int sift_nfeatures;
	int sift_nOctaveLayers;
	double sift_contrastThreshold;
	double sift_edgeThreshold;
	double sift_sigma;

	/***********************************/
	/* BRISK                           */
	/***********************************/
	BRISK *brisk;
	Mat brisk_mask;
	int brisk_thresh;
	int brisk_octaves;
	float brisk_patternScale;
};

