#include "ville.h"


Ville::Ville()
{
    this->nbHabitants = 0;
    this->superficie = 0;
    this->name = "unnamed";
}

Ville::Ville(int nbHabitants, double superficie, std::string name)
{
    this->nbHabitants = nbHabitants;
    this->superficie = superficie;
    this->name = name;
}



int Ville::getNbHabitants()
{
    return this->nbHabitants;
}

double Ville::getSuperficie()
{
    return this->superficie;
}

std::string Ville::getName()
{
    return this->name;
}



void Ville::displayInfos()
{
    std::cout<<this->name<<" : "<<this->nbHabitants<<" habitants, "<<this->superficie<<" metres carres"<<std::endl;
}

