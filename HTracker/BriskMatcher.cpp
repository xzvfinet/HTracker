#include "StdAfx.h"
#include "BriskMatcher.h"
#include "Features.h"

extern int count2;

BriskMatcher::BriskMatcher(void)
{
	// IMPORTANT this value would be variable
// 	this->thrshNumber = 1;
// 	this->distanceThreshold = 500;

}

BriskMatcher::~BriskMatcher(void)
{
}

void BriskMatcher::init( int thrshNumber, int distanceThreshold )
{
	feature.init(BRISKf);
	matcher.init(BRUTEFORCE);
	this->thrshNumber = thrshNumber;
	this->distanceThreshold = distanceThreshold;
}

void BriskMatcher::compute( Mat image, Rect r )
{
	this->person1.img = image(r).clone();
	this->person1.rect = r;

	feature.compute(BRISKf, person1.img, person1.keypoints, person1.descriptors);
}

void BriskMatcher::computeTarget( Mat image, Rect r )
{
	this->person2.img = image(r).clone();
	this->person2.rect = r;

	feature.compute(BRISKf, person2.img, person2.keypoints, person2.descriptors);
}

// match a person with another person
bool BriskMatcher::match( Mat image, Rect r )
{
	int count=0;
	bool result=false;

	/************************************************************************/
	/*  compute keypoints and match                                         */
	/************************************************************************/
	computeTarget(image, r);	// input r into person2
	matcher.match(BRUTEFORCE, person1.descriptors, person2.descriptors);
	matches = matcher.getMatches();

#ifdef DEBUG
	for(int i=0; i<matches.size(); i++) {
		cout<<matches[i].distance<<endl;
	}
#endif

	/************************************************************************/
	/* 1. compute the min and max distance of matches                       */
	/************************************************************************/
// 	double max_dist = 1; double min_dist = 1000;
// 	for( int i = 0; i < matches.size(); i++ )
// 	{ double dist = matches[i].distance;
// 	if( dist < min_dist ) min_dist = dist;
// 	if( dist > max_dist ) max_dist = dist;
// 	}
// 
// 	printf("-- Max dist : %f \n", max_dist );
// 	printf("-- Min dist : %f \n", min_dist );

	/************************************************************************/
	/* 2. count the match points that are below the threshold               */
	/************************************************************************/
	//vector<cv::DMatch>::iterator i;
	for(int i=0; i<matches.size(); i++) {
		if( matches[i].distance < this->distanceThreshold )	
			count++;
	}
#ifdef DEBUG
	cout<<"number of matched points "<<count<<endl;
#endif

	/************************************************************************/
	/* 3. check                                                             */
	/************************************************************************/
	if ( count>=thrshNumber ) {
		result = true;
		inputPerson();
	} else {
		result = false;
	}

	return result;
}

void BriskMatcher::forceMatch( Mat image, Rect r )
{
	this->computeTarget(image, r);
	this->inputPerson();
}

void BriskMatcher::inputPerson()
{
	this->prevRect = this->person1.rect;
	double temp_height = person1.height;
	int temp_n = person1.n_height;
	this->person1 = this->person2;
	this->person1.height = temp_height;
	this->person1.n_height = temp_n;
	this->putHeight( person2.rect.height );	// calculate the average of heights and update
}
// called by inputPerson.
void BriskMatcher::putHeight( double height )
{
	this->person1.putHeight(height);
}
