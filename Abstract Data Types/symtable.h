

/* @author Sundorius */


/* Type definition for the symTable. */
typedef struct SymTable *SymTable_T;


/* Creates a new SymTable, it checks if the symTable
    created is NULL. */
SymTable_T SymTable_new(void);

/* Frees the memory of an unwanted SymTable_T node, it checks if
    the symTable given is NULL. */
void SymTable_free(SymTable_T oSymTable);


/* Returns the length of the bindings, it checks if the symTable given
    is NULL. */
unsigned int SymTable_getLength(SymTable_T oSymTable);


/* It checks if the oSymTable contains a binding with the key: pcKey
    if yes then it returns 0, else it adds a new binding with key:
    pcKey and value: pvValue and returns 1. It also checks if oSymTable
    is NULL and if pcKey is NULL. */
int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue);


/* It checks if the oSymTable contains a binding with the key: pcKey
    if yes then it removes it and returns 1, else it leaves the symTable
    as it is and returns 0. It also checks if oSymTable
    is NULL and if pcKey is NULL. */
int SymTable_remove(SymTable_T oSymTable, const char *pcKey);


/* It returns 1 if the oSymTable has a binding with the
    key: pcKey, else it returns 0. It also checks if oSymTable
    is NULL and if pcKey is NULL.*/
int SymTable_contains(SymTable_T oSymTable, const char *pcKey);


/* It returns the value of the binding with key: pcKey if it
    exists, else it returns NULL. It also checks if oSymTable
    is NULL and if pcKey is NULL.*/
void* SymTable_get(SymTable_T oSymTable, const char *pcKey);


/* It applies the function *pfApply, in every binding of the
    oSymTable. It also checks if oSymTable is NULL and if
    pvExtra is NULL.*/
void SymTable_map(SymTable_T oSymTable,
                          void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),
                          const void *pvExtra);
