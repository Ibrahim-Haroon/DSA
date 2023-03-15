//
//  hash_set.h
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#ifndef hash_set_h
#define hash_set_h

#include <stdbool.h>

typedef void* HashSet;
//public
HashSet hashSet_init(void);
bool hashSet_isEmpty(HashSet hashset);
void hashSet_add(HashSet hashset, int key);
void hashSet_remove_entry(HashSet hashset, int key);
bool hashSet_contains(HashSet hashset, int key);
void hashSet_print(HashSet hashset);
void hashSet_destroy(HashSet* hashset);

#endif /* hash_set_h */
