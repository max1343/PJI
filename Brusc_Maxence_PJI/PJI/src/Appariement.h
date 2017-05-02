#ifndef APPARIEMENT_H_
#define APPARIEMENT_H_
#include <opencv2/core/core.hpp>
#include <iostream>
#include "Catalogue.h"
#include "Person.h"

using namespace std;
using namespace cv;
class Appariement {
	public:
		Appariement();
		virtual ~Appariement();
		virtual int associer(Catalogue *c, Mat image, vector<cv::Rect> visages, int frameNb);
		float perIntersection(Rect r1, Rect r2);
};

class AppariementMono:public Appariement {
public:
	virtual int associer(Catalogue *c, Mat image, std::vector<Rect> visages, int frameNb);
};

class AppariementMultiSpatial:public Appariement  {
	virtual int associer(Catalogue *c, Mat image, std::vector<Rect> visages,int frameNb);
};

/*class AppariementMultiSpatialApp {
	virtual int associer(Catalogue c, Mat image, std::vector<Rect> visages, int frameNb);
};*/

#endif /* APPARIEMENT_H_ */
