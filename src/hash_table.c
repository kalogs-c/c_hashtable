#include "hash_table.h"
#include "prime.h"
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define HT_PRIME_1 7993
#define HT_PRIME_2 8011

const static size_t HT_INITIAL_BASE_SIZE = 50;
static ht_item HT_DELETED_ITEM = {NULL, NULL};

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

static hash_table* new_sized_ht(const size_t base_size) {
  hash_table* ht = malloc(sizeof(hash_table));
  if (ht == NULL) {
    return NULL;
  }

  ht->base_size = base_size;
  ht->size = next_prime(ht->base_size);
  ht->count = 0;
  ht->items = calloc(ht->size, sizeof(ht_item));
  if (ht->items == NULL) {
    return NULL;
  }

  return ht;
}

hash_table* ht_new() { return new_sized_ht(HT_INITIAL_BASE_SIZE); }

void ht_destroy(hash_table* ht) {
  for (size_t i = 0; i < ht->size; i++) {
    ht_item* item = ht->items[i];
    if (item != NULL && item != &HT_DELETED_ITEM) {
      destroy_item(item);
    }
  }
  free(ht->items);
  free(ht);
}

static void resize_ht(hash_table* ht, const size_t base_size) {
  if (base_size < HT_INITIAL_BASE_SIZE) {
    return;
  }

  hash_table* new_ht = new_sized_ht(base_size);
  for (size_t i = 0; i < ht->size; i++) {
    ht_item* item = ht->items[i];
    if (item != NULL && item != &HT_DELETED_ITEM) {
      ht_insert(new_ht, item->key, item->value);
    }
  }

  ht->base_size = new_ht->base_size;
  ht->count = new_ht->count;

  // Swap size and items, to delete new_ht
  const size_t old_size = ht->size;
  ht->size = new_ht->size;
  new_ht->size = old_size;

  ht_item** old_items = ht->items;
  ht->items = new_ht->items;
  new_ht->items = old_items;

  ht_destroy(new_ht);
}

static void resize_up(hash_table* ht) {
  const size_t new_size = ht->base_size * 2;
  resize_ht(ht, new_size);
}

static void resize_down(hash_table* ht) {
  const size_t new_size = ht->base_size / 2;
  resize_ht(ht, new_size);
}

static size_t hash(const char* key, const int alpha, const size_t ht_size) {
  size_t hash = 0;
  const uint32_t key_len = strlen(key);

  for (size_t i = 0; i < key_len; i++) {
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
  const size_t load = ht->count * 100 / ht->size;
  if (load > 70) {
    resize_up(ht);
  }

  ht_item* item = new_item(key, value);
  size_t index = create_hash(item->key, ht->size, 0);

  int attempts = 1;
  ht_item* curr_item = ht->items[index];
  while (curr_item) {
    if (curr_item != &HT_DELETED_ITEM) {
      if (strcmp(curr_item->key, key) == 0) {
        destroy_item(curr_item);
        ht->items[index] = item;
        return;
      }
    }

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
  while (curr_item) {
    if (curr_item != &HT_DELETED_ITEM) {
      if (strcmp(curr_item->key, key) == 0) {
        return curr_item->value;
      }
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
  while (curr_item) {
    if (curr_item != &HT_DELETED_ITEM) {
      if (strcmp(curr_item->key, key) == 0) {
        return true;
      }
    }

    index = create_hash(key, ht->size, attempts);
    curr_item = ht->items[index];
    attempts++;
  }

  return false;
}

void ht_delete(hash_table* ht, const char* key) {
  const size_t load = ht->count * 100 / ht->size;
  if (load < 10) {
    resize_down(ht);
  }

  size_t index = create_hash(key, ht->size, 0);
  ht_item* curr_item = ht->items[index];

  int attempts = 1;
  while (curr_item) {
    if (curr_item != &HT_DELETED_ITEM) {
      if (strcmp(curr_item->key, key) == 0) {
        destroy_item(curr_item);
        ht->items[index] = &HT_DELETED_ITEM;
      }
    }

    index = create_hash(key, ht->size, attempts);
    curr_item = ht->items[index];
    attempts++;
  }

  ht->count--;
}
