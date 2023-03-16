//
//  trie.h
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#ifndef trie_h
#define trie_h

#include <stdbool.h>

typedef void* TRIE;

TRIE trie_init(void);
bool trie_isEmpty(TRIE trie);
void trie_insert(TRIE trie,char* word);
bool trie_search(TRIE trie,char* word);
void trie_printTrie(TRIE trie);
void trie_destroyTrie(TRIE* trie);

#endif /* trie_h */
