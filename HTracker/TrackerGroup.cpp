#include "StdAfx.h"
#include "TrackerGroup.h"


TrackerGroup::TrackerGroup(void)
{
	this->noMatchThreshold = 16;
	this->noNeighborThreshold = 4;
	this->deltaX = 0;
	this->deltaY = 0;
}


TrackerGroup::~TrackerGroup(void)
{
}

double rectDistance(Rect r1, Rect r2) {
	return sqrt(pow(r1.x - r2.x, 2.0) + pow(r1.y - r2.y, 2.0));
}

void TrackerGroup::kalmanPredict()
{
	for (int i = 0; i < trackers.size(); i++) {
		trackers[i].kalmanPredict();
	}
}

void TrackerGroup::kalmanUpdate()
{
	for (int i = 0; i < trackers.size(); i++) {
		//trackers[i].kalmanPredict();
		trackers[i].kalmanCorrect();
		//cout<<trackers[i].kalman.measPt<<" ";
	}
	//cout<<endl;
}

FeatureTracker TrackerGroup::operator[](int i)
{
	return trackers[i];
}

void TrackerGroup::setThreshold()
{
	this->rectDistThreshold = 50;
}

/************************************************************************/
/* MAIN ALGORITM FOR MATCH                                              */
/************************************************************************/
void TrackerGroup::match(Mat img, vector<Rect> rects)
{
	isRectUsed.assign(rects.size(), false);		// initialize the vector for rects
	int one = 0;
	int temp;

	resetIsMatch();

	for (int i = 0; i < trackers.size(); i++) {
		vector<int> rectIndex; // store the index of rects that are close enough to match with trackers[i]
		for (int j = 0; j < rects.size(); j++) {
			// when rects[j] is unused and 
			if (!isRectUsed[j] && rectDistance(trackers[i].getRect(), rects[j]) < this->rectDistThreshold) {
				this->countNoNeighbor = 0;
				rectIndex.push_back(j);
			}
			else {
				// too far to match
				this->countNoNeighbor++;
			}
		}

		// there are rects more than one nearby
		if (rectIndex.size() > 1) {
			for (int j = 0; j < rectIndex.size(); j++) {
				// when trackers[i] is not matched with other and rect is not used
				if (!trackers[i].isMatch && !isRectUsed[rectIndex[j]]) {
					if (trackers[i].match(img, rects[rectIndex[j]])) {
						/***********************************************/
						/* MATCHED                                     */
						/***********************************************/
						trackers[i].isMatch = true;
						trackers[rectIndex[j]].isMatch = true;
						isRectUsed[rectIndex[j]] = true;	// rects[j] is used
						break;
					}
				}
				else {
					// close but not matched
					trackers[i].countNoMatch++;
				}
			}
		}
		// just one rect
		else if (rectIndex.size() == 1) {
			trackers[i].forceMatch(img, rects[rectIndex[0]]);
			trackers[i].isMatch = true;
			trackers[i].countNoMatch = 0;
			isRectUsed[rectIndex[0]] = true;
		}

		// not matched and trackers.size() is larger than rects.size()
		if (rects.size() < trackers.size()
			&& (trackers[i].countNoMatch > this->noMatchThreshold
			|| this->countNoNeighbor > this->noNeighborThreshold)) {
			eraseTracker(i);
		}
		else {
			trackers[i].countNoMatch++;
		}
	}

	// there are new people
	if (rects.size() > trackers.size()) {
		for (int i = 0; i < rects.size() - trackers.size(); i++) {
			FeatureTracker temp;
			for (int j = 0; j < rects.size(); j++) {
				if (!isRectUsed[j]) {					// if rects[j] is unused
					temp.computeBrisk(img, rects[j]);	// temp take a rects[j](person)
					isRectUsed[j] = true;
					break;
				}
			}
			trackers.push_back(temp);
		}
	}

	ofstream debug("debug.txt", ios::out | ios::app);
	for (int i = 0; i < trackers.size(); i++)
	{
		if (!trackers[i].isMatch){
			//cout<<"ㅜㅜ "<<&trackers[i]<<" is not matched"<<endl;
			debug << "ㅜㅜ " << &trackers[i] << " is not matched\n";
		}
	}
	debug.close();
	//kalmanUpdate();
}

void TrackerGroup::eraseTracker(int i)
{
	trackers.erase(trackers.begin() + i);
}

void TrackerGroup::draw(Mat img)
{
	for (int i = 0; i<trackers.size(); i++) {
		trackers[i].kalmanDraw(img);
	}
}

Point calcCenter(Rect r)
{
	Point2f p = (r.tl() + r.br());
	p = Point2f(p.x / 2.0, p.y / 2.0);
	return p;
}

bool IsInside(Point point, vector<Point2f> polygon, int n)
{
	int i, j;
	bool result = false;
	for (i = 0, j = n - 1; i < n; j = i++) {
		if (((polygon[i].y>point.y) != (polygon[j].y>point.y)) &&
			(point.x < (polygon[j].x - polygon[i].x) * (point.y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x))
			result = !result;
	}
	// point가 vertex 위에 있는지 검사. 일단 제외
	/*
	for(int i=0; i<n;i++){
	if(polygon[i]==point)
	result = true;
	}
	*/
	return result;
}

void TrackerGroup::drawMap(Mat& background)
{
	vector<Point2f> corners;
	corners.push_back(Point2f(7, 173));
	corners.push_back(Point2f(222, 150));
	corners.push_back(Point2f(355, 177));
	corners.push_back(Point2f(103, 214));

	vector<Point2f> quad_pts;
	quad_pts.push_back(Point2f(0, 0));
	quad_pts.push_back(Point2f(background.cols, 0));
	quad_pts.push_back(Point2f(background.cols, background.rows));
	quad_pts.push_back(Point2f(0, background.rows));

	Mat transmtx = getPerspectiveTransform(corners, quad_pts);

	vector<Point2f> src;	// points that will be transformed
	vector<Point2f> dst;	// points that will be made by transform

	Point temp, foot;

	for (int i = 0; i < trackers.size(); i++) {
		trackers[i].kalman_map.predict();
		temp = trackers[i].kalman.statePt + Point(0, trackers[i].getHeight());
		//- Point(trackers[i].getRect().width, 0)
		trackers[i].kalman_map.correction(temp);
	}

	for (int i = 0; i < trackers.size(); i++) {
		foot = trackers[i].kalman_map.statePt;
		if (IsInside(foot, corners, 4))
			src.push_back(foot);
	}
	if (!src.empty()) {
		perspectiveTransform(src, dst, transmtx);	// transform

		for (int i = 0; i < dst.size(); i++) {
			pres = dst[i];
			if (prev.y != 0) {
				line(background, prev, pres, Scalar(0, 255, 0), 2);
			}
		}

		dst.clear();
		prev = pres;
	}
}

int TrackerGroup::size()
{
	return trackers.size();
}

void TrackerGroup::resetIsMatch()
{
	for (int i = 0; i < size(); i++)
		this->trackers[i].isMatch = false;
}