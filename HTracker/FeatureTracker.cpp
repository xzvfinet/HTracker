#include "StdAfx.h"
#include "FeatureTracker.h"


FeatureTracker::FeatureTracker(void)
{
	isMatch = false;

	// IMPORTANT this value would be variable
	brisk.init(3, 90);	// the number of goodmatch, goodmatch distance
	kalman.init();
	kalman_map.init(1e-8, 2e-1);

	r=rand()%255;
	g=rand()%255;
	b=rand()%255;
	
	this->countMissing = 0;
	this->countNoMatch = 0;
}


FeatureTracker::~FeatureTracker(void)
{
}

void FeatureTracker::computeBrisk( Mat img, Rect r )
{
	this->brisk.compute(img, r);
	this->kalmanInit(r);	// set first point
	this->isPrepared = true;
}

void FeatureTracker::setMatch( bool val )
{
	this->isMatch = val;
}

bool FeatureTracker::match( Mat img, Rect r )
{
	return this->brisk.match(img, r);
}

void FeatureTracker::forceMatch( Mat img, Rect r )
{
	brisk.forceMatch(img, r);
}

void FeatureTracker::kalmanInit( Rect r )
{
	this->kalman.setStartPoint(r.tl());
	// initialize with feet position
	//Point p((r.tl().x+r.br().x)/2+this->getRect().width/2, (r.tl().y+r.br().y)/2 + this->brisk.person1.height);
	this->kalman_map.setStartPoint( r.br()-Point(r.width,0) );
}

void FeatureTracker::kalmanPredict()
{
	this->kalman.predict();
}

void FeatureTracker::kalmanCorrect()
{
	//cout<<this->brisk.rect1<<endl;
	this->kalman.correction(this->brisk.person1.rect);
}

void FeatureTracker::kalmanDraw( Mat img )
{
	// draw predicted point
	rectangle(img, kalman.predictPt, kalman.predictPt+Point(kalman.width, kalman.height), Scalar(b, g, r), 3);

	// draw stated rectangle
	//rectangle(img, kalman.statePt, kalman.statePt+Point(kalman.width, brisk.person1.height), Scalar(b, g, r), 3);
	stringstream ss;
	ss<<kalman.predictPt;
	putText(img, ss.str(), Point(kalman.predictPt.x, kalman.predictPt.y-5), 0, 0.8, Scalar(128, 255, 128), 2);
}

bool FeatureTracker::isEmpty()
{
	return this->brisk.person1.isEmpty();
}

Rect FeatureTracker::getRect()
{
	return brisk.person1.rect;
}

double FeatureTracker::getHeight()
{
	return brisk.person1.height;
}
