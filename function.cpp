#include "library2.h"
#include "dealership.h"

////////////////////////Insert Static Functions Here//////////////////////////////////
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
static void mergeArry(CarType** temp1,int size1,CarType** temp2,int size2,CarType** temp3){
    int i1=0,i2=0,i3=0;
    while(i1<size1&&i2<size2){
        if(*(temp2[i2])>*(temp1[i1])){
            temp3[i3]=temp1[i1];
            i3++;
            i1++;
        }
        else{
            temp3[i3]=temp2[i2];
            i3++;
            i2++;
        }
    }
    while(i1<size1){
        temp3[i3]=temp1[i1];
        i3++;
        i1++;
    }
    while(i2<size2){
        temp3[i3]=temp2[i2];
        i3++;
        i2++;
    }
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
static void writeSalesTree(SalesNode* tree1, CarType** temp1,int* index){
    if(tree1==NULL){
        return;
    }
    writeSalesTree(tree1->left,temp1,index);
    temp1[*index]=tree1->key;
    (*index)++;
    writeSalesTree(tree1->right,temp1,index);
}

static void writeTypeTree(TypeNode* tree1, CarType** temp1,int* index){
    if(tree1==NULL){
        return;
    }
    writeTypeTree(tree1->left,temp1,index);
    temp1[*index]=tree1->key;
    (*index)++;
    writeTypeTree(tree1->right,temp1,index);
}

static SalesNode* mergeSalesTrees(SalesNode* tree1,int size1,SalesNode* tree2,int size2){
    CarType** temp1 = new CarType*[size1];
    CarType** temp2 = new CarType*[size2];
    CarType** temp3 = new CarType*[size1+size2];
    int index=0;
    writeSalesTree(tree1,temp1,&index);
    index=0;
    writeSalesTree(tree1,temp1,&index);
    mergeArrey(temp1,size1,temp2,size2,temp3);
}

static SalesNode* mergeTypeTrees(TypeNode* tree1,int size1,TypeNode* tree2,int size2){
    CarType** temp1 = new CarType*[size1];
    CarType** temp2 = new CarType*[size2];
    CarType** temp3 = new CarType*[size1+size2];
    int index=0;
    writeTypeTree(tree1,temp1,&index);
    index=0;
    writeTypeTree(tree1,temp1,&index);
    mergeArrey(temp1,size1,temp2,size2,temp3);
}
////////////////////////End of Static Functions//////////////////////////////////////

////////////////////////Insert Main Functions Here//////////////////////////////////
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
        root1->sales_key
        SalesNode* sales_temp=mergeSalesTrees(root1,root1->);
    }
    else{
        root2->father=root1;
    }
}

StatusType GetIthSoldType(void *DS, int agencyID, int i, int* res);

void Quit(void** DS);
//End of Main Functions//
