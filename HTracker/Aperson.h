#pragma once
class Aperson
{
public:
	Aperson(void);
	~Aperson(void);
//	getter, setter
// 	void keypointsSetter(vector<KeyPoint>);
// 	vector<KeyPoint> keypointsGetter();
// 
// 	void descriptorsSetter(Mat);
// 	Mat descriptorsGetter();
// 
// 	void imageSetter(Mat);
// 	Mat imageGetter();
// 
// 	void rectSetter(Rect);
// 	Rect rectGetter();

	bool isEmpty();

	void setAperson(vector<KeyPoint>, Mat, Mat, Rect);
	void putHeight(double height);

	/************************************************************************/
	/* Match Variables                                                      */
	/************************************************************************/
	vector<KeyPoint> keypoints;
	Mat descriptors;
	Mat img;
	Rect rect;

	/************************************************************************/
	/* Characteristic                                                       */
	/************************************************************************/
	double height;	//  height of this person
	int n_height;	// for average

private:
	bool empty;
};

