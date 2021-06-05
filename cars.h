#ifndef CARS_H
#define CARS_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class CarType{
public:
    int type_id;
    int sales;
    bool in_type_tree;
    CarType* sales_key;
    CarType(int type_id, int sales=0,bool in_type_tree=true, CarType* sales_key=NULL);
    ~CarType()=default;
    bool operator>(CarType &model2);
};

CarType::CarType(int type_id, int sales,bool in_type_tree, CarType* sales_key) : 
                        type_id(type_id),sales(sales),in_type_tree(in_type_tree),sales_key(sales_key)
{}


bool CarType::operator>(CarType &type2)
{
    if(in_type_tree==true){
        if (type_id > type2.type_id){
            return true;
        }
        else{
            return false;
        }
    }
    else{
        if (sales > type2.sales){
            return true;
        }
        else if (type2.sales > sales) {
            return false;
        }
        else{
            if (type_id > type2.type_id){
                return true;
            }
            else{
                return false;
            }
        }
    }  
}

int max_int(int a, int b) {
  return (a > b) ? a : b;
}


#endif