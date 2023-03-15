//
//  hash_map.h
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#ifndef hash_map_h
#define hash_map_h

#include <stdbool.h>

typedef void* HashMap;
//public
HashMap hashMap_init(void);
bool hashMap_isEmpty(HashMap hashmap);
void hashMap_insert(HashMap hashmap, int key, int value);
void hashMap_remove_entry(HashMap hashmap, int key);
bool hashMap_contains(HashMap hashmap, int key);
void hashMap_print(HashMap hashmap);
void hashMap_destroy(HashMap* hashmap);

#endif /* hash_map_h */
