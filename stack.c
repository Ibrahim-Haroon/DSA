//
//  stack.c
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node_s{
    int value;
    struct node_s* next;
}Node_s;

typedef struct stack{
    Node_s* top;
}Stack;
Node_s* create_stack_node(int num); //private

STACK stack_init(void) {
    Stack* newStack = (Stack*) malloc(sizeof(Stack));
    if (newStack == NULL) {
        fprintf(stderr, "Failed to allocate space for stack");
        exit(EXIT_FAILURE);
    }
    newStack ->top = NULL;
    return newStack;
}

bool stack_isEmpty(STACK stack) {
    Stack* curr_stack = (Stack*)stack;
    if (curr_stack ->top == NULL) return true;
    return false;
}

void stack_push(STACK stack, int num) {
    Stack* curr_stack = (Stack*)stack;
    if (stack_isEmpty(stack)) {
        Node_s* toInsert = create_stack_node(num);
        curr_stack ->top = toInsert;
        return;
    }
    Node_s* toInsert = create_stack_node(num);
    toInsert ->next = curr_stack ->top;
    curr_stack ->top = toInsert;
    return;
}

Node_s* create_stack_node(int num) {
    Node_s* newNode = (Node_s*) malloc(sizeof(Node_s));
    if (newNode == NULL) {
        fprintf(stderr, "Heap is FULL\n");
        exit(EXIT_FAILURE);
    }
    newNode ->value = num;
    newNode ->next = NULL;
    return newNode;
}

void stack_pop(STACK stack) {
    if (stack_isEmpty(stack)) {
        printf("Cannot pop from empty stack\n");
        return;
    }
    Stack* curr_stack = (Stack*)stack;
    if (curr_stack ->top->next == NULL) { //only one node
        free(curr_stack ->top);
        curr_stack ->top = NULL;
        return;
    }
    Node_s* toDelete = curr_stack ->top;
    curr_stack ->top = curr_stack ->top ->next;
    free(toDelete);
    toDelete = NULL;
    return;
}

int stack_peak(STACK stack) {
    if (stack_isEmpty(stack)) {
        printf("EMPTY\n");
        return 0xC0FFEE;
    }
    Stack* curr_stack = (Stack*)stack;
    return curr_stack ->top->value;
}

void stack_print(STACK stack) {
    if (stack_isEmpty(stack)) {
        printf("EMPTY\n");
        return;
    }
    Stack* curr_stack = (Stack*)stack;
    Node_s* temp = curr_stack ->top;
    while (temp != NULL) {
        printf("\t%d\n", temp ->value);
        temp = temp ->next;
    }
    printf("\tNULL\n");
    return;
}

void stack_destroy(STACK* stack) {
    Stack* curr_stack = (Stack*)stack;
    if (stack_isEmpty(*stack)) {
        free(*stack);
        *stack = NULL;
        return;
    }
    while (curr_stack ->top != NULL) {
        Node_s* toDelete = curr_stack ->top;
        curr_stack ->top = curr_stack ->top->next;
        free(toDelete);
        toDelete = NULL;
    }
    free(*stack);
    *stack = NULL;
    return;
}

