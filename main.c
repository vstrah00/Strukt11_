#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declarations.h"

int main(){
    FILE *fp = NULL;
    char countryName[MAX_COUNTRY]={0};
    int min_population = 0;
    int check = 0;
    char townName[MAX_TOWN]={0};
    char countryFile[MAX_FILE_NAME]={0};
    char line[MAX_LINE]={0};
    list_A headOfList = {.nameCountry_list = {0}, .next = NULL};
    positionList_A head = &headOfList;
    positionList_A current = NULL;
    positionTree_A root = NULL;


    fp=fopen("drzave.txt", "r");
    
    if(!fp){
        printf("File open error!\n");
        return -1;
    }

    fseek(fp, 0, SEEK_SET);
    
    while(!feof(fp)){
        fgets(line, MAX_LINE, fp);
        current=scanCountryLine(line, head, countryFile); //saves country in a linked list, returns pointer to positionList_A, stores name of a file with towns in countryFile
        if(current==NULL){
            freeAll(head);
            return -2;
        }
        current->treeRoot=handleFileOfCertainCountry(countryFile);
        if(current->treeRoot==NULL){
            freeAll(head);
            return -3;
        }
    }
    fclose(fp);

    printAll(head);
    while(1){
        printf("\n---Press 0 to exit---\n");
        printf("Enter country name:\t");
        scanf(" %s", countryName);
        if(strcmp(countryName, "0")==0){
            freeAll(head);
            return 0;
        }

        printf("---Press 0 to exit---\n");
        printf("Input min. number of people:\t");
        scanf(" %d", &min_population);
        if(min_population==0){
            freeAll(head);
            return 0;
        }

        check=printAllTownsOver(min_population, countryName, head);
        if(check<0){
            printf("\nTry again...\n");
        }
    }


    return 0;
}