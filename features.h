#pragma once
#include "helper.h"

class features
{
};

void baselineFeature(Mat& image, vector<float>& features);

void histogramFeature(Mat& image, vector<float>& features);

void oneHistogramFeature(Mat& image, vector<float>& features);

void multiHistogramFeature(Mat& image, vector<float>& features);

void colorTextureFeature(Mat& image, vector<float>& features);

void customFeature(Mat& image, vector<float>& features);
