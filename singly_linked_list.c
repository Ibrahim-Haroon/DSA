//
//  singly_linked_list.c
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include "singly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int value;
    struct node* next;
}Node;
static Node* create_node(int num); //private

SINGLY_LINKED_LIST ll_init(void) {
    Node* newLinkedList = (Node*) malloc(sizeof(Node));
    if (newLinkedList == NULL) {
        fprintf(stderr, "Heap is FULL\n");
        exit(EXIT_FAILURE);
    }
    newLinkedList ->next = NULL;
    return newLinkedList;
}

bool ll_isEmpty(SINGLY_LINKED_LIST head) {
    Node* _head = (Node*)head;
    if (_head -> next == NULL) return true;
    return false;
}

void ll_add(SINGLY_LINKED_LIST* head, int num) {
    Node** _head = (Node**)head;
    if (ll_isEmpty(head)) {          //empty linked list
        Node* newNode = create_node(num);
        (*_head) -> next = newNode;
        return;
    }
    Node* newNode = create_node(num);
    newNode ->next = (*_head) ->next;
    (*_head) ->next = newNode;
    return;
}

Node* create_node(int num) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Heap is FULL\n");
        exit(EXIT_FAILURE);
    }
    newNode ->value = num;
    newNode ->next = NULL;
    return newNode;
}

void ll_remove(SINGLY_LINKED_LIST* head) {
    if (ll_isEmpty(*head)) return;
    Node** _head = (Node**)head;
    Node* temp = (*_head) ->next;
    (*_head) ->next = temp ->next;
    free(temp);
    temp = NULL;

    return;
}

void ll_remove_num(SINGLY_LINKED_LIST* head, int num) {
    if (ll_isEmpty(head)) return;
    Node** linker = (Node**)head;
    Node* slow = *linker;
    Node* fast = *linker;
    
    if (fast ->next->value == num) { //remove head of linked list
        ll_remove(head);
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
    free(fast);
    (fast) = NULL;
    
    return;
}

bool ll_contains(SINGLY_LINKED_LIST head, int num) {
    if (ll_isEmpty(head)) return false;
    Node* temp = (Node*)head;
    while (temp != NULL && temp ->value != num) {
        temp = temp ->next;
    }
    return temp; //temp will either equal NULL or the value we're looking
}

void ll_print(SINGLY_LINKED_LIST head) {
    if (ll_isEmpty(head)) {
        printf("EMPTY\n");
        return;
    }
    Node* temp = (Node*)head;
    temp = temp ->next;
    while (temp != NULL) {
        if (temp ->next == NULL) {
            printf("%d -> NULL\n", temp ->value);
        }
        else printf("%d -> ", temp ->value);
        temp = temp ->next;
    }
    return;
}

void ll_destroy(SINGLY_LINKED_LIST* head) {
    if (ll_isEmpty(*head)) {
        free(*head);
        *head = NULL;
        return;
    }
    Node* _head = (Node*)*head;
    while (_head != NULL) {
        Node* temp = _head;
        _head = _head ->next;
        free(temp);
        temp = NULL;
    }
    *head = NULL;
    return;
}
