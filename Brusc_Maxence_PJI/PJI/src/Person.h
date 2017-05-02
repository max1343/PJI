#ifndef PERSON_H_
#define PERSON_H_
#include <opencv2/core/core.hpp>


using namespace cv;
using namespace std;

class Person{
	public:
		Person();
		virtual ~Person();
		vector<cv::Rect> visage;
		int genre[20];
		int genreFinal;
		int genreDefine;
		int nbDecision;
		int femmeCount;
		int hommeCount;
		vector<int> frame;
		void addVisage(cv::Rect visage, Mat image,int frameNb);
};


#endif /* PERSON_H_ */
