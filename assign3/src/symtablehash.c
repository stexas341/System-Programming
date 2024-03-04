#include "SymTable.h"
#define HASH_MULTIPLIER 65599
#define SIZE 509


struct bindings {
  	char *key;
  	void *value;
	struct bindings * next;
	};

struct SymTable{
  	 unsigned int total;
	 struct bindings * hash_table[SIZE];
	};



static unsigned int SymTable_hash(const char *pcKey){
	size_t ui;
	unsigned int uiHash = 0U;
	for (ui = 0U; pcKey[ui] != '\0'; ui++)
		uiHash = uiHash * HASH_MULTIPLIER + pcKey[ui];
	return uiHash;
}

SymTable_T SymTable_new(void) {
  SymTable_T table = (SymTable_T) malloc(sizeof(struct SymTable));
  if (table == NULL) {
    return NULL; 
  }
  table->total = 0;
  for (int i = 0; i < SIZE; i++) {
    table->hash_table[i] = NULL;
  }
  
  return table;
}


void SymTable_free(SymTable_T oSymTable)
{
    if (oSymTable == NULL)
        return;

    for (unsigned int i = 0; i < SIZE; i++) {
        struct bindings *current = oSymTable->hash_table[i];
        while (current != NULL) {
            struct bindings *temp = current;
            current = current->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }

    free(oSymTable);
}
unsigned int SymTable_getLength(SymTable_T oSymTable)
{
    if (oSymTable == NULL)
        return 0;

    unsigned int length = 0;
    for (unsigned int i = 0; i < SIZE; i++) {
        struct bindings *current = oSymTable->hash_table[i];
        while (current != NULL) {
            length++;
            current = current->next;
        }
    }

    return length;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue)
{
    if (oSymTable == NULL || pcKey == NULL) {
        return 0;
    }

    unsigned int index = SymTable_hash(pcKey) % SIZE;
    struct bindings *current = oSymTable->hash_table[index];

    while (current != NULL) {
        if (strcmp(current->key, pcKey) == 0) {
            return 0;
        }
        current = current->next;
    }

    struct bindings *new_binding = malloc(sizeof(struct bindings));
    if (new_binding == NULL) {
        return 0;
    }
    new_binding->key = strdup(pcKey);
    new_binding->value = (void *)pvValue;
    new_binding->next = oSymTable->hash_table[index];
    oSymTable->hash_table[index] = new_binding;
    oSymTable->total++;

    return 1;
}

int SymTable_remove(SymTable_T oSymTable, const char *pcKey)
{
    if (oSymTable == NULL || pcKey == NULL) {
        return 0; // NULL arguments, return FALSE
    }

    unsigned int index = SymTable_hash(pcKey) % SIZE;
    struct bindings *prev = NULL;
    struct bindings *current = oSymTable->hash_table[index];

    while (current != NULL) {
        if (strcmp(current->key, pcKey) == 0) {
            if (prev == NULL) {
                oSymTable->hash_table[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->key);
            free(current);
            oSymTable->total--;
            return 1; // binding removed, return TRUE
        }
        prev = current;
        current = current->next;
    }

    return 0; // binding not found, return FALSE
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey){
    if(oSymTable == NULL || pcKey == NULL)
        return 0;
    unsigned int hashIndex = SymTable_hash(pcKey) % SIZE;
    struct bindings* ptr = oSymTable->hash_table[hashIndex];
    while(ptr != NULL){
        if(strcmp(ptr->key, pcKey) == 0)
            return 1;
        ptr = ptr->next;
    }
    return 0;
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey){

    if(oSymTable == NULL || pcKey == NULL){
        return NULL;
    }

    unsigned int uiHash = SymTable_hash(pcKey) % SIZE;

    struct bindings * current = oSymTable->hash_table[uiHash];
    while(current != NULL){
        if(strcmp(current->key, pcKey) == 0){
            return current->value;
        }
        current = current->next;
    }

    return NULL;
}

 void SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra), const void *pvExtra){
	if (oSymTable == NULL || pfApply == NULL)
		exit;

	for (int i = 0; i < SIZE; i++) {
		struct bindings *binding = oSymTable->hash_table[i];
		while (binding != NULL) {
			pfApply(binding->key, binding->value, pvExtra);
			binding = binding->next;
		}
	}
} 





/* void test_put_get() {
    SymTable_T table = SymTable_new();

    char* key1 = "key1";
    int value1 = 1;

    char* key2 = "key2";
    char* value2 = "value2";

    SymTable_put(table, key1, &value1);
    SymTable_put(table, key2, value2);

    int* retrieved_value1 = SymTable_get(table, key1);
    char* retrieved_value2 = SymTable_get(table, key2);

    if (*retrieved_value1 != value1 || strcmp(retrieved_value2, value2) != 0) {
        printf("Failed test_put_get.\n");
    }

    SymTable_free(table);
}

void test_put_duplicate() {
    SymTable_T table = SymTable_new();

    char* key = "key";
    int value1 = 1;
    int value2 = 2;

    SymTable_put(table, key, &value1);
    int result = SymTable_put(table, key, &value2);

    if (result != 0 || *(int*)SymTable_get(table, key) != value1) {
        printf("Failed test_put_duplicate.\n");
    }

    SymTable_free(table);
}

void test_remove() {
    SymTable_T table = SymTable_new();

    char* key1 = "key1";
    int value1 = 1;

    char* key2 = "key2";
    char* value2 = "value2";

    SymTable_put(table, key1, &value1);
    SymTable_put(table, key2, value2);

    SymTable_remove(table, key1);

    if (SymTable_get(table, key1) != NULL || SymTable_get(table, key2) != value2 || SymTable_getLength(table) != 1) {
        printf("Failed test_remove.\n");
    }

    SymTable_free(table);
}

 void test_map() {
    SymTable_T table = SymTable_new();

    char* key1 = "key1";
    int value1 = 1;

    char* key2 = "key2";
    char* value2 = "value2";

    SymTable_put(table, key1, &value1);
    SymTable_put(table, key2, value2);

    int sum = 0;
    void add_values(const char* key, void* value, void* extra) {
        sum += *(int*)value;
    }

    SymTable_map(table, add_values, NULL);

    if (sum != value1 || strcmp(value2, "value2") != 0) {
        printf("Failed test_map.\n");
    }

    SymTable_free(table);
} 

int main() {
    test_put_get();
    test_put_duplicate();
    test_remove();
    //test_map();

    return 0;
}*/

void print_key_value(const char *key, void *value, void *extra) {
    printf("%s: %d\n", key, *((int*)value));
}

int main(void) {
    SymTable_T table = SymTable_new();

    // Test SymTable_put and SymTable_get
    int value1 = 42;
    int value2 = 7;
    int value3 = 99;
    SymTable_put(table, "key1", &value1);
    SymTable_put(table, "key2", &value2);
    SymTable_put(table, "key3", &value3);
    int *pValue1 = (int*) SymTable_get(table, "key1");
    int *pValue2 = (int*) SymTable_get(table, "key2");
    int *pValue3 = (int*) SymTable_get(table, "key3");
    if (pValue1 == NULL || *pValue1 != value1) {
        printf("Test failed: SymTable_put or SymTable_get.\n");
        exit(EXIT_FAILURE);
    }
    if (pValue2 == NULL || *pValue2 != value2) {
        printf("Test failed: SymTable_put or SymTable_get.\n");
        exit(EXIT_FAILURE);
    }
    if (pValue3 == NULL || *pValue3 != value3) {
        printf("Test failed: SymTable_put or SymTable_get.\n");
        exit(EXIT_FAILURE);
    }

    // Test SymTable_contains
    if (!SymTable_contains(table, "key1") || !SymTable_contains(table, "key2") || !SymTable_contains(table, "key3")) {
        printf("Test failed: SymTable_contains.\n");
        exit(EXIT_FAILURE);
    }

    // Test SymTable_remove
    SymTable_remove(table, "key2");
    if (SymTable_contains(table, "key2")) {
        printf("Test failed: SymTable_remove.\n");
        exit(EXIT_FAILURE);
    }

    // Test SymTable_map
    SymTable_map(table, &print_key_value, NULL);

    // Test SymTable_getLength
    if (SymTable_getLength(table) != 2) {
        printf("Test failed: SymTable_getLength.\n");
        exit(EXIT_FAILURE);
    }

    SymTable_free(table);
    printf("All tests passed!\n");
    return 0;
}




