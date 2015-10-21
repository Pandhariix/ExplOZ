#include "region.h"

Region::Region()
{
    this->name = "none";
    this->pays = "none";
    this->nbHabitants = 0;
}

Region::Region(std::string name, std::string pays, int nbHabitants)
{
    this->name = name;
    this->pays = pays;
    this->nbHabitants = nbHabitants;
}

std::string Region::getName()
{
    return this->name;
}
std::string Region::getPays()
{
    return this->pays;
}
int Region::getNbHabitants()
{
    return this->nbHabitants;
}

