#include<iostream>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
 
using namespace std;
using namespace cv;

void createFilter(double Kernel[][5])
{      
    // set standard deviation to 1.0
    double sigma = 1.0;
    double r, s = 2.0 * sigma * sigma;
 
    // sum is for normalization
    double sum = 0.0;
 
 
    // generate 5x5 kernel
    for (int x = -2; x <= 2; x++)
    {
        for(int y = -2; y <= 2; y++)
        {
            
            r = sqrt(x*x + y*y);
            Kernel[x + 2][y + 2] =( (exp(-(r*r)/s))/sqrt((M_PI * s)));
            sum += Kernel[x + 2][y + 2];
            
        }
    }
 
  // normalize the Kernel
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            Kernel[i][j] /= sum;
   
}
 
int main()
{
 
      Mat src, dst;
      float sum;
 
      /// Load an image
      src = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);
 
      if( !src.data )
      { return -1; }
        
       double Kernel[5][5];
    createFilter(Kernel);
          
         
        //convolution operation
        for(int y = 1; y < src.rows - 1; y++){
            for(int x = 1; x < src.cols - 1; x++){
                sum = 0.0;
                for(int k = -2; k <= 2;k++){
                    for(int j = -2; j <=2; j++){
                        sum = sum + Kernel[j+2][k+2]*src.at<uchar>(y - j, x - k);
                    }
                }
                dst.at<uchar>(y,x) = sum;
            }
         }



        namedWindow("final");
        imshow("final", dst);
        imwrite("final.jpg",dst);
        namedWindow("initial");
        imshow("initial", src);
 
      waitKey();
 
 
    return 0;
}
