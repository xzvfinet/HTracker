#include "StdAfx.h"
#include "Aperson.h"


Aperson::Aperson(void)
{
	this->height = 0;
	this->n_height = 0;
}


Aperson::~Aperson(void)
{
}

// getter, setter
// void Aperson::keypointsSetter( vector<KeyPoint> keypoints)
// {
// 	this->keypoints = keypoints;
// }
// 
// vector<KeyPoint> Aperson::keypointsGetter()
// {
// 	return this->keypoints;
// }
// 
// void Aperson::descriptorsSetter( Mat descriptors)
// {
// 	this->descriptors = descriptors;
// }
// 
// cv::Mat Aperson::descriptorsGetter()
// {
// 	return this->descriptors;
// }
// 
// void Aperson::imageSetter( Mat image )
// {
// 	this->img = image;
// }
// 
// cv::Mat Aperson::imageGetter()
// {
// 	return this->img;
// }
// 
// void Aperson::rectSetter( Rect rect)
// {
// 	this->rect = rect;
// }
// 
// Rect Aperson::rectGetter()
// {
// 	return this->rect;
// }



void Aperson::setAperson( vector<KeyPoint> keypoints, Mat descriptors, Mat image, Rect rect )
{
	this->keypoints = keypoints;
	this->descriptors = descriptors;
	this->img = image;
	this->rect = rect;
	this->empty = true;
}

bool Aperson::isEmpty()
{
	return empty;
}

void Aperson::putHeight( double height )
{// 가중치를 부여한다. 현재 키에(9/10), 새로 입력된 키에(1/10).
	int weight=10;
	this->n_height++;
	if(n_height>=weight)
		this->height = this->height*((weight-1.0)/weight) + height*(1.0/weight);
	else
		this->height = this->rect.height;
}
