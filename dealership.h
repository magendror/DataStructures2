#ifndef DEALERSHIP_H
#define DEALERSHIP_H
#include "salestree.h"
#include "typetree.h"
#include "cars.h"
#include "agency.h"

class Dealership
{
public:
    Agency** agencies;
    int num_of_agencies;
    int array_size;
    Dealership();
    ~Dealership();
};

Dealership::Dealership() : agencies(new Agency*[1]),num_of_agencies(0), array_size(1)
{
}

Dealership::~Dealership() {}
#endif