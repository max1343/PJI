#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/objdetect/objdetect.hpp"

#include "DetectionVisage.h"

DetectionVisage::DetectionVisage() {
	// TODO Auto-generated constructor stub

}

DetectionVisage::~DetectionVisage() {
	// TODO Auto-generated destructor stub
}

std::vector<Rect> DetectionVisage::detectAndDisplay(Mat frame)
{
	 	Mat image;
	    Mat img2;
	    string text;
	    stringstream sstm;
	    image = frame;
	    CascadeClassifier face_cascade;
	    	    face_cascade.load( "/Users/pro/Applications/opencv-3.1.0/data/haarcascades/haarcascade_frontalface_alt2.xml" );

	    	    std::vector<Rect> faces;
	    	    face_cascade.detectMultiScale( image, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );

	    for( vector<Rect>::const_iterator i=faces.begin(); i < faces.end(); i++ )
	    	    {
	    	        Point center( i->x + i->width*0.5, i->y + i->height*0.5 );
	    	        ellipse( image, center, Size( i->width*0.5, i->height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
	    	    }
	    sstm << faces.size() << " personnes";
	    text = sstm.str();
	    putText(image, text, cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 2, cvScalar(0, 0, 255), 1, CV_AA);
	    //cv::resize(frame,img2,Size(1000,1000),0,0,CV_INTER_LINEAR);
	    //imshow( "Detected Face", img2);
	    return faces;
}


