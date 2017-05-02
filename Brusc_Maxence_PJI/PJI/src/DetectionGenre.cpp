#include "DetectionGenre.h"


DetectionGenre::DetectionGenre() {
	//this->genreDefine = 4;
	//this->femmeCount = 0;
	//this->hommeCount = 0;
	//this->nbDecision = 20;
}

DetectionGenre::~DetectionGenre() {
}

int DetectionGenre::getGenre(Person &p, int i){
	p.genre[i] = rand()%2;
	return p.genre[i];
}

int DetectionGenre::predefinedGenre(Person* p, int frameNb, Mat img){
	int i = frameNb-1 % p->nbDecision;
	if(p->genreFinal!=-1)
		return p->genreFinal;
	else{
		p->genre[i] = this->getGenre(*p,i);
	}
	if(i == p->nbDecision){
		p->genreFinal = p->femmeCount > p->hommeCount? 0:1;
		return p->genreFinal;
	}
	else if(p->genreDefine==0){
		p->genreFinal = p->genre[i];
		return p->genreFinal;
	}else{
		if(i>1){
			if(p->genre[i]==p->genre[i-1]){
				p->genreDefine--;
			}
			else
				p->genreDefine = 4;
		}

		if(p->genre[i]==0)
			p->femmeCount += 1;
		else if(p->genre[i] == 1)
			p->hommeCount += 1;
		return p->genre[i];
	}
}

void* printGenre(Person* p, int* frameNb,Mat* img){
	int genre;
	string text;
	stringstream sstm;
	DetectionGenre dg;
	Rect r = p->visage.back();
	genre = dg.predefinedGenre(p,*frameNb, *img);


	if(genre == 1)
		text = "homme";
	else if(genre == 0)
		text = "femme";

	sstm <<text;
	text = sstm.str();
	putText(*img, text, cvPoint( r.x+int(0.3*r.width), r.y-5),CV_FONT_HERSHEY_COMPLEX,0.7,Scalar(0,255,0));
	return 0;
}





void * sub_thread_entry(void * arg)
{
    ARGS args;

    args.callback = ((ARGS *)arg)->callback;
    args.arg1 = ((ARGS *)arg)->arg1;
    args.arg2 = ((ARGS *)arg)->arg2;
    args.arg3 = ((ARGS *)arg)->arg3;
    free(arg);

    return args.callback(args.arg1, args.arg2,args.arg3);
}

int DetectionGenre::my_pthread_create(pthread_t *thread, const pthread_attr_t *attr, Person *arg1, int * arg2, Mat* arg3)
{
    ARGS * args;

    if (NULL == (args=(ARGS *)malloc(sizeof(ARGS))))
        return -1;
    args->callback = printGenre;
    args->arg1 = arg1;
    args->arg2 = arg2;
    args->arg3 = arg3;

    return pthread_create(thread, attr, sub_thread_entry, args);
}

