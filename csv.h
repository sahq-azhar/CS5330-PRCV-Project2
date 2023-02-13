 #pragma once
#include <cstdio>
#include <cstring>
#include <vector>
#include "opencv2/opencv.hpp"
using namespace std;

class csv
{
};


#ifndef CVS_UTIL_H
#define CVS_UTIL_H

int append_image_data_csv(char* filename, char* image_filename,   vector<float>& image_data, int reset_file = 0);

int read_image_data_csv(char* filename,   vector<char*>& filenames,   vector<  vector<float>>& data, int echo_file = 0);
#endif 