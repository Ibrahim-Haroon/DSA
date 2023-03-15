//
//  stack.h
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#ifndef stack_h
#define stack_h

#include <stdbool.h>

typedef void* STACK;
//public
STACK stack_init(void);
bool stack_isEmpty(STACK stack);
void stack_push(STACK stack, int num);
void stack_pop(STACK stack);
int stack_peak(STACK stack);
void stack_print(STACK stack);
void stack_destroy(STACK* stack);

#endif /* stack_h */
