#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
 
using namespace cv;
using namespace std;
void HomomorphicFilter::butterworth_homomorphic_filter(Mat &dft_Filter, int D, int n, float high_h_v_TB, float low_h_v_TB)
{
Mat single(dft_Filter.rows, dft_Filter.cols, CV_32F);
Point centre = Point(dft_Filter.rows/2, dft_Filter.cols/2);
double radius;
float upper = (high_h_v_TB * 0.01);
float lower = (low_h_v_TB * 0.01);

// create a butterworth highpass filter
for(int i = 0; i < dft_Filter.rows; i++)
{
    for(int j = 0; j < dft_Filter.cols; j++)
    {
        radius = (double) sqrt(pow((i - centre.x), 2.0) + pow((double) (j - centre.y), 2.0));
        single.at<float>(i,j) =((upper - lower) * (1/(1 + pow((double) (D/radius), (double) (2*n))))) + lower;
    }
}
//Apply filter
mulSpectrums( dft_Filter, single, dft_Filter, 0);
}
void HomomorphicFilter::Shifting_DFT(Mat &fImage)
{
Mat tmp, q0, q1, q2, q3;
fImage = fImage(Rect(0, 0, fImage.cols & -2, fImage.rows & -2));
int cx = fImage.cols/2;
int cy = fImage.rows/2;
/*Rearrange the quadrants of Fourier image so that the origin is at the image center*/
q0 = fImage(Rect(0, 0, cx, cy));
q1 = fImage(Rect(cx, 0, cx, cy));
q2 = fImage(Rect(0, cy, cx, cy));
q3 = fImage(Rect(cx, cy, cx, cy));
/*We reverse q0 and q3*/
q0.copyTo(tmp);
q3.copyTo(q0);
tmp.copyTo(q3);

/*We reverse q1 and q2*/
q1.copyTo(tmp);
q2.copyTo(q1);
tmp.copyTo(q2);
}

void HomomorphicFilter::Fourier_Transform(Mat frame_bw, Mat &image_phase, Mat &image_mag)
{
Mat frame_log;
frame_bw.convertTo(frame_log, CV_32F);
/*Taking the natural log of the input*/
frame_log += 1;
log( frame_log, frame_log); 
Mat padded;
int M = getOptimalDFTSize(frame_log.rows);
int N = getOptimalDFTSize(frame_log.cols);
copyMakeBorder(frame_log, padded, 0, M - frame_log.rows, 0, N - frame_log.cols, BORDER_CONSTANT, Scalar::all(0));
Mat image_planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
Mat image_complex;
merge(image_planes, 2, image_complex);

dft(image_complex, image_complex);


phase(image_planes[0], image_planes[1], image_phase);
magnitude(image_planes[0], image_planes[1], image_mag);
}

void HomomorphicFilter::Inv_Fourier_Transform(Mat image_phase, Mat image_mag, Mat &inverseTransform)
{
/*Calculates x and y coordinates of 2D vectors from their magnitude and angle.*/
Mat result_planes[2];
polarToCart(image_mag, image_phase, result_planes[0], result_planes[1]);

/*Creates one multichannel array out of several single-channel ones.*/
Mat result_complex;
merge(result_planes, 2, result_complex);

/*Make the IDFT*/
dft(result_complex, inverseTransform, DFT_INVERSE|DFT_REAL_OUTPUT);
/*exponential*/
exp(inverseTransform, inverseTransform);
}


int main( int argc, char** argv ) 
{
 
    Mat image1, fin,image;
     float sum;
    image1 = imread("peppers.tif", IMREAD_GRAYSCALE);   // Read the file
    
Mat log_img;
log(float_img, log_img);
Mat image_phase, image_mag;
    HomomorphicFilter().Fourier_Transform(frame_bw, image_phase, image_mag);
   //Shifting the DFT//
  HomomorphicFilter().Shifting_DFT(image_mag);
   //Butterworth homomorphic filter//
    int high_h_v_TB = 100;
    int low_h_v_TB = 30;
    int D = 10;
    int order = 2;
    HomomorphicFilter().butterworth_homomorphic_filter(image_mag, D, order, high_h_v_TB, low_h_v_TB);
   //Shifting the DFT//
    HomomorphicFilter().Shifting_DFT(image_mag);
    Mat inverseTransform;
    HomomorphicFilter().Inv_Fourier_Transform(image_phase, image_mag, inverseTransform);
    imshow("Result", inverseTransform);
return 0;
}
