#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define MAX_TOWN 190 
#define MAX_COUNTRY 70
#define MAX_LINE 1024
#define MAX_FILE_NAME 50

struct search_tree;
typedef struct search_tree* positionTree_A;
typedef struct search_tree{
    char nameTown_tree[MAX_TOWN];
    int num;
    positionTree_A left;
    positionTree_A right;
}tree_A;

positionTree_A CreateNewTreeElement();
positionTree_A insertIntoTree(positionTree_A current, positionTree_A newEl);

struct linkedList;
typedef struct linkedList* positionList_A;
typedef struct linkedList{
    char nameCountry_list[MAX_COUNTRY];
    positionTree_A treeRoot;
    positionList_A next;
}list_A;

int insertAfter(positionList_A current, positionList_A newElement);
positionList_A CreateListElement(char* country);

positionList_A scanCountryLine(char* line, positionList_A head, char* fileName);
positionTree_A handleFileOfCertainCountry(char* countryFile);
positionList_A SortOnInsert_List(positionList_A newEl, positionList_A head);

int printAll(positionList_A head);
int PrintTree(positionTree_A root);
int printAllTownsOver(int min_population, char* countryName, positionList_A head);
int PrintOnlyTownsOver(int min_population, positionTree_A root);

int freeAll(positionList_A head);
positionTree_A FreeTree(positionTree_A root);

#endif