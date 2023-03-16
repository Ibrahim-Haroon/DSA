//
//  binary_tree.h
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#ifndef binary_tree_h
#define binary_tree_h

#include <stdbool.h>

typedef void* BST;
//public
BST bst_init(void);
bool bst_isEmpty(BST tree);
void bst_insert(BST tree, int value);
void bst_remove(BST tree, int value);
bool bst_contains(BST tree, int value);
void bst_print(BST tree);
void bst_destroy(BST* tree);

#endif /* binary_tree_h */
