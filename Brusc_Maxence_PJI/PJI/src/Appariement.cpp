#include "Appariement.h"

Appariement::Appariement() {
}

Appariement::~Appariement() {
}

int Appariement::associer(Catalogue *c, Mat image, vector<cv::Rect> visages, int frameNb){
}



float Appariement::perIntersection(Rect r1, Rect r2){
	float area1 = r1.area();
	float area2 = r2.area();
	if (r1.x > r2.x+r2.width) { return 0.0; }
	if (r1.y > r2.y+r2.height) { return 0.0; }
	if (r1.x+r1.width < r2.x) { return 0.0; }
	if (r1.y+r1.height < r2.y) { return 0.0; }
	float colInt =  min(r1.x+r1.width,r2.x+r2.width) - max(r1.x, r2.x);
	float rowInt =  min(r1.y+r1.height,r2.y+r2.height) - max(r1.y,r2.y);
	float intersection = colInt * rowInt;
	return intersection / (area1 + area2 - intersection);

}


int AppariementMono::associer(Catalogue *c, Mat image, vector<cv::Rect> visages,int frameNb){
    if (c->nb_person>0) {

    	c->personnes[0].addVisage(visages.at(0),image,frameNb);
    	return 0;
    }
    c->addPerson();
    c->personnes.back().addVisage(visages[0],image(visages.at(0)),frameNb);
	return 1;
 }



int AppariementMultiSpatial::associer(Catalogue *c, Mat image, std::vector<Rect> visages,int frameNb){
	int i;
	int max = 0;
	int nbPerson = c->nb_person;
	int nbVisage = visages.size();
	vector <int>associer(nbVisage,-1);
	for( int i = 0; i < nbVisage; i++ ){
		for(int j=0; j<nbPerson; j++){
			float percent = perIntersection(c->personnes[j].visage.back(),visages[i]);
			if(percent>max){
				max = percent;
				associer[i]=j;
			}
		}
	}
	for (i=0; i < nbVisage; i ++) {
		if(associer[i]!=-1)
			c->personnes[associer[i]].addVisage(visages[i],image(visages.at(i)),frameNb);
		else{
			Person person;
			person.addVisage(visages[i],image(visages.at(i)),frameNb);
			c->addPerson(person);
		}
	}
	if(nbVisage<nbPerson){
		   for(vector<Person>::iterator it=c->personnes.begin(); it!=c->personnes.end(); )
		    {
		        if(it->frame.back() != frameNb)
		        {
		            c->deletePerson(it);
		        }
		        else
		        {
		            ++it;
		        }
		    }
	}
	return c->nb_person;
}
