#include "filter.h"

#define PI 3.14159265
using namespace cv;

Mat sobelXFilter(  Mat& src) {

    Mat dst(src.size(), CV_32F);

    int sobelX_hor[] = { -1, 0, 1 }; // 1x3
    int sobelX_ver[] = { 1,
                         2,
                         1 }; // 3x1

    short sum;

    Mat temp(src.size(), CV_16SC1);

    for (int x = 1; x < src.rows - 1; x++) {
        for (int y = 1; y < src.cols - 1; y++) {

            sum = 0;

            for (int i = x - 1; i <= x + 1; i++) {

                int intensity = src.at<uchar>(i, y);
                int filter_point = sobelX_hor[i - (x - 1)];
                sum += intensity * filter_point;
            }

            temp.at<short>(x, y) = sum;

        }
    }

    for (int x = 1; x < temp.rows - 1; x++) {
        for (int y = 1; y < temp.cols - 1; y++) {

            sum = 0;

            for (int j = y - 1; j <= y + 1; j++) {

                short intensity = temp.at<short>(x, j);
                int filter_point = sobelX_ver[j - (y - 1)];
                sum += intensity * filter_point;

            }
            dst.at<float>(x, y) = abs(sum/ 4);
        }
    }

    return dst;
}

Mat sobelYFilter(  Mat& src) {

    Mat dst(src.size(), CV_32F);

    int sobelY_hor[] = { 1, 2, 1 }; // 1x3
    int sobelY_ver[] = { -1,
                          0,
                          1 }; // 3x1

    short sum;

    Mat temp(src.size(), CV_16SC1);

    for (int x = 1; x < src.rows - 1; x++) {
        for (int y = 1; y < src.cols - 1; y++) {

            sum = 0;

            for (int i = x - 1; i <= x + 1; i++) {

                int intensity = src.at<uchar>(i, y);
                int filter_point = sobelY_hor[i - (x - 1)];
                sum += intensity * filter_point;
            }

            temp.at<short>(x, y) = sum;

        }
    }

    for (int x = 1; x < temp.rows - 1; x++) {
        for (int y = 1; y < temp.cols - 1; y++) {

            sum = 0;

            for (int j = y - 1; j <= y + 1; j++) {

                short intensity = temp.at<short>(x, j);
                int filter_point = sobelY_ver[j - (y - 1)];
                sum += intensity * filter_point;

            }

            dst.at<float>(x, y) = abs(sum / 4);
        }
    }

    return dst;
}

Mat magnitude(  Mat& sx,   Mat& sy,   Mat& src) {
    Mat dst(src.size(), CV_32S);

    for (int i = 0; i < sx.rows; i++) {
        for (int j = 0; j < sx.cols; j++) {

            float x = sx.at<float>(i, j);
            float y = sy.at<float>(i, j);

            dst.at<float>(i, j) = sqrtf((x * x) + (y * y));
            
        }
    }
    Mat scaled;
      convertScaleAbs(dst, scaled, 1, 0);
    return scaled;
}

Mat orientation(  Mat& sx,   Mat& sy,   Mat& src) {
    Mat dst(src.size(), CV_32S);
    float m = -100;

    for (int i = 0; i < sx.rows; i++) {
        for (int j = 0; j < sx.cols; j++) {

            float x = sx.at<float>(i, j);
            float y = sy.at<float>(i, j);
            if (m < (atan(y / x) * 180 / PI))
                m = (atan(y / x) * 180 / PI);

            float val = (int)((( (float)atan(y / x)) * 180) / PI) + 90;
            if (val == 180)
                val = 179;
            dst.at<float>(i, j) = val;
        }
    }
    return dst;

}

Mat gaborFilter(  Mat outImg) {
    Mat gaborOut, outAsFloat, gaborImage;
    outImg.convertTo(outAsFloat, CV_32F);
    Mat gaborKernel = getGaborKernel(  Size(30, 30), 1, 0, 1, 0.02);
    filter2D(outAsFloat, gaborOut, CV_32F, gaborKernel);
    double xmin[4], xmax[4];
    minMaxIdx(gaborOut, xmin, xmax);
    gaborOut.convertTo(gaborImage, CV_8U, 255.0 / (xmax[0] - xmin[0]), -255 * xmin[0] / (xmax[0] - xmin[0]));
    return gaborImage;
}

