//
//  doubly_linked_list.h
//  DSA
//
//  Created by Ibrahim Haroon on 3/14/23.
//

#ifndef doubly_linked_list_h
#define doubly_linked_list_h

#include <stdbool.h>

typedef void* DOUBLY_LINKED_LIST;

//public methods
DOUBLY_LINKED_LIST dll_init(void);
void dll_add(DOUBLY_LINKED_LIST* head, int num);
void dll_remove(DOUBLY_LINKED_LIST* head);
void dll_remove_num(DOUBLY_LINKED_LIST* head, int num);
bool dll_contains(DOUBLY_LINKED_LIST head, int num);
bool dll_isEmpty(DOUBLY_LINKED_LIST head);
void dll_print(DOUBLY_LINKED_LIST head);
void dll_destroy(DOUBLY_LINKED_LIST* head);

#endif /* doubly_linked_list_h */
