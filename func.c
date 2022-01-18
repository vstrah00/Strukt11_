#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"

int insertAfter(positionList_A current, positionList_A newElement){
    newElement->next=current->next;
    current->next=newElement;

    return 0;
}


positionList_A scanCountryLine(char* line, positionList_A head, char* fileName){
    int check = 0;
    char country[MAX_COUNTRY] = {0};
    positionList_A newEl = NULL;


    check=sscanf(line, "%s %s", country, fileName);
    if(check!=2){
        printf("FILE FORMAT ERROR!\n");
        return NULL;
    }
    
    newEl=CreateListElement(country);
    if(newEl==NULL){
        return NULL;
    }
    
    newEl=SortOnInsert_List(newEl, head);

    return newEl;
}


positionList_A CreateListElement(char* country){
    positionList_A newElement = NULL;

    newElement = (positionList_A)malloc(sizeof(list_A));
    if(newElement==NULL){
        return NULL;
    }

    strcpy(newElement->nameCountry_list, country);
    newElement->next = NULL;

    return newElement;
}

positionList_A SortOnInsert_List(positionList_A newEl, positionList_A head){
    positionList_A temp = head->next;

    if(head->next==NULL){
        insertAfter(head, newEl);
        return head->next;
    }

    if(strcmp(newEl->nameCountry_list, head->next->nameCountry_list)<0){
        insertAfter(head, newEl);
        return head->next;
    }

    while(temp){
        if(temp->next==NULL && strcmp(newEl->nameCountry_list, temp->nameCountry_list)>0){
            insertAfter(temp, newEl);
            return temp->next;
        }
        else if(strcmp(newEl->nameCountry_list, temp->nameCountry_list)>0 && strcmp(newEl->nameCountry_list, temp->next->nameCountry_list)<0){
            insertAfter(temp, newEl);
            return temp->next;
        }
        temp = temp->next;
    }
}

positionTree_A handleFileOfCertainCountry(char* countryFile){
    FILE *fpCountry = NULL;
    char line[MAX_LINE] = {0};
    positionTree_A newEl = NULL;
    positionTree_A root = NULL;
    int check = 0;
    char town[MAX_TOWN] = {0};
    int population = 0;

    fpCountry = fopen(countryFile, "r");
    if(fpCountry==NULL){
        printf("COUNTRY FILE OPEN ERROR!\n");
        return NULL;
    }

    fseek(fpCountry, 0, SEEK_SET);

    while(!feof(fpCountry)){
        fgets(line, MAX_LINE, fpCountry);
        check=sscanf(line, "%[a-zA-Z ], %d", town, &population);
        if(check!=2){
            printf("FILE FORMAT ERROR!\n");
            return NULL;
        }
        newEl = CreateNewTreeElement();
        strcpy(newEl->nameTown_tree, town);
        newEl->num = population;

        root=insertIntoTree(root, newEl);
    }

    fclose(fpCountry);
    return root;
}

positionTree_A CreateNewTreeElement(){
    positionTree_A newElement = NULL;
    char temp[MAX_TOWN] = {0};

    newElement = (positionTree_A)malloc(sizeof(tree_A));
    if(newElement==NULL){
        return NULL;
    }

    strcpy(newElement->nameTown_tree, temp);
    newElement->num = 0;
    newElement->left = NULL;
    newElement->right = NULL;

    return newElement;
}

positionTree_A insertIntoTree(positionTree_A current, positionTree_A newEl){
    if(current==NULL){
        current = newEl;
    }
    else if(current->num < newEl->num){
        current->right=insertIntoTree(current->right, newEl);
    }
    else if(current->num > newEl->num){
        current->left=insertIntoTree(current->left, newEl);
    }
    else if(current->num==newEl->num){
        if(strcmp(current->nameTown_tree, newEl->nameTown_tree)>0){
            current->left=insertIntoTree(current->left, newEl);
        }
        else if(strcmp(current->nameTown_tree, newEl->nameTown_tree)<0){
            current->right=insertIntoTree(current->right, newEl);
        }
        else{
            printf("TOWN DUPLICATE! Duplicate not stored!\n");
            free(newEl);
        }
    }
    return current;
}

int printAll(positionList_A head){
    positionList_A temp = head->next;
    positionTree_A tempTree = NULL;

    while(temp){
        printf("\n%s:\n", temp->nameCountry_list);
        PrintTree(temp->treeRoot);
        temp = temp->next;
    }
    return 0;
}

int PrintTree(positionTree_A root){
    if(root!=NULL){
        if(root->right!=NULL){
            PrintTree(root->right);
        }
        printf("-%s\n", root->nameTown_tree);

        if(root->left!=NULL){
            PrintTree(root->left);
        }
    }
    else{
        printf("\nNo towns stored!\n");
    }
    return 0;
}

int printAllTownsOver(int min_population, char* countryName, positionList_A head){
    positionList_A temp = head->next;
    int check = 0;

    if(temp!=NULL){
        while(strcmp(temp->nameCountry_list, countryName)!=0){
            temp = temp->next;
            if(temp==NULL){
                printf("\nNo such country stored!\n");
                return -1;
            }
        }
    }
    else{
        printf("\nNo countries stored!\n");
        return -2;
    }
    
    printf("\nAll towns in %s with population over %d:\n", countryName, min_population);
    check=PrintOnlyTownsOver(min_population, temp->treeRoot);
    if(check==0){
        printf("No such towns in %s.\n", countryName);
    }

    return 0;
}

int PrintOnlyTownsOver(int min_population, positionTree_A root){
    int check = 0;

    if(root!=NULL){
        if(root->left!=NULL){
            check+=PrintOnlyTownsOver(min_population, root->left);
        }
        if(root->num>min_population){
            printf("-%s\n", root->nameTown_tree);
            ++check;
        }

        if(root->right!=NULL){
            check+=PrintOnlyTownsOver(min_population, root->right);
        }
    }
    else{
        printf("No towns stored\n");
    }

    return check;
}


int freeAll(positionList_A head){
    positionList_A temp = head->next;
    head = head->next;

    while(head){
        head->treeRoot=FreeTree(head->treeRoot);
        temp = head;
        head = head->next;
        free(temp);
    }
}

positionTree_A FreeTree(positionTree_A root){
    if(root!=NULL){
        if(root->left!=NULL){
            root->left = FreeTree(root->left);
        }
        if(root->right!=NULL){
            root->right = FreeTree(root->right);
        }
        free(root);
    }
    return root;
}