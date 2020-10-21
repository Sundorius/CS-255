#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "symtable.h"


/* @author Sundorius */


/* This struct represents the nodes of the symTable. */
struct SymTableNode
{
    char *pcKey;
    void *pvValue;
    struct SymTableNode *next;
};

/* This struct represents a symTable. */
struct SymTable
{
    int NodesCnt;
    struct SymTableNode *FirstNode;
};

/* ============================================================= */

/* Creates a new SymTable, it checks if the symTable
    created is NULL. */
SymTable_T SymTable_new(void)
{
    SymTable_T oSymTable=(SymTable_T)malloc(sizeof(SymTable_T));
    assert(oSymTable!=NULL);

    oSymTable->FirstNode=NULL;
    oSymTable->NodesCnt=0;
    return (SymTable_T)oSymTable;
}


/* Frees the memory of an unwanted SymTable_T node, it checks if
    the symTable given is NULL. */
void SymTable_free(SymTable_T oSymTable)
{   
    struct SymTableNode *currNode;
    struct SymTableNode *nextNode=NULL;
    assert(oSymTable!=NULL);

    currNode=oSymTable->FirstNode;
    while(currNode!=NULL)
    {
        nextNode=currNode->next;
        free(currNode->pcKey);
        /*free(currNode->pvValue);*/
        free(currNode);
        currNode=nextNode;
    }
    free(oSymTable);
    return;
}


/* Returns the length of the bindings, it checks if the symTable given
    is NULL. */
unsigned int SymTable_getLength(SymTable_T oSymTable)
{
    assert(oSymTable!=NULL);
    return oSymTable->NodesCnt;
}


/* It checks if the oSymTable contains a binding with the key: pcKey
    if yes then it returns 0, else it adds a new binding with key:
    pcKey and value: pvValue and returns 1. It also checks if oSymTable
    is NULL and if pcKey is NULL. */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
    struct SymTableNode *newNode;
    assert(oSymTable!=NULL);
    assert(pcKey!=NULL);

    if(SymTable_contains(oSymTable,pcKey)) return 0;

    newNode=(struct SymTableNode*)malloc(sizeof(struct SymTableNode));
    assert(newNode!=NULL);
    newNode->pcKey=(char*)malloc(sizeof(strlen(pcKey)+1));
    assert(newNode->pcKey!=NULL);

    strcpy(newNode->pcKey,pcKey);
    newNode->pvValue=pvValue;
    newNode->next=oSymTable->FirstNode;
    oSymTable->FirstNode=newNode;
    oSymTable->NodesCnt++;
    return 1;
}


/* It checks if the oSymTable contains a binding with the key: pcKey
    if yes then it removes it and returns 1, else it leaves the symTable
    as it is and returns 0. It also checks if oSymTable
    is NULL and if pcKey is NULL. */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
    struct SymTableNode *currNode;
    struct SymTableNode *nextNode;
    struct SymTableNode *prevNode=NULL;
    assert(oSymTable!=NULL);
    assert(pcKey!=NULL);

    currNode=oSymTable->FirstNode;
    while(currNode!=NULL)
    {
        if(strcmp(currNode->pcKey,pcKey)==0)
        {
            free(currNode->pcKey);
            nextNode=currNode->next;
            free(currNode);
            if(prevNode!=NULL) prevNode->next=nextNode;
	    else oSymTable->FirstNode=oSymTable->FirstNode->next;
            oSymTable->NodesCnt--;
            return 1;
        }
        prevNode=currNode;
        currNode=currNode->next;
    }
    return 0;
}

/* It returns 1 if the oSymTable has a binding with the
    key: pcKey, else it returns 0. It also checks if oSymTable
    is NULL and if pcKey is NULL.*/
int SymTable_contains(SymTable_T oSymTable, const char *pcKey)
{
    struct SymTableNode *currNode;
    assert(oSymTable!=NULL);
    assert(pcKey!=NULL);

    currNode=oSymTable->FirstNode;
    while(currNode!=NULL)
    {
        if(strcmp(currNode->pcKey,pcKey)==0) return 1;
        currNode=currNode->next;
    }
    return 0;
}


/* It returns the value of the binding with key: pcKey if it
    exists, else it returns NULL. It also checks if oSymTable
    is NULL and if pcKey is NULL.*/
void* SymTable_get(SymTable_T oSymTable, const char *pcKey)
{
    struct SymTableNode *currNode;
    assert(oSymTable!=NULL);
    assert(pcKey!=NULL);

    currNode=oSymTable->FirstNode;
    while(currNode!=NULL)
    {
        if(strcmp(currNode->pcKey,pcKey)==0) return currNode->pvValue;
        currNode=currNode->next;
    }
    return NULL;
}


/* It applies the function *pfApply, in every binding of the
    oSymTable. It also checks if oSymTable is NULL and if
    pvExtra is NULL.*/
void SymTable_map(SymTable_T oSymTable,
                  void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
                  const void *pvExtra)
{
    struct SymTableNode *currNode;
    assert(oSymTable!=NULL);
    assert(pvExtra!=NULL);

    currNode=oSymTable->FirstNode;
    while(currNode!=NULL)
    {
        (*pfApply)(currNode->pcKey, currNode->pvValue, pvExtra);
        currNode=currNode->next;
    }
    return;
}
