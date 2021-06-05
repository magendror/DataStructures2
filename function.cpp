#include "library2.h"
#include "dealership.h"

////////////////////////Insert Static Functions Here//////////////////////////////////
static Agency* getRoot(Agency* current){
    while(current->father!=NULL){
        current=current->father;
    }
    return current;
}

static void shrink(Agency* current){
    Agency* root =getRoot(current);
    Agency* temp=NULL;
    while(current->father!=NULL){
        temp =current->father;
        current->father=root;
        current=temp;
    }
}

static void clearTypeTree(TypeNode* current){
    if (current==NULL){
        return;
    }
    clearTypeTree(current->left);
    clearTypeTree(current->right);
    delete current;
}

// static void deleteTypeTree(TypeNode* current){
//     if (current==NULL){
//         return;
//     }
//     deleteTypeTree(current->left);
//     deleteTypeTree(current->right);
//     delete current->key;
//     delete current;
// }
///not sure if needed because salestree and typetree have the same key

static void clearSalesTree(SalesNode* current){
    if (current==NULL){
        return;
    }
    clearSalesTree(current->left);
    clearSalesTree(current->right);
    delete current;
}

static void deleteSalesTree(SalesNode* current){
    if (current==NULL){
        return;
    }
    deleteSalesTree(current->left);
    deleteSalesTree(current->right);
    delete current->key->sales_key;
    delete current->key;
    delete current;
}


static void mergeArrey(CarType** temp1,int size1,CarType** temp2,int size2,CarType** temp3){
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

static SalesNode* createMergedSalesTree(CarType** temp3, int start, int end){
    if (start > end)
    return NULL;
    int middle = (start + end)/2;
    SalesNode* node = new SalesNode(temp3[middle]);
    node->left=createMergedSalesTree(temp3,start,middle-1);
    node->right=createMergedSalesTree(temp3,middle+1,end);
    return node;
}

static TypeNode* createMergedTypeTree(CarType** temp3, int start, int end){
    if (start > end)
    return NULL;
    int middle = (start + end)/2;
    TypeNode* node = new TypeNode(temp3[middle]);
    node->left=createMergedTypeTree(temp3,start,middle-1);
    node->right=createMergedTypeTree(temp3,middle+1,end);
    return node;
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
    delete[] temp1;
    delete[] temp2;
    SalesNode* new_tree = createMergedSalesTree(temp3,0,size1+size2-1);
    delete[] temp3;
    return new_tree;
}

static TypeNode* mergeTypeTrees(TypeNode* tree1,int size1,TypeNode* tree2,int size2){
    CarType** temp1 = new CarType*[size1];
    CarType** temp2 = new CarType*[size2];
    CarType** temp3 = new CarType*[size1+size2];
    int index=0;
    writeTypeTree(tree1,temp1,&index);
    index=0;
    writeTypeTree(tree1,temp1,&index);
    mergeArrey(temp1,size1,temp2,size2,temp3);
    delete[] temp1;
    delete[] temp2;
    TypeNode* new_tree = createMergedTypeTree(temp3,0,size1+size2-1);
    delete[] temp3;
    return new_tree;
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

StatusType SellCar(void *DS, int agencyID, int typeID, int k){
    if(DS==NULL||k<=0||agencyID<0){
        return INVALID_INPUT;
    }
    Dealership* DS_convert = (Dealership*)DS;
    if(agencyID>=DS_convert->num_of_agencies){
        return FAILURE;
    }
    Agency* root=getRoot(DS_convert->agencies[agencyID]);
    TypeNode* car_node= findTypeNode(root->type_tree,typeID);
    if(car_node==NULL){
        CarType* car_new_node=new CarType(typeID,k);
        if(car_new_node==NULL){
            return ALLOCATION_ERROR;
        }
        root->type_tree= insertTypeNode(root->type_tree,car_new_node);
        root->sales_tree=insertSalesNode(root->sales_tree,car_new_node);
        //// salestree and typetree have the same key ////
    }
    else{
        int newSales=car_node->key->sales_key->sales+k;
        CarType* sales_new_key=new CarType(car_node->key->sales_key->type_id,newSales);
        if(sales_new_key==NULL){
            return ALLOCATION_ERROR;
        }
        root->sales_tree=deleteSalesNode(root->sales_tree,car_node->key->sales_key);
        root->sales_tree=insertSalesNode(root->sales_tree,sales_new_key);
    }
    shrink(DS_convert->agencies[agencyID]);
    return SUCCESS;
}

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
    SalesNode* sales_temp=mergeSalesTrees(root1->sales_tree,root1->num_of_cars,root2->sales_tree,root2->num_of_cars);
    TypeNode* type_temp=mergeTypeTrees(root1->type_tree,root1->num_of_cars,root2->type_tree,root2->num_of_cars);
    clearSalesTree(root1->sales_tree);
    clearSalesTree(root2->sales_tree);
    clearTypeTree(root1->type_tree);
    clearTypeTree(root2->type_tree);
    if(root2->num_of_agency>root1->num_of_agency){
        root1->father=root2;
        root2->sales_tree=sales_temp;
        root2->type_tree=type_temp;
        root2->num_of_agency+=root1->num_of_agency;
        root2->num_of_cars+=root1->num_of_cars;
    }
    else{
        root2->father=root1;
        root1->sales_tree=sales_temp;
        root1->type_tree=type_temp;
        root1->num_of_agency+=root2->num_of_agency;
        root1->num_of_cars+=root2->num_of_cars;
    }
    return SUCCESS;
}

StatusType GetIthSoldType(void *DS, int agencyID, int i, int* res){
    if(DS==NULL||i<0||agencyID<0||res==NULL){
        return INVALID_INPUT;
    }
    Dealership* DS_convert = (Dealership*)DS;
    Agency* root=getRoot(DS_convert->agencies[agencyID]);
    if(agencyID>=DS_convert->num_of_agencies||root->num_of_cars<i){
        return FAILURE;
    }
    *res=select(root->sales_tree,i)->key->type_id;
    return SUCCESS;
}

void Quit(void** DS){
    Dealership* DS_convert = (Dealership*)*DS;
    for(int i=0; i<DS_convert->num_of_agencies; i++){
        Agency* root= getRoot(DS_convert->agencies[i]);
        deleteSalesTree(root->sales_tree);
        clearTypeTree(root->type_tree);
        delete DS_convert->agencies[i];
    }
    delete[] DS_convert->agencies;
    delete DS_convert;

}
//End of Main Functions//
