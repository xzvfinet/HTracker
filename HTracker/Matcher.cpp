#include "StdAfx.h"
#include "Matcher.h"


Matcher::Matcher(void)
{
}


Matcher::~Matcher(void)
{
}

void Matcher::init( int matcher )
{
	this->matcher = matcher;
	switch(matcher) {
	case BRUTEFORCE:
#if 1
		normType = NORM_HAMMING;		// for binary string based descriptors like BRISK, HAMMING distance should be used
#else
		normType = 4;
#endif
		bfm = new BFMatcher(normType);
		break;
	case FLANN:
		break;
	default:
		cout<<"wrong matcher"<<endl;
		break;
	}
}

void Matcher::match(int matcher, Mat descriptors1, Mat descriptors2 )
{
	if(this->matcher != matcher) {
		cout<<"you should call init() before match"<<endl;
		return;
	}
	if(!descriptors1.empty() && !descriptors2.empty())
		bfm->match(descriptors1, descriptors2, matches);
}

vector<DMatch> Matcher::getMatches()
{
	return matches;
}


