#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtable.h"



/* int main(void) {
    SymTable_T table = SymTable_new();

    // Test SymTable_put and SymTable_get
    int x = 5;
    SymTable_put(table, "foo", &x);
    int *value = (int *)SymTable_get(table, "foo");
    if (value == NULL || *value != 5) {
        printf("SymTable_put or SymTable_get failed\n");
        return EXIT_FAILURE;
    }

    // Test SymTable_contains and SymTable_remove
    if (!SymTable_contains(table, "foo")) {
        printf("SymTable_contains failed\n");
        return EXIT_FAILURE;
    }
    SymTable_remove(table, "foo");
    if (SymTable_contains(table, "foo")) {
        printf("SymTable_remove failed\n");
        return EXIT_FAILURE;
    }

    // Test SymTable_getLength and SymTable_map
    for (int i = 0; i < 10; i++) {
        char key[4];
        sprintf(key, "%d", i);
        SymTable_put(table, key, &i);
    }
    if (SymTable_getLength(table) != 10) {
        printf("SymTable_getLength failed\n");
        return EXIT_FAILURE;
    }
    SymTable_map(table, print_table, NULL);

    // Test SymTable_free
    SymTable_free(table);
    printf("All tests passed!\n");
    return EXIT_SUCCESS;
}

 void print_table(const char *key, void *value, void *extra) {
    printf("%s: %d\n", key, *((int*)value));
}  */









/* 
void test_SymTable_new() {
    SymTable_T sym_table = SymTable_new();
    assert(sym_table != NULL);
    assert(SymTable_getLength(sym_table) == 0);
    SymTable_free(sym_table);
}

void test_SymTable_put_get_contains() {
    SymTable_T sym_table = SymTable_new();
    assert(sym_table != NULL);
    
    char *key1 = "key1";
    int value1 = 1;
    char *key2 = "key2";
    char *value2 = "value2";
    char *key3 = "key3";
    double value3 = 3.14;
    
    assert(SymTable_put(sym_table, key1, &value1) == 1);
    assert(SymTable_put(sym_table, key2, value2) == 1);
    assert(SymTable_put(sym_table, key3, &value3) == 1);
    assert(SymTable_contains(sym_table, key1) == 1);
    assert(SymTable_contains(sym_table, key2) == 1);
    assert(SymTable_contains(sym_table, key3) == 1);
    assert(SymTable_contains(sym_table, "non-existent key") == 0);
    assert(SymTable_get(sym_table, key1) == &value1);
    assert(SymTable_get(sym_table, key2) == value2);
    assert(SymTable_get(sym_table, key3) == &value3);
    
    SymTable_free(sym_table);
}

void increment_value(const char *pcKey, void *pvValue, void *pvExtra) {
    int *value = (int *)pvValue;
    (*value)++;
}

void test_SymTable_map() {
    SymTable_T sym_table = SymTable_new();
    assert(sym_table != NULL);
    
    char *key1 = "key1";
    int value1 = 1;
    char *key2 = "key2";
    int value2 = 2;
    
    assert(SymTable_put(sym_table, key1, &value1) == 1);
    assert(SymTable_put(sym_table, key2, &value2) == 1);
    
    int extra = 0;
    SymTable_map(sym_table, increment_value, &extra);
    
    assert(value1 == 2);
    assert(value2 == 3);
    
    SymTable_free(sym_table);
}

int main() {
    test_SymTable_new();
    test_SymTable_put_get_contains();
    test_SymTable_map();
    printf("All tests passed.\n");
    return 0;
}
 */





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SymTable.h"

void test_put_get() {
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
    test_map();

    return 0;
}
