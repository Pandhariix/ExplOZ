#include "capitale.h"

Capitale::Capitale() : Ville()
{
    this->gouvernement = "none";
}

void Capitale::lol(){
    
}

Capitale::Capitale(int nbHabitants, double superficie, std::string name, std::string gouvernement) : Ville(nbHabitants, superficie, name)
{
    this->gouvernement = gouvernement;
}

std::string Capitale::getGouvernement()
{
    return this->gouvernement;
}

std::string Capitale::getBolosse()
{
    return this->gouvernement;
}
