#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "symtable.h"
#define HASH_MULTIPLIER 65599



/* @author Sundorius */



/*
		KATHE HASH VALUE EPREPE NA GINEI: HashValue=SymTable_hash(pcKey) % oSymTable->BucketsCnt;
*/

/* This struct represents the nodes of the symTable. */
struct SymTableNode
{
    const char *pcKey;
    const void *pvValue;
    struct SymTableNode *next;
};


/* This struct represents the symTable. */
struct SymTable
{
    int NodesCnt;
    int BucketsArrayIndex;
    int BucketsCnt;
    struct SymTableNode **FirstBucket;
};

/* ============================================================= */

/* It contains all the appropriate bucket sizes, it is const because
    the contents must not change! */
const int BucketsArray[]={509, 1021, 2053, 4093, 8191, 16381, 32771, 65521};
/* Returns a hash code for the given pcKey. */
static unsigned int SymTable_hash(const char *pcKey)
{
  size_t ui;
  unsigned int uiHash = 0U;
  for (ui = 0U; pcKey[ui] != '\0'; ui++)
    uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
  return uiHash;
}


/* Creates a new SymTable, it checks if the symTable
    created is NULL and if the Buckets created
    are NULL. */
SymTable_T SymTable_new(void)
{
    SymTable_T oSymTable=(SymTable_T)malloc(sizeof(SymTable_T));
    struct SymTableNode **SymBuckets;
    int i=0;
    assert(oSymTable!=NULL);

    oSymTable->NodesCnt=0;
    oSymTable->BucketsArrayIndex=0;
    oSymTable->BucketsCnt=BucketsArray[oSymTable->BucketsArrayIndex];

    SymBuckets=(struct SymTableNode **)malloc(oSymTable->BucketsCnt*sizeof(struct SymTableNode*));

    assert(SymBuckets!=NULL);

    oSymTable->FirstBucket=SymBuckets;
    return oSymTable;
}


/* Frees the memory of an unwanted SymTable_T node, it checks if
    the symTable given is NULL. */
void SymTable_free(SymTable_T oSymTable)
{
    struct SymTableNode *currNode=NULL;
    struct SymTableNode *nextNode=NULL;
    int i=0;
    assert(oSymTable!=NULL);

    while(i<oSymTable->BucketsCnt)
    {
        currNode=oSymTable->FirstBucket[i];
        while(currNode!=NULL)
        {
            nextNode=currNode->next;
            free(currNode->pcKey);
            free(currNode->pvValue);
            free(currNode);
            currNode=nextNode;
        }
        i++;
    }
    free(oSymTable->FirstBucket);
    free(oSymTable);
    return;
}


/* Returns the number of the bindings, it checks if the symTable given
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
    struct SymTableNode *currNode;
    struct SymTableNode *newNode;
    int HashValue;
    assert(oSymTable!=NULL);
    assert(pcKey!=NULL);

    HashValue=SymTable_hash(pcKey);
	if(HashValue<0 || HashValue>oSymTable->BucketsCnt )
    {
        printf("SymTable_put -> Hash_Value=%d\n\n",HashValue);
        return 0;
    }
    currNode=oSymTable->FirstBucket[HashValue];

    if(SymTable_contains(oSymTable,pcKey)) return 0;

    if(oSymTable->BucketsCnt < oSymTable->NodesCnt) return 0;
    newNode=(struct SymTableNode*)malloc(sizeof(struct SymTableNode));
    assert(newNode!=NULL);
    newNode->pcKey=(char*)malloc(sizeof(strlen(pcKey)+1));
    assert(newNode->pcKey!=NULL);
    strcpy(newNode->pcKey,pcKey);
    newNode->pvValue=pvValue;
    newNode->next=oSymTable->FirstBucket[HashValue];
    oSymTable->FirstBucket[HashValue]=newNode;
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
    struct SymTableNode *prevNode=NULL;
    struct SymTableNode *nextNode;
    int HashValue;
    assert(oSymTable!=NULL);
    assert(pcKey!=NULL);

    HashValue=SymTable_hash(pcKey);
    if(HashValue<0 || HashValue>oSymTable->BucketsCnt )
    {
        printf("SymTable_remove -> Hash_Value=%d\n\n",HashValue);
        return 0;
    }
    currNode=oSymTable->FirstBucket[HashValue];
    if(currNode==NULL) return 0;
    while(currNode!=NULL)
    {
        if(strcmp(currNode->pcKey,pcKey)==0)
        {
            free(currNode->pcKey);
            free(currNode->pvValue);
            nextNode=currNode->next;
            free(currNode);
            prevNode->next=nextNode;
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
    int HashValue;
    assert(oSymTable!=NULL);
    assert(pcKey!=NULL);

    HashValue=SymTable_hash(pcKey);
    if(HashValue<0 || HashValue>oSymTable->BucketsCnt )
    {
        printf("SymTable_contains -> Hash_Value=%d\n\n",HashValue);
        return 0;
    }
    currNode=oSymTable->FirstBucket[HashValue];
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
    int HashValue;
    assert(oSymTable!=NULL);
    assert(pcKey!=NULL);

    HashValue=SymTable_hash(pcKey);
    if(HashValue<0 || HashValue>oSymTable->BucketsCnt )
    {
        printf("SymTable_get -> Hash_Value=%d\n\n",HashValue);
        return NULL;
    }
    currNode=oSymTable->FirstBucket[HashValue];
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
    int i=0;
    assert(oSymTable!=NULL);
    assert(pvExtra!=NULL);

    while(i<oSymTable->BucketsCnt)
    {
        currNode=oSymTable->FirstBucket[i];
        while(currNode!=NULL)
        {
            (*pfApply)(currNode->pcKey, currNode->pvValue, pvExtra);
            currNode=currNode->next;
        }
        i++;
    }
    return;
}
