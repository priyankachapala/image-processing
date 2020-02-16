
#include <iostream>
#include <stdio.h>
#include <cmath>

#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;
int main()
{
    // read the image
    Mat image = imread("image.tif", CV_LOAD_IMAGE_GRAYSCALE);
Mat timage = imread("timage.tif", CV_LOAD_IMAGE_GRAYSCALE);
Mat nimage;
nimage=timage.clone();
for(int y = 0; y < timage.rows; y++)
{
        for(int x = 0; x <timage.cols; x++)
{
nimage.at<uchar>(y,x)=0.0;
}}


   // Generate the histogram
    int histogram[256];
    for(int i = 0; i < 256; i++)
    {
        histogram[i] = 0;
    }
int k,i,j;
	

float T[256];

 for(k=0;k<256;k++){
T[k]=0;
    for(int y = 0; y < image.rows; y++)
{
        for(int x = 0; x < image.cols; x++)
{

if(image.at<uchar>(y,x)==k)
T[k]=T[k]+(timage.at<uchar>(y,x));
}}}


 
for(int y = 0; y < image.rows; y++)
        for(int x = 0; x < image.cols; x++)
            histogram[(int)image.at<uchar>(y,x)]++;


for(k=0;k<256;k++)
{
if(histogram[k]>0)
{
T[k]=T[k]/histogram[k];
T[k]=round(T[k]);
cout<<"T["<<k<<"]"<<T[k]<<endl;
}
}



for(int y = 0; y < image.rows; y++){
        for(int x = 0; x < image.cols; x++)
{

nimage.at<uchar>(y,x)=T[(int)image.at<uchar>(y,x)];}}

namedWindow("output",WINDOW_AUTOSIZE);
imshow("output",nimage);

namedWindow("target",WINDOW_AUTOSIZE);
imshow("target",timage);

waitKey(0);
	
	

return 0;
}
