#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "opencv2/objdetect/objdetect.hpp"
#include <pthread.h>
#include "Catalogue.h"
#include "Appariement.h"



Catalogue::Catalogue(){
	this->nb_person = 0;
	this->personnes.clear();
}

void Catalogue::addPerson(){
	Person p;
	this->personnes.push_back(p);
	this->nb_person++;
}

void Catalogue::addPerson(Person p){
	this->personnes.push_back(p);
	this->nb_person++;
}

void Catalogue::deletePerson(vector<Person>::iterator it){
	this->personnes.erase(it);
	//vector<Person>(this->personnes).swap(this->personnes);
	this->nb_person--;

}



int Catalogue::get_number(){
	   return nb_person;
}

Catalogue::~Catalogue(){
	cout<<"~"<<endl;
}




