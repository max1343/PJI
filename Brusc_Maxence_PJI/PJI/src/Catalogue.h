#ifndef CATALOGUE_H_
#define CATALOGUE_H_
#include "Person.h"
using namespace std;
using namespace cv;

class Catalogue
{
	public:
	 	 int nb_person;
	     std::vector<Person> personnes;
	     Catalogue();
	     ~Catalogue();
	     int get_number();
	     void addPerson();
	     void addPerson(Person p);
	     void deletePerson(vector<Person>::iterator it);


};

#endif /* CATALOGUE_H_ */
