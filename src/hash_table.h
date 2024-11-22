#ifndef HASH_TABLE_H
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
  char* key;
  char* value;
} ht_item;

typedef struct {
  size_t base_size;
  size_t size;
  size_t count;
  ht_item** items;
} hash_table;

hash_table* ht_new();
void ht_destroy(hash_table* ht);

// Operations
void ht_insert(hash_table* ht, const char* key, const char* value);
char* ht_search(hash_table* ht, const char* key);
bool ht_has(hash_table* ht, const char* key);
void ht_delete(hash_table* ht, const char* key);

#endif // !HASH_TABLE_H
