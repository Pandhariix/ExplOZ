#ifndef CAPITALE_H
#define CAPITALE_H

#include <ville.h>

class Capitale : Ville
{

private:

    std::string gouvernement;
    std::string pelouse;

public:

    Capitale();
    Capitale(int nbHabitants, double superficie, std::string name, std::string gouvernement);
    std::string getGouvernement();
    std::string getBolosse();
    void lol();


};

#endif // CAPITALE_H
