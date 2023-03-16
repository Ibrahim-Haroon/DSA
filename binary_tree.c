//
//  binary_tree.c
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include "binary_tree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node{
    int value;
    struct tree_node* left;
    struct tree_node* right;
}Tree_node;

typedef struct bst{
    Tree_node* root;
}Binary_tree;
Tree_node* create_treeNode(int value); //private
void balance_tree(BST tree);            //private
void insert_recursive(Tree_node** root, int value);  //private
bool contains_recursive(Tree_node* root, int value); //private
void print_recursive(Tree_node* root, int space);             //private
void destroy_recursive(Tree_node* root);          //private

BST bst_init(void) {
    Binary_tree* newTree = (Binary_tree*) malloc(sizeof(Binary_tree));
    if (newTree == NULL) {
        fprintf(stderr, "Failed to allocate space for Binary Tree\n");
        exit(EXIT_FAILURE);
    }
    newTree ->root = NULL; //empty
    return newTree;
}

bool bst_isEmpty(BST tree) {
    Binary_tree* curr_tree = (Binary_tree*)tree;
    if (curr_tree ->root == NULL) return true;
    return false;
}

Tree_node* create_treeNode(int value) {
    Tree_node* newNode = (Tree_node*) malloc(sizeof(Tree_node));
    if (newNode == NULL) {
        fprintf(stderr, "Failed to allocate space for a new tree Node\n");
        exit(EXIT_FAILURE);
    }
    newNode ->value = value;
    newNode ->left = NULL;
    newNode ->right = NULL;
    return newNode;
}

void balance_tree(BST tree) {   //AVL tree
    return;
}

void insert_recursive(Tree_node** root, int value) {
    if (*root == NULL) {
        *root = create_treeNode(value);
        return;
    }
    if (value < (*root) ->value) {
        insert_recursive(&((*root) ->left), value);
    }
    else if (value > (*root) ->value) {
        insert_recursive(&((*root) ->right), value);
    }
}

void bst_insert(BST tree, int value) {
    Binary_tree* curr_tree = (Binary_tree*)tree;
    if (bst_isEmpty(tree)) {
        curr_tree ->root = create_treeNode(value);
        return;
    }
    insert_recursive(&(curr_tree ->root), value);
    return;
}


void bst_remove(BST tree, int value);

bool contains_recursive(Tree_node* root, int value) {
    if (root == NULL) {
        return false;
    }
    
    if (value < root->value) {
        contains_recursive(root->left, value);
    }
    else if (value > root->value) {
        contains_recursive(root->right, value);
    }
    
    return true;//if value == current node
}

bool bst_contains(BST tree, int value) {
    Binary_tree* curr_tree = (Binary_tree*)tree;
    
    return contains_recursive(curr_tree ->root, value);
}

#define COUNT (5)
void print_recursive(Tree_node* root, int space) {
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print_recursive(root->right, space);
 
    // Print current node after space
    printf("\n");
    for (int i = COUNT; i < space; i++) printf(" ");
    printf("%d\n", root->value);
 
    // Process left child
    print_recursive(root->left, space);
}

void bst_print(BST tree) {
    if (bst_isEmpty(tree)) {
        printf("EMPTY\n");
        return;
    }
    Binary_tree* curr_tree = (Binary_tree*)tree;
    print_recursive(curr_tree ->root, 0);
    return;
}

void destroy_recursive(Tree_node* root) {
    if (root == NULL) {
        return;
    }
    destroy_recursive(root ->left);
    destroy_recursive(root ->right);
    free(root);
}

void bst_destroy(BST* tree) {
    if (bst_isEmpty(*tree)) {
        free(*tree);
        *tree = NULL;
        return;
    }
    Binary_tree* curr_tree = (Binary_tree*)tree;
    destroy_recursive(curr_tree ->root);
    *tree = NULL;
    return;
}
