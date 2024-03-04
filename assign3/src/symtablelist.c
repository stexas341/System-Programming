#include "SymTable.h"

struct SymTable {
    struct bindings *head;
};

struct bindings {
    void *value;
    char *key;
    struct bindings *next;
};

SymTable_T SymTable_new(void) {
    SymTable_T ptr = malloc(sizeof(struct SymTable));
    if (ptr == NULL) {
        return NULL;
    }
    ptr->head = NULL;
    return ptr;
}

void SymTable_free(SymTable_T oSymTable) {
    if (oSymTable == NULL) {
        return;
    }
    struct bindings *temp = oSymTable->head;
    while (temp != NULL) {
        struct bindings *prev = temp;
        temp = temp->next;
        free(prev->key);
        free(prev);
    }
    free(oSymTable);
}
unsigned int SymTable_getLength(SymTable_T oSymTable) {
    if (oSymTable == NULL) {
        return 0;
    }
    unsigned int count = 0;
    struct bindings *temp = oSymTable->head;
    assert(temp);
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

int SymTable_put(SymTable_T oSymTable, const char *pcKey, const void *pvValue) {
    assert(oSymTable!=NULL);
    assert(pcKey!=NULL);
    if (SymTable_contains(oSymTable, pcKey)) {
        return 0;
    }
    struct bindings *new_node = malloc(sizeof(struct bindings));
    if (new_node == NULL) {
        return 0;
    }
    size_t sz = strlen(pcKey) + 1;
    new_node->key = malloc(sz * sizeof(char));
    if (new_node->key == NULL) {
        free(new_node);
        return 0;
    }
    strcpy(new_node->key, pcKey);
    new_node->value = (void *)pvValue;
    new_node->next = oSymTable->head;
    oSymTable->head = new_node;
    return 1;
}

int SymTable_remove(SymTable_T oSymTable, const char *pcKey) {
    assert(oSymTable);
    assert(pcKey);
    struct bindings *prev = NULL;
    struct bindings *temp = oSymTable->head;
    while (temp != NULL) {
        if (strcmp(temp->key, pcKey) == 0) {
            if (prev == NULL) {
                oSymTable->head = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp->key);
            free(temp);
            return 1;
        }
        prev = temp;
        temp = temp->next;
    }
    return 0;
}

int SymTable_contains(SymTable_T oSymTable, const char *pcKey) {
    if (oSymTable == NULL || pcKey == NULL) {
        return 0;
    }
    for (struct bindings *temp = oSymTable->head; temp != NULL; temp = temp->next) {
        if (strcmp(temp->key, pcKey) == 0) {
            return 1;
        }
    }
    return 0;
}

void *SymTable_get(SymTable_T oSymTable, const char *pcKey) {
    if (oSymTable == NULL || pcKey == NULL) {
        return NULL;
    }
    for (struct bindings *temp = oSymTable->head; temp != NULL; temp = temp->next) {
        if (strcmp(temp->key, pcKey) == 0) {
            return temp->value;
        }
    }
    return NULL;
}

void SymTable_map(SymTable_T oSymTable, void (*pfApply)(const char *pcKey, void *pvValue, void *pvExtra),const void *pvExtra){
    assert(oSymTable != NULL);
    assert(pfApply != NULL);   
    struct bindings *curr = oSymTable->head;
    while (curr != NULL) {
        pfApply(curr->key, curr->value, (void*)pvExtra);
        curr = curr->next;
    }
}


void test_put_and_get() {
    SymTable_T table = SymTable_new();
    assert(SymTable_put(table, "key1", "value1"));
    assert(SymTable_put(table, "key2", "value2"));
    assert(SymTable_put(table, "key3", "value3"));

    assert(strcmp(SymTable_get(table, "key1"), "value1") == 0);
    assert(strcmp(SymTable_get(table, "key2"), "value2") == 0);
    assert(strcmp(SymTable_get(table, "key3"), "value3") == 0);

    SymTable_free(table);
}
 
void test_remove() {
    SymTable_T table = SymTable_new();
    assert(SymTable_put(table, "key1", "value1"));
    assert(SymTable_put(table, "key2", "value2"));
    assert(SymTable_put(table, "key3", "value3"));

    assert(SymTable_remove(table, "key2"));
    assert(!SymTable_contains(table, "key2"));

    SymTable_free(table);
}

void test_map(const char *pcKey, void *pvValue, void *pvExtra) {
    int *sum = (int*) pvExtra;
    int value = *(int*) pvValue;
    printf("%s -> %d\n", pcKey, value);
    *sum += value;
}
 
 

int main() {
    test_put_and_get();
    test_remove();
    printf("All tests passed\n");

    return 0;
} 






/* int main() {
    SymTable_T table = SymTable_new();

    int a = 1, b = 2, c = 3;
    SymTable_put(table, "A", &a);
    SymTable_put(table, "B", &b);
    SymTable_put(table, "C", &c);

    int sum = 0;
    SymTable_map(table, test_map, &sum);
    printf("Sum of all values: %d\n", sum);

    SymTable_free(table);
    return 0;
}
 */