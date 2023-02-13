#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

class filter
{
};

Mat sobelXFilter(  Mat& src);

Mat sobelYFilter(  Mat& src);

Mat magnitude(  Mat& sx,   Mat& sy,   Mat& src);

Mat orientation(  Mat& sx,   Mat& sy,   Mat& src);

Mat gaborFilter(  Mat outImg);