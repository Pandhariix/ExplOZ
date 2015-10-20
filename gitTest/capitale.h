#ifndef CAPITALE_H
#define CAPITALE_H

#include <ville.h>

class Capitale : Ville
{

private:

    std::string gouvernement;
    std::string pelouse;
	std::string pelouse;
public:

    Capitale();
    Capitale(int nbHabitants, double superficie, std::string name, std::string gouvernement);
    std::string getGouvernement();


};

#endif // CAPITALE_H
