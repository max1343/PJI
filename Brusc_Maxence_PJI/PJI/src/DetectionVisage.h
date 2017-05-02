#ifndef DETECTIONVISAGE_H_
#define DETECTIONVISAGE_H_

#include <opencv2/core/core.hpp>
using namespace cv;
using namespace std;

class DetectionVisage {
	public:
		DetectionVisage();
		virtual ~DetectionVisage();
		std::vector<Rect> detectAndDisplay(Mat frame);
};


#endif /* DETECTIONVISAGE_H_ */
