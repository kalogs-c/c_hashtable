#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  hash_table* ht = ht_new();
  if (ht == NULL) {
    puts("Failed to create hash table");
    return EXIT_FAILURE;
  }

  ht_insert(ht, "key1", "value1");
  ht_insert(ht, "key2", "value1");
  printf("Key 2: %s\n", ht_search(ht, "key2"));
  printf("Key 1: %s\n", ht_search(ht, "key1"));
  ht_delete(ht, "key1");
  printf("Key 1: %s\n", ht_search(ht, "key1"));
  printf("Key 3: %s\n", ht_search(ht, "key3"));

  ht_destroy(ht);
  return EXIT_SUCCESS;
}
