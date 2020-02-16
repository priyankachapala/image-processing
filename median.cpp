#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;
int main()
{
    // read the image
    Mat image = imread("rimage.tiff", CV_LOAD_IMAGE_GRAYSCALE);
   // Generate the histogram
    int histogram[256];
    for(int i = 0; i < 256; i++)
    {
        histogram[i] = 0;
    }
 // calculate the no of pixels for each intensity values
    for(int y = 0; y < image.rows; y++)
        for(int x = 0; x < image.cols; x++)
            histogram[(int)image.at<uchar>(y,x)]++;
    int size = image.rows * image.cols;
    // Calculate the probability of each intensity
    float Prob[256];
    for(int i = 0; i < 256; i++)
    {
        Prob[i] = (double)histogram[i] / size;
    }
 
    // Generate cumulative frequency 
    float cprob[256];
   cprob[0] = cprob[0];
 
    for(int i = 1; i < 256; i++)
    {
        cprob[i] = Prob[i] + cprob[i-1];
}
	
  float min=10;
int median;
    for(int j = 1; j < 256; j++)
    {
    if(cprob[j]>=0.5)
    {
    
    if(cprob[j]<min)
    {min=cprob[j];
    median=j;}
    }}
 cout<<"median is"<<median<<endl;
return 0;
}
