#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <pthread.h>
#include "opencv2/objdetect/objdetect.hpp"
#include "Person.h"
#include "Catalogue.h"
#include "Appariement.h"
#include "DetectionGenre.h"
#include "DetectionVisage.h"



using namespace std;
using namespace cv;

std::vector<Rect> detectAndDisplay(Mat frame);


int main()
{
    std::vector<Rect> faces;
    int count = 0;
	VideoCapture capture("/Users/pro/Desktop/PJI/video/test.mp4");//"/Users/pro/Desktop/PJI/video/test.mp4"
	if(!capture.isOpened())
		cout<<"fail to open!"<<endl;
	Mat frame,img2;
	DetectionVisage dv=DetectionVisage();
	Catalogue *c = new Catalogue();
	Appariement am;
	Appariement *app;
	AppariementMono amo;
	AppariementMultiSpatial amu;
	DetectionGenre dg;
	string genre;

	while (1) {
		capture>>frame;
		count++;
		faces=dv.detectAndDisplay(frame);
		 if(cvWaitKey(10) >= 0)
		            break;
		 if(faces.size()>0){
			 if(faces.size()==1 && c->nb_person<2)
				app=&amo;
			 else
				app=&amu;
			 app->associer(c,frame,faces,count);
		 }
		 /*Detection Carateristique*/
		 pthread_t tids[c->nb_person];
		for(int p=0; p<c->nb_person;p++){
			dg.my_pthread_create(&tids[p], NULL,&c->personnes[p] , &count,&frame);
		 }

		// cv::resize(frame,img2,Size(1000,1000),0,0,CV_INTER_LINEAR);
		 imshow( "Detected Face", frame);

	}
	delete c;
	capture.release();
	return 0;
}

