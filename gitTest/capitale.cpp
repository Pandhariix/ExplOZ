#include "capitale.h"

Capitale::Capitale() : Ville()
{
    this->gouvernement = "none";
}

Capitale::Capitale(int nbHabitants, double superficie, std::string name, std::string gouvernement) : Ville(nbHabitants, superficie, name)
{
    this->gouvernement = gouvernement;
}

std::string Capitale::getGouvernement()
{
    return this->gouvernement;
}