#include "stdafx.h"
#include "KalmanTest.h"


KalmanTest::KalmanTest(void)
{
}


KalmanTest::~KalmanTest(void)
{
}

void KalmanTest::init()
{ // Should be modified.
	KF = KalmanFilter(4, 2, 0);//상태4, 측정2
	state = Mat_<float>(4, 1); //상태값 (x, y, Vx, Vy) 
	processNoise = Mat(4, 1, CV_32F);//노이즈 상태값4
	measurement = Mat_<float>(2,1); //측정2

	measurement.setTo(Scalar(0));

	KF.statePre.at<float>(0) = 0;
	KF.statePre.at<float>(1) = 0;
	KF.statePre.at<float>(2) = 0;
	KF.statePre.at<float>(3) = 0;
	
	//전이 행렬
	KF.transitionMatrix = *(Mat_<float>(4, 4) << 1,0,1,0,   0,1,0,1,  0,0,1,0,  0,0,0,1);
	//단위행렬로 초기화

	//측정행렬
	setIdentity(KF.measurementMatrix);
	//프로세스 잡음 공분산, 클수록 수정값이 많이 변함
	setIdentity(KF.processNoiseCov, Scalar::all(1e-4));//1e-4, 따라오는 속도,클수록 빠름
	//측정 잡음 공분산, 작을수록 수정값이 많이 변함
	setIdentity(KF.measurementNoiseCov, Scalar::all(1e-1 ));//1e-1, 따라오는 속도, 작을수록 빠름
	//사후 에러 공분산
	setIdentity(KF.errorCovPost, Scalar::all( .1 ) );//.1


	randn(KF.statePost, Scalar::all(0), Scalar::all(0.1));
}

void KalmanTest::init( double pnc, double mnc )
{
	KF = KalmanFilter(4, 2, 0);//상태4, 측정2
	state = Mat_<float>(4, 1); //상태값 (x, y, Vx, Vy) 
	processNoise = Mat(4, 1, CV_32F);//노이즈 상태값4
	measurement = Mat_<float>(2,1); //측정2

	measurement.setTo(Scalar(0));

	KF.statePre.at<float>(0) = 0;
	KF.statePre.at<float>(1) = 0;
	KF.statePre.at<float>(2) = 0;
	KF.statePre.at<float>(3) = 0;

	//전이 행렬
	KF.transitionMatrix = *(Mat_<float>(4, 4) << 1,0,1,0,   0,1,0,1,  0,0,1,0,  0,0,0,1);
	//단위행렬로 초기화

	//측정행렬
	setIdentity(KF.measurementMatrix);
	//프로세스 잡음 공분산, 클수록 수정값이 많이 변함
	setIdentity(KF.processNoiseCov, Scalar::all(pnc));//1e-4, 따라오는 속도,클수록 빠름
	//측정 잡음 공분산, 작을수록 수정값이 많이 변함
	setIdentity(KF.measurementNoiseCov, Scalar::all(mnc));//1e-1, 따라오는 속도, 작을수록 빠름
	//사후 에러 공분산
	setIdentity(KF.errorCovPost, Scalar::all( .1 ) );//.1


	randn(KF.statePost, Scalar::all(0), Scalar::all(0.1));
}

void KalmanTest::setStartPoint( Point p )
{
	KF.statePre.at<float>(0) = p.x;
	KF.statePre.at<float>(1) = p.y;
	correction(p);
}

void KalmanTest::predict()
{
	prediction = KF.predict();//예측 : 다음 시간단계에 대한 예측
	predictPt = Point(prediction.at<float>(0), prediction.at<float>(1));
	
	//cout<<"예측점: "<<predictPt<<endl;
}

void KalmanTest::correction(cv::Point actual)
{
	measurement(0) = actual.x;
	measurement(1) = actual.y;
	measPt = Point(measurement(0),measurement(1));

	estimated = KF.correct(measurement);
	statePt = Point(estimated.at<float>(0), estimated.at<float>(1));
}

void KalmanTest::correction(cv::Rect actual)
{
	measurement(0) = actual.x;
	measurement(1) = actual.y;
	measPt = Point(measurement(0),measurement(1));
	this->width = actual.width;
	this->height = actual.height;

	estimated = KF.correct(measurement);
	statePt = Point(estimated.at<float>(0), estimated.at<float>(1));
}

void KalmanTest::draw( Mat image )
{
	rectangle(image, predictPt, predictPt+Point(width, height), Scalar(255, 0, 0), 3);	// 검출된 모든 사람에 녹색 사각형 그림
}
