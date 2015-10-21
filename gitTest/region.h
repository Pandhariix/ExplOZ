#ifndef REGION_H
#define REGION_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

class Region
{

private:

    int nbHabitants;
    std::string name;
    std::string pays;

public:

    Region();
    Region(std::string name, std::string pays, int nbHabitants);

    int getNbHabitants();
    std::string getName();
    std::string getPays();

};

#endif // REGION_H
