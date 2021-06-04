#include "library2.h"
#include "dealership.h"

void *Init(){
    Dealership* ds= new Dealership();
    return ds;
}

StatusType AddAgency(void *DS){
    if(DS==NULL){
        return INVALID_INPUT;
    }
    Dealership* DS_convert = (Dealership*)DS;
    Agency** temp = new Agency*[DS_convert->num_of_agencies+1];
    for(int i=0;i<DS_convert->num_of_agencies;i++){
        temp[i]=DS_convert->agencies[i];
    }
    temp[DS_convert->num_of_agencies]=new Agency(DS_convert->num_of_agencies);
    delete[] DS_convert->agencies;
    DS_convert->agencies = temp;
    DS_convert->num_of_agencies++;
    return SUCCESS;
}

StatusType SellCar(void *DS, int agencyID, int typeID, int k);

StatusType UniteAgencies(void *DS, int agencyID1, int agencyID2);

StatusType GetIthSoldType(void *DS, int agencyID, int i, int* res);

void Quit(void** DS);