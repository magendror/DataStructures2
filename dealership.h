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
    Dealership();
    ~Dealership();
};

Dealership::Dealership() : agencies(NULL),num_of_agencies(0)
{
}

Dealership::~Dealership() {}
#endif