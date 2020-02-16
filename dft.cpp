#include "opencv2/core.hpp"
 #include "opencv2/imgproc.hpp"
 #include "opencv2/imgcodecs.hpp"
 #include "opencv2/highgui.hpp"
 
 #include <iostream>
 
 using namespace cv;
 using namespace std;
 
 static void help(char* progName)
 {
     cout << endl
         <<  "This program demonstrated the use of the discrete Fourier transform (DFT). " << endl
         <<  "The dft of an image is taken and it's power spectrum is displayed."          << endl
         <<  "Usage:"                                                                      << endl
         << progName << " [image_name -- default ../data/lena.jpg] "               << endl << endl;
 }
 
 int main(int argc, char ** argv)
 {
     /*help(argv[0]);
 
     const char* filename = argc >=2 ? argv[1] : "inputImage.pgm";*/
 
     Mat I = imread("cameraman.tif", IMREAD_GRAYSCALE);
     if( I.empty())
         return -1;
 
     Mat padded;                            //expand input image to optimal size
     int m = getOptimalDFTSize( I.rows );
     int n = getOptimalDFTSize( I.cols ); // on the border add zero values
     copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));
     imshow("spectrum magnitude", padded);
 
     Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
     Mat complexI;
     merge(planes, 2, complexI);         // Add to the expanded another plane with zeros
 
     dft(complexI, complexI);            // this way the result may fit in the source matrix
 
     // compute the magnitude and switch to logarithmic scale
     // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
     split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
     magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
     Mat magI = planes[0];
 
     magI += Scalar::all(1);                    // switch to logarithmic scale
     log(magI, magI);
    
     
    
 
     normalize(magI, magI, 0, 1, NORM_MINMAX); // Transform the matrix with float values into a
                                             // viewable image form (float between values 0 and 1).
     resize(magI,magI,Size(magI.cols,magI.rows));
     namedWindow( "spectrum magnitude",CV_WINDOW_AUTOSIZE );
     //imshow("Input Image"       , I   );    // Show the result
     imshow("spectrum magnitude", magI);
     waitKey();
 
     return 0;
 }
