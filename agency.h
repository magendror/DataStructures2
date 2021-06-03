#ifndef AGENCY_H
#define AGENCY_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "salestree.h"
#include "typetree.h"

class Agency{
public:
    int num_of_agency;
    Agency* father;
    SalesNode* sales_key;
    TypeNode* type_tree;
    Agency(int num_of_agency, Agency* father=NULL,SalesNode* sales_key=NULL, TypeNode* type_tree=NULL);
    ~Agency()=default;
    bool operator>(CarType &model2);
};

Agency::Agency(int num_of_agency, Agency* father,SalesNode* sales_key, TypeNode* type_tree):
        num_of_agency(num_of_agency),father(father),sales_key(sales_key),type_tree(type_tree)
{
}


#endif