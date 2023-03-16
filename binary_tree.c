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
    int height;
}Tree_node;

typedef struct bst{
    Tree_node* root;
}Binary_tree;
Tree_node* create_treeNode(int value);          //private
int getHeight(Tree_node* root);                 //private
int getBalanceFactor(Tree_node* root);          //private
void balance_tree(BST tree);                    //private
void insert_recursive(Tree_node** root, int value);  //private
void remove_recursive(Tree_node** root, int value); //private
bool contains_recursive(Tree_node* root, int value); //private
void print_recursive(Tree_node* root, int space);   //private
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
    newNode ->height = 1;
    return newNode;
}

int getHeight(Tree_node* root) {
    if (root == NULL) {
        return 0;
    }
    return root->height;
}

int getBalanceFactor(Tree_node* root) {
    if (root == NULL) {
        return 0;
    }
    return getHeight(root ->left) - getHeight(root->right);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Tree_node* rotateLeft(Tree_node* parent) {
    Tree_node* newParent = parent->right;
    Tree_node* newLeftChild = newParent->left;
    newParent->left = parent;
    parent->right = newLeftChild;
    parent->height = max(getHeight(parent->left), getHeight(parent->right)) + 1;
    newParent->height = max(getHeight(newParent->left), getHeight(newParent->right)) + 1;

    return newParent;
}

Tree_node* rotateRight(Tree_node* parent) {
    Tree_node* newParent = parent->left;
    Tree_node* newRightChild = newParent->right;
    newParent->right = parent;
    parent->left = newRightChild;
    parent->height = max(getHeight(parent->left), getHeight(parent->right)) + 1;
    newParent->height = max(getHeight(newParent->left), getHeight(newParent->right)) + 1;
    
    return newParent;
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

    // update height of current node
    (*root)->height = 1 + max(getHeight((*root)->left), getHeight((*root)->right));
    // calculate balance factor
    int balanceFactor = getBalanceFactor(*root);

    // check if the tree is unbalanced
    if (balanceFactor > 1 && value < (*root)->left->value) {
        // left-left case
        *root = rotateRight(*root);
    }
    else if (balanceFactor < -1 && value > (*root)->right->value) {
        // right-right case
        *root = rotateLeft(*root);
    }
    else if (balanceFactor > 1 && value > (*root)->left->value) {
        // left-right case
        (*root)->left = rotateLeft((*root)->left);
        *root = rotateRight(*root);
    }
    else if (balanceFactor < -1 && value < (*root)->right->value) {
        // right-left case
        (*root)->right = rotateRight((*root)->right);
        *root = rotateLeft(*root);
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

Tree_node* succesor_node(Tree_node* parent) {
    Tree_node* current = parent->right;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

void remove_recursive(Tree_node** root, int value) {
    if (*root == NULL) {
        return; //value was not in the tree
    }
    if (value < (*root) ->value) {
        remove_recursive((&(*root) ->left), value);
    }
    else if (value > (*root) ->value) {
        remove_recursive((&(*root) ->right), value);
    }
    else {
        // case 1: no child or one child
        if ((*root)->left == NULL) {
            Tree_node* temp = (*root)->right;
            free(*root);
            *root = temp;
        }
        else if ((*root)->right == NULL) {
            Tree_node* temp = (*root)->left;
            free(*root);
            *root = temp;
        }
        // case 2: two children
        else {
            Tree_node* succesor = succesor_node((*root)->right);
            (*root)->value = succesor->value;
            remove_recursive(&((*root)->right), succesor->value);
        }
    }
    // update height of current node
    if (*root != NULL) {
        (*root)->height = 1 + max(getHeight((*root)->left), getHeight((*root)->right));
        // calculate balance factor
        int balanceFactor = getBalanceFactor(*root);

        // check if the tree is unbalanced
        if (balanceFactor > 1 && getBalanceFactor((*root)->left) >= 0) {
            // left-left case
            *root = rotateRight(*root);
        }
        else if (balanceFactor > 1 && getBalanceFactor((*root)->left) < 0) {
            // left-right case
            (*root)->left = rotateLeft((*root)->left);
            *root = rotateRight(*root);
        }
        else if (balanceFactor < -1 && getBalanceFactor((*root)->right) <= 0) {
            // right-right case
            *root = rotateLeft(*root);
        }
        else if (balanceFactor < -1 && getBalanceFactor((*root)->right) > 0) {
            // right-left case
            (*root)->right = rotateRight((*root)->right);
            *root = rotateLeft(*root);
        }
    }
}

void bst_remove(BST tree, int value) {
    if (bst_isEmpty(tree)) return;
    Binary_tree* curr_tree = (Binary_tree*)tree;
    remove_recursive(&(curr_tree->root), value);
}


bool contains_recursive(Tree_node* root, int value) {
    if (root == NULL) {
        return false;
    }
    if (root ->value == value) {
        return true;
    }
    if (value < root->value) {
        return contains_recursive(root->left, value);
    }
    else {
        return contains_recursive(root->right, value);
    }

    //never reaches
    return false;
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
