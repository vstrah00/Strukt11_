#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#define MAX_TOWN 190 
#define MAX_COUNTRY 70
#define MAX_LINE 1024
#define MAX_FILE_NAME 50
#define TABLE_SIZE 11
#define HASH_CONST 5

struct search_tree;
typedef struct search_tree* positionTree_A;
typedef struct search_tree{
    char nameTown_tree[MAX_TOWN];
    int num;
    positionTree_A left;
    positionTree_A right;
}tree_A;

struct linkedList;
typedef struct linkedList* positionList_A;
typedef struct linkedList{
    char nameCountry_list[MAX_COUNTRY];
    positionTree_A treeRoot;
    positionList_A next;
}list_A;

positionList_A hash_table[TABLE_SIZE];


positionList_A hash_insert(positionList_A newEl);
int hash(char *countryName);
int initTable();
int printAllTownsOver_hash(int min_population, char* countryName);
int freeAll_B();
int printAll_B();


positionList_A scanCountryLine(char* line, char* fileName);
positionTree_A handleFileOfCertainCountry(char* countryFile);
positionList_A SortOnInsert_List(positionList_A newEl, positionList_A head);
positionList_A CreateListElement(char* country);
int insertAfter(positionList_A current, positionList_A newElement);
int PrintTree(positionTree_A root);
int PrintOnlyTownsOverFromTree(int min_population, positionTree_A root);
int freeAll_from(positionList_A first);
positionTree_A FreeTree(positionTree_A root);
positionTree_A CreateNewTreeElement();
positionTree_A insertIntoTree(positionTree_A current, positionTree_A newEl);


#endif