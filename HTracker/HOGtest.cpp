#include "StdAfx.h"
#include "HOGtest.h"

HOGtest::HOGtest(void)
{
}

HOGtest::HOGtest( Mat img )
{

}


HOGtest::~HOGtest(void)
{

}

void HOGtest::init()
{
	// initialize
	groupThreshold = 2;
	padding = Size(4, 4);
	winStride = Size(8, 8);
	hitThreshold = 0.0; // 0 and should be specified in the detector coeifficients(as the last free coefficient).
	scale = 1.05;

#ifdef HEAD
	winStride = Size(8, 8);
	hog.cellSize = Size(4, 4);
	hog.blockStride = Size(4, 4);
    hog.winSize = Size(32, 32);
	hog.blockSize = Size(8, 8);
	hog.nbins = 8;
	
	ifstream input("data/descriptorVector(32x32) (1824 8713).dat");
	double val;
	input >> val;
	input >> val;
	cout<<"setting descriptor vector";
	for(int i=0; i<1568; i++) {
		input >> val;
		descriptorVector.push_back(val);
	}
	cout<<endl;
#else
	descriptorVector = HOGDescriptor::getDefaultPeopleDetector();
#endif

	hog.setSVMDetector(descriptorVector);

#ifdef DAIMLER
	hogg = new HOGDescriptor(Size(48,96), Size(16,16), Size(8,8), Size(8,8), 9);
	descriptorVector = HOGDescriptor::getDaimlerPeopleDetector();
	hogg->setSVMDetector(descriptorVector);
#endif
	
	
}

void HOGtest::detect( cv::Mat& image )
{
#ifdef HEAD
	hog.detect(image, found_h, 58.0, winStride, padding);
	for(int i=0; i<found_h.size(); i++)  {
		if(found_h[i].x>0 && found_h[i].y>0)
		this->found.push_back(Rect(found_h[i].x, found_h[i].y, 32, 32));
	}
#else
	hog.detectMultiScale(image, found, hitThreshold, winStride, padding, scale, groupThreshold);
#endif
	
	// grouping
 	//found.clear();
// 	for(int i=0; i<found_h.size(); i++) 
// 		this->found.push_back(Rect(found_h[i].x, found_h[i].y, 32, 32));
		//this->found.push_back(Rect(found_h[i].x, found_h[i].y, 64, 128));
	
	//groupRectangles(found, 2.0, 0.5);
#ifdef DAIMLER
	hogg->detectMultiScale(image, found, 1.2, Size(8,8), Size(32,32), 1.05, 6);
#endif
}



void HOGtest::show(cv::Mat& image)
{
#ifndef HEAD
	vector<Rect> found_filtered;
	size_t i, j;
	//	Mat target;
	for (i = 0; i < found.size(); ++i) {
		Rect r = found[i];
		for (j = 0; j < found.size(); ++j)
			if (j != i && (r & found[j]) == r)
				break;
		if (j == found.size())
			found_filtered.push_back(r);
	}// 같은 것이 여러개 있으면 걸러내는 루프
	this->found_filtered = found_filtered;


	for (i = 0; i < this->found_filtered.size(); i++) {
		// If the position of rect is out of image range, relocatse.
		if( this->found_filtered[i].x < 0 )
			this->found_filtered[i].x = 0;
		if( this->found_filtered[i].y < 0 )
			this->found_filtered[i].y = 0;
		if( this->found_filtered[i].x + this->found_filtered[i].width >= WINDOW_WIDTH )
			this->found_filtered[i].x = WINDOW_WIDTH - this->found_filtered[i].width;
		if( this->found_filtered[i].y + this->found_filtered[i].height >= WINDOW_HEIGHT )
			this->found_filtered[i].y = WINDOW_HEIGHT - this->found_filtered[i].height;

		Rect r = this->found_filtered[i];
		rectangle(image, r.tl(), r.br(), Scalar(64, 255, 64), 3);	// 검출된 모든 사람에 녹색 사각형 그림

		stringstream ss;
		string str;
		int a = i;
		ss<<a;
		str = "rect: "+ss.str();

		putText(image, str.c_str(), Point(r.br().x-r.width, r.br().y+19), 0, 0.8, Scalar(255, 255, 128), 2);
	}
#endif

#ifdef HEAD
	vector<Rect> found_filtered;
	size_t i, j;
	//	Mat target;
	for (i = 0; i < found.size(); ++i) {
		Rect r = found[i];
		for (j = 0; j < found.size(); ++j)
			if (j != i && (r & found[j]) == r)
				break;
		if (j == found.size())
			found_filtered.push_back(r);
	}// 같은 것이 여러개 있으면 걸러내는 루프
	this->found_filtered = found_filtered;
	found.clear();
	for(int i=0; i<found_filtered.size(); i++) {
		//rectangle(image, Rect(found_filtered[i].x, found_filtered[i].y, 64, 128), Scalar(0, 255, 0), 1);
		rectangle(image, Rect(found_filtered[i].x, found_filtered[i].y, 32, 32), Scalar(0, 255, 0), 2);
	}
#endif
}
