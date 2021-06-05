#include "library2.h"
#include "dealership.h"

//Insert Static Functions Here//
static Agency* getRoot(Agency* current){
    while(current->father!=NULL){
        current=current->father;
    }
    return current;
}

static void clearTypeTree(TypeNode* current){
    if (current==NULL){
        return;
    }
    clearTypeTree(current->left);
    clearTypeTree(current->right);
    delete current->key;
    delete current;
}

static void clearSalesTree(SalesNode* current){
    if (current==NULL){
        return;
    }
    clearSalesTree(current->left);
    clearSalesTree(current->right);
    delete current->key;
    delete current;
}
//End of Static Functions//

//Insert Main Functions Here//
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

StatusType UniteAgencies(void *DS, int agencyID1, int agencyID2){
    if(DS==NULL||agencyID1<0||agencyID2<0){
        return INVALID_INPUT;
    }
    Dealership* DS_convert = (Dealership*)DS;
    if(agencyID1>=DS_convert->num_of_agencies||agencyID2>=DS_convert->num_of_agencies){
        return FAILURE;
    }
    if(agencyID1==agencyID2){
        return SUCCESS;
    }
    Agency* root1= getRoot(DS_convert->agencies[agencyID1]);
    Agency* root2= getRoot(DS_convert->agencies[agencyID2]);
    if(root2->num_of_agency>root1->num_of_agency){
        root1->father=root2;
        sales_temp=mergeTrees();
    }
    else{
        root2->father=root1;
    }
}

StatusType GetIthSoldType(void *DS, int agencyID, int i, int* res);

void Quit(void** DS);
//End of Main Functions//
