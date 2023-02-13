#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "helper.h"

using namespace cv;
using namespace std;

int featureCall(string dir, string target_file_name, string featureName, int n) {

	fs::path target_path = fs::current_path();
	target_path = (target_path/dir)/target_file_name;
	Mat target = imread(target_path.string(), IMREAD_COLOR);
	 
	string database = "-feature_csvdata.csv";
	vector<char*> fileNames;
	vector<vector<float>> featuresData;
	readFeatures(featureName+database, fileNames, featuresData);
	vector<float> featureTarget = generateFeatures(target, featureName);
	vector<Distance> distances = computeDistance(fileNames, featuresData, featureTarget, featureName);
	
	sort(distances.begin(), distances.end(), 
		[](Distance const& a, Distance const& b) {
			return a.dist < b.dist;
		});

	for (int i = 0; i < n; i++) {

		fs::path img_path = ((fs::current_path() / dir) / string(distances[i].filename));
		imshow("results", imread(img_path.string(), IMREAD_COLOR));
		waitKey(0);
	}
	return 0;
}


const int menu_height = 120;
const int menu_width = 300;

const int button_height = 20;
const int button_width = 300;

const string menu_options[] = {
	"Baseline Matching",
	"Histogram Matching",
	"Multi-histogram Matching",
	"Texture and color",
	"Custom Design Matching",
	"Exit"
};

void draw_menu(Mat& image)
{
	// Draw menu background
	rectangle(image, Point(0, 0), Point(menu_width, menu_height), Scalar(255, 0, 155), -1);

	// Draw menu options
	int y = 0;
	for (const auto& option : menu_options) {
		putText(image, option, Point(12, y + 16), FONT_HERSHEY_SIMPLEX, 0.5, Scalar(255, 255, 255),0.2);
		rectangle(image, Point(0, 0), Point(menu_width, y + 20), Scalar(0, 255, 0), 2);
		y += button_height;
	}
}

void on_mouse(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONUP) {
		int menu_index = y / button_height;
		if (menu_index >= 0 && menu_index < sizeof(menu_options) / sizeof(string)) {
			cout << "Selected option: " << menu_options[menu_index] << endl;
			switch (menu_index) {
			case 0: {
				featureCall("olympus", "pic.1016.jpg", "baseline", 4);
				break;
			}
			case 1: {
				featureCall("olympus", "pic.0164.jpg", "histogram_matching", 4);
				break;
			}
			case 2: {
				featureCall("olympus", "pic.0274.jpg", "multi-histogram_matching", 4);
				break;
			}
			case 3: {
				featureCall("olympus", "pic.0535.jpg", "texture-color_matching", 4);
				break;
			}
			case 4: {
				featureCall("orangecustom", "orange_7.jpeg", "customdata_matching", 10);
				break;
			}
			case 5: {
				exit(0);
				break;
			}
			}
		}
	}
}

int main()
{
	Mat image(menu_height, menu_width, CV_8UC3, Scalar(200, 200, 200));

	draw_menu(image);

	namedWindow("Menu", WINDOW_NORMAL);
	setMouseCallback("Menu", on_mouse);

	imshow("Menu", image);

	waitKey(0);

	return 0;
}