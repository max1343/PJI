#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

int main( )
{
    Mat image;
    Mat img2;
    string text;
    stringstream sstm;
    image = imread("/Users/pro/Desktop/PJI/photo/face3.jpg", CV_LOAD_IMAGE_COLOR);

    // Load Face cascade (.xml file)
    CascadeClassifier face_cascade;
    face_cascade.load( "/Users/pro/Applications/opencv-3.1.0/data/haarcascades/haarcascade_frontalface_alt2.xml" );

    // Detect faces
    std::vector<Rect> faces;
    face_cascade.detectMultiScale( image, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
    cout<<faces.size()<<endl;
    // Draw circles on the detected faces
    for( int i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        ellipse( image, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
    }
    sstm << faces.size() << "personnes";
    text = sstm.str();
    putText(image, text, cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 2, cvScalar(0, 0, 255), 1, CV_AA);
    cv::resize(image,img2,Size(1000,1000),0,0,CV_INTER_LINEAR);
   // imshow( "Detected Face", image );
    imshow( "Detected Face", img2);
    waitKey(0);
    return 0;
}
