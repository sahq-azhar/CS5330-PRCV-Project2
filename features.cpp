#include "features.h"
#include "filter.h"
using namespace cv;
void baselineFeature(Mat& image, vector<float>& features) {

    int xx = image.rows / 2 - 4;
    int yy = image.cols / 2 - 4;

    for (int x = xx; x <= xx + 8; x++) {
        for (int y = yy; y <= yy + 8; y++) {
            Vec3b pixel = image.at<Vec3b>(x, y);
            for (int c = 0; c < image.channels(); c++) {
                features.push_back(pixel[c]);
            }
        }
    }

}

void histogramFeature(Mat& image, vector<float>& features) {

    const int bin_size = 8;
    const int Hsize = 256 / bin_size;
    int dim3[3] = { bin_size, bin_size, bin_size };
    Mat hist3d = Mat::zeros(3, dim3, CV_32S);
    float normalizing_sum = image.rows * image.cols;

    for (int x = 0; x < image.rows; x++) {
        for (int y = 0; y < image.cols; y++) {

            Vec3b pixel = image.at<Vec3b>(x, y);
            int b = pixel[0] / Hsize;
            int g = pixel[1] / Hsize;
            int r = pixel[2] / Hsize;
            hist3d.at<int>(b, g, r) += 1;
        }
    }
    for (int i = 0; i < bin_size; i++) {
        for (int j = 0; j < bin_size; j++) {
            for (int k = 0; k < bin_size; k++) {

                float normalized_value = ((float)hist3d.at<int>(i, j, k)) / normalizing_sum;
                features.push_back(normalized_value);
            }
        }
    }
}

void oneHistogramFeature(Mat& image, vector<float>& features) {

    const int bin_size = 8;
    const int Hsize = 256 / bin_size;

    float hist1d[bin_size] = {};
    float normalizing_sum = image.rows * image.cols;

    for (int x = 0; x < image.rows; x++) {
        for (int y = 0; y < image.cols; y++) {

            int pixel = image.at<uchar>(x, y);
            int index = pixel / Hsize;
            hist1d[index] += 1;
        }
    }
    for (int i = 0; i < bin_size; i++) {
        float normalized_value = ((float)hist1d[i]) / normalizing_sum;
        features.push_back(normalized_value);
    }
}

void TwoHistogramFeature(Mat& mag, Mat& ang, vector<float>& features) {

    const int bin_size_mag = 8;
    const int Hsize_mag = 256 / bin_size_mag;

    const int bin_size_ang = 9;
    const int Hsize_ang = 180 / bin_size_ang;

    Mat hist2d = Mat::zeros(bin_size_mag, bin_size_ang, CV_32S);
    float normalizing_sum = mag.rows * mag.cols;

    for (int x = 0; x < mag.rows; x++) {
        for (int y = 0; y < mag.cols; y++) {

            int pixel_mag = mag.at<uchar>(x, y);
            int mag_idx = pixel_mag / Hsize_mag;

            int pixel_ang = ang.at<float>(x, y);
            int ang_idx = pixel_ang / Hsize_ang;

                hist2d.at<int>(mag_idx, ang_idx) += 1;
        }
    }
    for (int i = 0; i < bin_size_mag; i++) {
        for (int j = 0; j < bin_size_ang; j++) {

            float normalized_value = ((float)hist2d.at<int>(i, j)) / normalizing_sum;
            features.push_back(normalized_value);  
        }
    }
}

void hsvHistogramFeature(Mat& image, vector<float>& features) {

    const int bin_size = 8;
    const int Hsize = 256 / bin_size;
    int dim3[3] = { bin_size, bin_size, bin_size };
    Mat hist3d = Mat::zeros(3, dim3, CV_32S);
    float normalizing_sum = image.rows * image.cols;

    for (int x = 0; x < image.rows; x++) {
        for (int y = 0; y < image.cols; y++) {

            Vec3b pixel = image.at<Vec3b>(x, y);
            int b = pixel[0] / Hsize;
            int g = pixel[1] / Hsize;
            int r = pixel[2] / Hsize;
            hist3d.at<int>(b, g, r) += 1;
        }
    }
    for (int i = 0; i < bin_size; i++) {
        for (int j = 0; j < bin_size; j++) {
            for (int k = 0; k < bin_size; k++) {

                float normalized_value = ((float)hist3d.at<int>(i, j, k)) / normalizing_sum;
                features.push_back(normalized_value);
            }
        }
    }
}

void multiHistogramFeature(Mat& image, vector<float>& features) {

    const int bin_size = 8;
    const int Hsize = 256 / bin_size;
    int dim3[3] = { bin_size, bin_size, bin_size };
    Mat hist3d_upper = Mat::zeros(3, dim3, CV_32S);
    Mat hist3d_lower = Mat::zeros(3, dim3, CV_32S);
    float normalizing_sum = image.rows * image.cols / 2;

    for (int x = 0; x < image.rows / 2; x++) {
        for (int y = 0; y < image.cols; y++) {

            Vec3b pixel = image.at<Vec3b>(x, y);
            int b = pixel[0] / Hsize;
            int g = pixel[1] / Hsize;
            int r = pixel[2] / Hsize;
            hist3d_upper.at<int>(b, g, r) += 1;
        }
    }
    for (int x = image.rows / 2; x < image.rows; x++) {
        for (int y = 0; y < image.cols; y++) {

            Vec3b pixel = image.at<Vec3b>(x, y);
            int b = pixel[0] / Hsize;
            int g = pixel[1] / Hsize;
            int r = pixel[2] / Hsize;
            hist3d_lower.at<int>(b, g, r) += 1;
        }
    }

    for (int i = 0; i < bin_size; i++) {
        for (int j = 0; j < bin_size; j++) {
            for (int k = 0; k < bin_size; k++) {

                float normalized_value = ((float)hist3d_upper.at<int>(i, j, k)) / normalizing_sum;
                features.push_back(normalized_value);
            }
        }
    }
    for (int i = 0; i < bin_size; i++) {
        for (int j = 0; j < bin_size; j++) {
            for (int k = 0; k < bin_size; k++) {

                float normalized_value = ((float)hist3d_lower.at<int>(i, j, k)) / normalizing_sum;
                features.push_back(normalized_value);
            }
        }
    }
}

void colorTextureFeature(Mat& image, vector<float>& features) {
    histogramFeature(image, features);
    Mat g = gaborFilter(image);
    oneHistogramFeature(g, features);
}

void customFeature(Mat& image, vector<float>& features) {
    Mat fullImageHSV, dst;
    for (int i = 1; i < 31; i = i + 2)
    {
        bilateralFilter(image, dst, i, i * 2, i / 2);

    }
    cvtColor(dst, fullImageHSV, COLOR_BGR2HSV);
    hsvHistogramFeature(fullImageHSV, features);
}