#include "hash_table.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define HT_PRIME_1 7993
#define HT_PRIME_2 8011

static ht_item* new_item(const char* key, const char* value) {
  ht_item* item = malloc(sizeof(ht_item));
  item->key = strdup(key);
  item->value = strdup(value);
  return item;
}

static void destroy_item(ht_item* item) {
  free(item->key);
  free(item->value);
  free(item);
}

hash_table* ht_new() {
  hash_table* ht = malloc(sizeof(hash_table));
  ht->size = 53;
  ht->count = 0;
  ht->items = calloc(ht->size, sizeof(ht_item*));
  return ht;
}

void ht_destroy(hash_table* ht) {
  for (size_t i = 0; i < ht->size; i++) {
    ht_item* item = ht->items[i];
    if (item != NULL) {
      destroy_item(item);
    }
  }
  free(ht->items);
  free(ht);
}

static size_t hash(const char* key, const int alpha, const size_t ht_size) {
  size_t hash = 0;
  const uint32_t key_len = strlen(key);

  for (int i = 0; i < key_len; i++) {
    hash += pow(alpha, key_len - (i + 1)) * key[i];
    hash = hash % ht_size;
  }

  return hash;
}

static size_t create_hash(const char* key, const size_t ht_size,
                          const uint32_t attempts) {
  const size_t first_hash = hash(key, HT_PRIME_1, ht_size);
  const size_t second_hash = hash(key, HT_PRIME_2, ht_size);

  return (first_hash + (attempts * (second_hash + 1))) % ht_size;
}

void ht_insert(hash_table* ht, const char* key, const char* value) {
  ht_item* item = new_item(key, value);
  size_t index = create_hash(item->key, ht->size, 0);

  int attempts = 1;
  ht_item* curr_item = ht->items[index];
  while (curr_item) {
    index = create_hash(key, ht->size, attempts);
    curr_item = ht->items[index];
    attempts++;
  }

  ht->items[index] = item;
  ht->count++;
}

char* ht_search(hash_table* ht, const char* key) {
  size_t index = create_hash(key, ht->size, 0);
  ht_item* curr_item = ht->items[index];

  int attempts = 1;
  while (curr_item != NULL) {
    if (strcmp(curr_item->key, key) == 0) {
      return curr_item->value;
    }

    index = create_hash(key, ht->size, attempts);
    curr_item = ht->items[index];
    attempts++;
  }

  return NULL;
}

bool ht_has(hash_table* ht, const char* key) {
  size_t index = create_hash(key, ht->size, 0);
  ht_item* curr_item = ht->items[index];

  int attempts = 1;
  while (curr_item != NULL) {
    if (strcmp(curr_item->key, key) == 0) {
      return true;
    }

    index = create_hash(key, ht->size, attempts);
    curr_item = ht->items[index];
    attempts++;
  }

  return false;
}
