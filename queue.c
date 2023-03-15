//
//  queue.c
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct node_q{ //_q to differentiate with other node structs
    int value;
    struct node_q* next;
    struct node_q* prev;
}Node_q;

typedef struct queue{
    Node_q* head;
    Node_q* tail;
}Queue;

Node_q* create_queue_node(int num); //private

QUEUE queue_init(void) {
    Queue* newQueue = (Queue*) malloc(sizeof(Queue));
    if (newQueue == NULL) {
        fprintf(stderr, "Failed to allocated space for Queue\n");
        exit(EXIT_FAILURE);
    }
    newQueue ->head = NULL;
    newQueue ->tail = NULL;
    return newQueue;
}

bool queue_isEmpty(QUEUE queue) {
    Queue* current_queue = (Queue*)queue;
    if (current_queue ->head == NULL && current_queue ->tail == NULL) {
        return true;
    }
    return false;
}

void enqueue(QUEUE queue, int num) {
    Queue* current_queue = (Queue*)queue;
    if (queue_isEmpty(queue)) {
        Node_q* toInsert = create_queue_node(num);
        current_queue ->head = toInsert;
        current_queue ->tail = current_queue ->head;
        return;
    }
    //only one node in queue
    if (current_queue ->head == current_queue ->tail) {
        Node_q* toInsert = create_queue_node(num);
        toInsert ->next = current_queue ->head;
        current_queue ->tail ->prev = toInsert;
        current_queue ->head = toInsert;
        return;
    }
    Node_q* toInsert = create_queue_node(num);
    toInsert ->next = current_queue ->head;
    current_queue ->head ->prev = toInsert;
    current_queue ->head = toInsert;
}

Node_q* create_queue_node(int num) {
    Node_q* newNode = (Node_q*) malloc(sizeof(Node_q));
    if (newNode == NULL) {
        printf("Heap is FULL\n");
        exit(EXIT_FAILURE);
    }
    newNode ->value = num;
    newNode ->next = NULL;
    newNode ->prev = NULL;
    return newNode;
}

void dequeue(QUEUE queue) {
    if (queue_isEmpty(queue)) {
        printf("Invalid! Queue is empty\n");
        return;
    }
    Queue* current_queue = (Queue*)queue;
    if (current_queue ->head == current_queue ->tail) { //one node
        free(current_queue ->head);
        current_queue ->head = NULL;
        current_queue ->tail = NULL;
        return;
    }
    Node_q* temp = current_queue ->tail;
    current_queue ->tail = current_queue ->tail ->prev;
    current_queue ->tail ->next = NULL;
    free(temp);
    temp = NULL;
    return;
}

void queue_print(QUEUE queue) {
    if (queue_isEmpty(queue)) {
        printf("EMPTY\n");
        return;
    }
    Queue* current_queue = (Queue*)queue;
    Node_q* temp = current_queue ->head;
    printf("Front ");
    while (temp != NULL) {
        if (temp ->next == NULL) {
            printf("%d", temp ->value);
        }
        else printf("%d <-> ", temp ->value);
        temp = temp ->next;
    }
    printf(" Back\n");
    return;
}

void queue_destroy(QUEUE* queue) {
    if (queue_isEmpty(*queue)) {
        free(*queue);
        *queue = NULL;
        return;
    }
    Queue* current_queue = (Queue*)queue;
    while (current_queue ->head != NULL) {
        Node_q* temp = current_queue ->head;
        current_queue ->head = current_queue ->head->next;
        free(temp);
        temp = NULL;
    }
    free(*queue);
    *queue = NULL;
    return;
}
