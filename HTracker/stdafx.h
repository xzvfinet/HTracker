// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <sstream>
#include <fstream>
#include <windows.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>W
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/ocl/ocl.hpp>

using namespace std;
using namespace cv;

#define WINDOW_WIDTH 360	//360 768
#define WINDOW_HEIGHT 288	//288 432

//#define IMWRITE
//#define WRITE_DETECTED
//#define SEQUENCE
//#define HEAD
//#define MYDETECT
//#define VIDEOWRITER