//
//  singly_linked_list.h
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#ifndef singly_linked_list_h
#define singly_linked_list_h

#include <stdbool.h>

typedef void* SINGLY_LINKED_LIST; //s for singly linked

//public methods
SINGLY_LINKED_LIST ll_init(void);
void ll_add(SINGLY_LINKED_LIST* head, int num);
void ll_remove(SINGLY_LINKED_LIST* head);
void ll_remove_num(SINGLY_LINKED_LIST* head, int num);
bool ll_contains(SINGLY_LINKED_LIST head, int num);
bool ll_isEmpty(SINGLY_LINKED_LIST head);
void ll_print(SINGLY_LINKED_LIST head);
void ll_destroy(SINGLY_LINKED_LIST* head);

#endif /* singly_linked_list_h */
