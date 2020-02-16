#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<cmath>
 
using namespace std;
using namespace cv;
 
int main()
{
 
      Mat src ;
      
      int m , n;
      /// Load an image
      src = imread("cameraman.tif", CV_LOAD_IMAGE_GRAYSCALE);
       
     m = src.rows;
     n = src.cols;

Mat pad(2*m, 2*n, CV_8UC1, Scalar(0));

     for(int i =0; i< 2*m; i++){
          for(int j=0 ; j< 2*n; j++){
              if(i<m && j<n) 
                  pad.at<uchar>(i,j) = src.at<uchar>(i,j);
              else
                   pad.at<uchar>(i,j)=0;
          }
     }

   for(int i =0; i< m; i++){
          for(int j=0 ; j< n; j++){
            int k = i+j;
           pad.at<uchar>(i,j) = pow(-1, k)*pad.at<uchar>(i,j);   
              
          }
     }

Mat dft(2*m, 2*n, CV_8UC1, Scalar(0));


for( int u=0; u<100; u++){
 for( int v=0; v<100; v++){
  for( int i=0; i<m; i++){
   for( int j=0; j<n; j++){
     float l= -((u*i/m) + (v*j/n));
     float  a=cos(l);
     float  b=sin(l);
     float c = sqrt(a*a + b*b);
     dft.at<uchar>(u,v)=dft.at<uchar>(u,v) + pad.at<uchar>(i,j)*c;
   }
  }
 }
} 
    





        


  namedWindow("final");
        imshow("final", dft);
 
 waitKey();
    return 0;
}
