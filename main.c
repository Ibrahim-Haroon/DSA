//
//  main.c
//  data_structures_and_algorithms
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include <stdio.h>
#include "trie.h"

int main(int argc, char** argv) {
    TRIE newTrie = trie_init();
    trie_insert(newTrie, "cage");
    trie_insert(newTrie, "abs");
    trie_insert(newTrie, "bass");
    trie_insert(newTrie, "cage");
    trie_insert(newTrie, "cattle");
    trie_insert(newTrie, "cage");
    trie_printTrie(newTrie);
    
    trie_search(newTrie, "abs") ? printf("Found!\n") : printf("Not in Dictinary!\n");
    trie_destroyTrie(&newTrie);
    return 0;
}
