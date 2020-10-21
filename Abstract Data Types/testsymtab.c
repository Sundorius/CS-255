#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.h"
#define BUZZ_SIZE 1024


/* @author Sundorius */




void *IncrementFive(const char *pcKey, void *pvValue, void *pvExtra)
{
    return (pvValue=pvValue+1);
}


int main()
{
    FILE *input;
    char buffer[BUZZ_SIZE];
    char *pvValue="value";
    int result=0; /* this is a flag for tests */
    char option[20]="";
    SymTable_T oSymTable=SymTable_new();
    printf("\nThis test file checks the Symtable_put, Symtable_remove, Symtable_get, Symtable_map,\n");
    printf("Symtable_getLength functions, Symtable_contains function is used in function Symtable_put,\n");
    printf("so it does not need extra testing.\n\n");
    printf("If some function does not correspond to the standards, a message will be shown.\n\n");
    printf("Please choose the level of testing\n1) tiny1 <509\n2) tiny2 <1021\n3) small1 <2053\n4) small2 <4093\n5) medium1 <8191\n");
    printf("6) medium2 <16381\n7) large1 <32771\n8) large2 <65521\n");
    printf("Option: ");
    scanf("%d",&result);
    switch(result)
    {
    case 1: strcpy(option,"tiny1"); break;
    case 2: strcpy(option,"tiny2"); break;
    case 3: strcpy(option,"small1"); break;
    case 4: strcpy(option,"small2"); break;
    case 5: strcpy(option,"medium1"); break;
    case 6: strcpy(option,"medium2"); break;
    case 7: strcpy(option,"large1"); break;
    case 8: strcpy(option,"large2"); break;
    default:
        printf("Something went wrong in the choosing of level!\n"); exit(1);
    }
    input=fopen(option,"r");
    if(input==NULL)
    {
        printf("Error opening file: %s \n",option);
        exit(1);
    }
/*==============    TESTING PUT    ==============*/
    printf("===================  Symtable_put  ===================\n");
    while (fscanf(input, "%s", buffer) != EOF)
    {
        result=SymTable_put(oSymTable, buffer, &pvValue);
    }
    printf("\nSymTable length=%d\n\n",SymTable_getLength(oSymTable));
/*==============    TESTING MAP    ==============*/
    printf("===================  Symtable_map  ===================\n");
    while (fscanf(input, "%s", buffer) != EOF)
    {
        SymTable_map(oSymTable,
                     IncrementFive(buffer,&pvValue, &pvValue),&pvValue);
    }
    printf("\nSymTable length=%d\n\n",SymTable_getLength(oSymTable));
/*==============    TESTING GET    ==============*/
    printf("===================  Symtable_get  ===================\n");
    result=0;
    while (fscanf(input, "%s", buffer) != EOF)
    {
        if(SymTable_get(oSymTable, buffer)==NULL)
        {
            printf("pcKey=%s not found!\n",buffer);
            result=1;
        }
    }
    if(!result) printf("\noSymTable_get ended successfully!\n\n");
    printf("SymTable length=%d\n\n",SymTable_getLength(oSymTable));
    fclose(input);
/*==============    TESTING REMOVE    ==============*/
    printf("===================  Symtable_remove  ===================\n");
    printf("Please choose how many bindings to remove\n1) <509\n2) <1021\n3) <2053\n4) <4093\n5) <8191\n");
    printf("6) <16381\n7) <32771\n8) <65521\n");
    printf("Option: ");
    scanf("%d",&result);
    switch(result)
    {
    case 1: strcpy(option,"tiny1"); break;
    case 2: strcpy(option,"tiny2"); break;
    case 3: strcpy(option,"small1"); break;
    case 4: strcpy(option,"small2"); break;
    case 5: strcpy(option,"medium1"); break;
    case 6: strcpy(option,"medium2"); break;
    case 7: strcpy(option,"large1"); break;
    case 8: strcpy(option,"large2"); break;
    default:
        printf("Something went wrong in the choosing of level!\n"); exit(1);
    }
    input=fopen(option,"r");
    if(input==NULL)
    {
        printf("Error opening file: %s \n",option);
        exit(1);
    }
    while (fscanf(input, "%s", buffer) != EOF)
    {
        result=SymTable_remove(oSymTable, buffer);
    }
    printf("\nSymTable length=%d\n\n",SymTable_getLength(oSymTable));
/*==============    TESTING FREE    ==============*/
    SymTable_free(oSymTable);
    printf("===================  End of Test File  ===================");
    fclose(input);
    return 0;
}
