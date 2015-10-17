#ifndef VILLE_H
#define VILLE_H

#include <iostream>

class Ville
{

protected:

    std::string name;

    int nbHabitants;
    double superficie;
    double pays;

public:

    Ville();
    Ville(int nbHabitants, double superficie, std::string name);

    int getNbHabitants();
    double getSuperficie();
    std::string getName();

    void displayInfos();

};

#endif // VILLE_H
