//
//  trie.c
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include "trie.h"
#include "stringBuilder.h"
#include <stdio.h>
#include <stdlib.h>

#define ALPHABELT_SIZE (26)

typedef struct trieNode{
    bool terminal;
    struct trieNode* children[ALPHABELT_SIZE];
}TrieNode;

typedef struct trie{
    TrieNode* root;
}Trie;
TrieNode* createTrieNode(void); //private
void print_trie_recursive(TrieNode* currNode, StringBuilder prefix); //private
void destroy_trie_recursive(TrieNode* currNode); //private

TRIE trie_init(void) {
    Trie* newTrie = (Trie*) malloc(sizeof(Trie));
    if (newTrie == NULL) {
        fprintf(stderr, "Failed to allocate space for Trie\n");
        exit(EXIT_FAILURE);
    }
    
    newTrie ->root = (TrieNode*) malloc(sizeof(TrieNode));
    newTrie ->root = NULL;
    
    return newTrie;
}

bool trie_isEmpty(TRIE trie) {
    Trie* curr_trie = (Trie*)trie;
    if (curr_trie ->root == NULL) return true;
    return false;
}

TrieNode* createTrieNode(void) {
    TrieNode* newNode = (TrieNode*) malloc(sizeof(TrieNode));
    if (newNode == NULL) {
        fprintf(stderr, "Failed to allocate space for trie node\n");
        exit(EXIT_FAILURE);
    }
    
    newNode ->terminal = false;
    for (int i = 0; i < ALPHABELT_SIZE; i++) {
        newNode ->children[i] = NULL;
    }
    
    return newNode;
}

void trie_insert(TRIE trie,char* word) {
    Trie* curr_trie = (Trie*)trie;
    if (trie_isEmpty(trie)) {
        curr_trie ->root = createTrieNode();
    }
    
    TrieNode* temp = curr_trie ->root;
    StringBuilder tmp_word = stringBuilder_init();
    stringBuilder_append(word, tmp_word);
    for (int i = 0; i < string_len(tmp_word); i++) {
        int index  = word[i] - 'a';
        if (temp ->children[index] == NULL) {
            temp ->children[index] = createTrieNode();
        }
        temp = temp ->children[index];
    }
    
    if (temp ->terminal == false) {
        temp ->terminal = true;
    }
    
    stringBuilder_destroy(&tmp_word);
    return;
}

bool trie_search(TRIE trie,char* word) {
    if (trie_isEmpty(trie)) return false;
    
    Trie* curr_trie = (Trie*)trie;
    
    StringBuilder tmp = stringBuilder_init();
    stringBuilder_append(word, tmp);
    
    for (int i = 0; i < string_len(tmp); i++) {
        if (curr_trie ->root ->children[word[i] - 'a'] != NULL) {
            curr_trie ->root =  curr_trie ->root ->children[word[i] - 'a'];
            continue;
        }
        stringBuilder_destroy(&tmp);
        return false; //word not in trie
    }
    
    if (curr_trie->root ->terminal == true) return true; //if the last word is the terminating char
                                                         //that means it was a word
    return false;
}


void print_trie_recursive(TrieNode* currNode, StringBuilder prefix) {
    if (currNode ->terminal) { //reached end of word
        print_s(prefix);
    }
    
    for (int i = 0; i < ALPHABELT_SIZE; i++) { //go through every child
        if (currNode ->children[i] != NULL) {
            stringBuilder_appendChar(i + 'a', prefix);
            print_trie_recursive(currNode ->children[i], prefix);
            stringBuilder_pop(prefix);
        }
    }
}

void trie_printTrie(TRIE trie) {
    if (trie_isEmpty(trie)) {
        printf("\t--<EMPTY>--\n");
        return;
    }
    Trie* curr_trie = (Trie*)trie;
    StringBuilder emptyStr = stringBuilder_init();
    print_trie_recursive(curr_trie ->root, emptyStr);
    stringBuilder_destroy(&emptyStr);
    return;
}

void destroy_trie_recursive(TrieNode* currNode) {
    if (currNode == NULL) return;
    
    for (int i = 0; i < ALPHABELT_SIZE; i++) {
        if (currNode ->children[i] != NULL) {
            destroy_trie_recursive(currNode ->children[i]);
        }
    }
    free(currNode);
}

void trie_destroyTrie(TRIE* trie) {
    if (trie_isEmpty(*trie)) { //empty trie
        free(*trie);
        *trie = NULL;
        return;
    }
    Trie** curr_trie = (Trie**)trie;
    destroy_trie_recursive((*curr_trie) ->root);
    
    free(*trie);
    *trie = NULL;
    return;
}
