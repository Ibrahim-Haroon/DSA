//
//  doubly_linked_list.c
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include "doubly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node_d{
    int value;
    struct node_d* next;
    struct node_d* prev;
}Node_d;
Node_d* create_node_double(int num); //private

DOUBLY_LINKED_LIST dll_init(void) {
    Node_d* newLinkedList = (Node_d*) malloc(sizeof(Node_d));
    if (newLinkedList == NULL) {
        fprintf(stderr, "Heap is FULL\n");
        exit(EXIT_FAILURE);
    }
    newLinkedList ->next = NULL;
    newLinkedList ->prev = NULL;
    return newLinkedList;
}

bool dll_isEmpty(DOUBLY_LINKED_LIST head) {
    Node_d* _head = (Node_d*)head;
    if (_head -> next == NULL && _head ->prev == NULL) return true;
    return false;
}

void dll_add(DOUBLY_LINKED_LIST* head, int num) {
    Node_d** _head = (Node_d**)head;
    if (dll_isEmpty(*head)) {          //empty linked list
        Node_d* newNode = create_node_double(num);
        (*_head) -> next = newNode;
        newNode ->prev = (*_head);
        return;
    }
    Node_d* newNode = create_node_double(num);
    newNode ->next = (*_head) ->next;
    (*_head) ->next ->prev = newNode;
    (*_head) ->next = newNode;
    return;
}

Node_d* create_node_double(int num) {
    Node_d* newNode = (Node_d*) malloc(sizeof(Node_d));
    if (newNode == NULL) {
        printf("Heap is FULL\n");
        exit(EXIT_FAILURE);
    }
    newNode ->value = num;
    newNode ->next = NULL;
    newNode ->prev = NULL;
    return newNode;
}

void dll_remove(DOUBLY_LINKED_LIST* head) {
    if (dll_isEmpty(*head)) return;
    Node_d** _head = (Node_d**)head;
    Node_d* temp = (*_head) ->next;
    (*_head) ->next = temp ->next;
    free(temp);
    temp = NULL;
    (*_head) ->prev = NULL;
    return;
}

void dll_remove_num(DOUBLY_LINKED_LIST* head, int num) {
    if (dll_isEmpty(head)) return;
    Node_d** linker = (Node_d**)head;
    Node_d* slow = *linker;
    Node_d* fast = *linker;
    
    if (fast ->next->value == num) { //remove head of linked list
        dll_remove(head);
        return;
    }
    
    while (fast != NULL && fast ->value != num) {
        slow = fast;
        fast = fast ->next;
    }
    if (fast == NULL) {
        printf("%d is not in the linked list\n", num);
        return;
    }
    
    slow ->next = fast ->next;
    slow ->next ->prev= slow;
    free(fast);
    (fast) = NULL;
    
    return;
}

bool dll_contains(DOUBLY_LINKED_LIST head, int num) {
    if (dll_isEmpty(head)) return false;
    Node_d* temp = (Node_d*)head;
    while (temp != NULL && temp ->value != num) {
        temp = temp ->next;
    }
    return temp; //temp will either equal NULL or the value we're looking
}

void dll_print(DOUBLY_LINKED_LIST head) {
    if (dll_isEmpty(head)) {
        printf("EMPTY\n");
        return;
    }
    Node_d* temp = (Node_d*)head;
    temp = temp ->next;
    printf("NULL <- ");
    while (temp != NULL) {
        if (temp ->next == NULL) {
            printf("%d -> NULL\n", temp ->value);
        }
        else printf("%d <-> ", temp ->value);
        temp = temp ->next;
    }
    return;
}

void dll_destroy(DOUBLY_LINKED_LIST* head) {
    if (dll_isEmpty(*head)) {
        free(*head);
        *head = NULL;
        return;
    }
    Node_d* _head = (Node_d*)*head;
    while (_head != NULL) {
        Node_d* temp = _head;
        _head = _head ->next;
        free(temp);
        temp = NULL;
    }
    *head = NULL;
    return;
}
