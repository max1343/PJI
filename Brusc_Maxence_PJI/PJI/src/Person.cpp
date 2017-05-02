#include "Person.h"
#include <iostream>

Person::Person() {
	this->genreFinal=-1;
	this->genreDefine = 4;
	this->nbDecision = 20;
	this->femmeCount = 0;
	this->hommeCount = 0;
}

Person::~Person() {
}

void Person::addVisage(cv::Rect visage, Mat image,int frameNb){
	this->visage.push_back(visage);
	this->frame.push_back(frameNb);
	//this->visage[frameNb] = visage;
	//this->visage.insert(this->visage.begin()+frameNb,visage);
}



