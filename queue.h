//
//  queue.h
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#ifndef queue_h
#define queue_h

#include <stdbool.h>

typedef void* QUEUE;

QUEUE queue_init(void);
bool queue_isEmpty(QUEUE queue);
void enqueue(QUEUE queue, int num);
void dequeue(QUEUE queue);
void queue_print(QUEUE queue);
void queue_destroy(QUEUE* queue);

#endif /* queue_h */
