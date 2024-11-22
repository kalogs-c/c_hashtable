#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  hash_table* ht = ht_new();
  if (ht == NULL) {
    puts("Failed to create hash table");
    return EXIT_FAILURE;
  }

  ht_insert(ht, "key1", "value1");
  ht_insert(ht, "key2", "value2");
  ht_insert(ht, "key3", "value3");
  ht_insert(ht, "key4", "value4");
  ht_insert(ht, "key5", "value5");
  ht_insert(ht, "key6", "value6");
  ht_insert(ht, "key7", "value7");
  ht_insert(ht, "key8", "value8");
  ht_insert(ht, "key9", "value9");
  ht_insert(ht, "key10", "value10");
  ht_insert(ht, "key11", "value11");
  ht_insert(ht, "key12", "value12");
  ht_insert(ht, "key13", "value13");
  ht_insert(ht, "key14", "value14");
  ht_insert(ht, "key15", "value15");
  ht_insert(ht, "key16", "value16");
  ht_insert(ht, "key17", "value17");
  ht_insert(ht, "key18", "value18");
  ht_insert(ht, "key19", "value19");

  printf("Key 10: %s\n", ht_search(ht, "key10"));
  printf("Key 20: %s\n", ht_search(ht, "key20"));

  ht_destroy(ht);
  return EXIT_SUCCESS;
}
