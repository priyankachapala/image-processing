#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
 
using namespace cv;
using namespace std;
//void copyMakeBorder(InputArray src, OutputArray dst, int top, int bottom, int left, int right, int borderType, const Scalar& value=Scalar() )
 
int main( int argc, char** argv ) 
{
 
    Mat image1, fin,image,HSV;
     float sum;
    image1 = imread("strawberry.tif", CV_LOAD_IMAGE_COLOR);   // Read the file
   copyMakeBorder( image1,image , 0.02*image1.rows, 0.02*image1.cols,0.02*image1.rows, 0.02*image1.cols, BORDER_CONSTANT, 0 );
    
    
 namedWindow( "Original Image", CV_WINDOW_AUTOSIZE );
 imshow( "Original Image", image );
 
    Mat rgbchannel[3],dst[3],hsv[3];
    cvtColor(image, HSV, CV_BGR2HSV);
    // The actual splitting.
    split(image, rgbchannel);
     split(image, hsv);
  dst[2] = rgbchannel[0].clone();
        for(int y = 0; y <rgbchannel[0] .rows; y++)
            for(int x = 0; x < rgbchannel[0].cols; x++)
                dst[2].at<uchar>(y,x) = 0.0;
  dst[1] = rgbchannel[1].clone();
        for(int y = 0; y <rgbchannel[1] .rows; y++)
            for(int x = 0; x < rgbchannel[1].cols; x++)
                dst[1].at<uchar>(y,x) = hsv[1].at<uchar>(y,x);

 dst[0] = rgbchannel[2].clone();
        for(int y = 0; y <rgbchannel[2] .rows; y++)
            for(int x = 0; x < rgbchannel[2].cols; x++)
                dst[0].at<uchar>(y,x) = hsv[0].at<uchar>(y,x);

float Kernel[5][5] = {
                            {1/25.0, 1/25.0, 1/25.0, 1/25.0, 1/25.0},
                            {1/25.0, 1/25.0, 1/25.0, 1/25.0, 1/25.0},
                            {1/25.0, 1/25.0, 1/25.0, 1/25.0, 1/25.0},
                            {1/25.0, 1/25.0, 1/25.0, 1/25.0, 1/25.0},
                            {1/25.0, 1/25.0, 1/25.0, 1/25.0, 1/25.0},
                           };
 
  
     for(int y=1; y<rgbchannel[0].rows-1; y++){
       for(int x=1; x<rgbchannel[0].cols-1; x++){
            sum=0.0; 
           for(int k=-1; k<=1;k++){
             for(int j=1; j<=1; j++){
                  sum = sum +Kernel[j][k]*hsv[2].at<uchar>(y-j,x-k);
                    }
                }
            dst[2].at<uchar>(y,x)=sum-hsv[2].at<uchar>(y,x);;
              }
            }
        
    
                                 


/*namedWindow("HUE",CV_WINDOW_AUTOSIZE);
 imshow("Hue", hsv[0]);

 
 namedWindow("saturation",CV_WINDOW_AUTOSIZE);
 imshow("saturation", hsv[1]);
 
 namedWindow("Value",CV_WINDOW_AUTOSIZE);
 imshow("value", dst[2]);*/


   merge(dst,3, fin);
namedWindow("final",CV_WINDOW_AUTOSIZE);
 imshow("final", fin);
imwrite("hsv.jpg", fin);                        
       
     


 
    waitKey(0);//Wait for a keystroke in the window
    return 0;
}