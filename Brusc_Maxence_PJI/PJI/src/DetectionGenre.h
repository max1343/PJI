#ifndef DETECTIONGENRE_H_
#define DETECTIONGENRE_H_

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include "Person.h"
#include <pthread.h>

using namespace std;
using namespace cv;


typedef void * (*FUNCALLBACK)(Person * arg1, int * arg2, Mat* arg3);
typedef struct {
   FUNCALLBACK callback;
   Person * arg1;
   int * arg2;
   Mat*	arg3;
} ARGS;

class DetectionGenre{
	public:
		/*int genreDefine;
		int femmeCount;
		int hommeCount;
		int nbDecision;*/
		DetectionGenre();
		virtual ~DetectionGenre();
        int getGenre(Person &p, int i);
        int predefinedGenre(Person* p,int frameNb, Mat img);
        //void printGenre(Person p,int frameNb, Mat img);
		//void * sub_thread_entry(void * arg);
		int my_pthread_create(pthread_t *thread, const pthread_attr_t *attr,Person *arg1, int * arg2, Mat* arg3);

};





#endif /* DETECTIONGENRE_H_ */
