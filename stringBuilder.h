//
//  stringBuilder.h
//  data_structures_and_algorithms
//
//  Created by Ibrahim Haroon on 3/15/23.
//

#ifndef stringBuilder_h
#define stringBuilder_h

#include <stdbool.h>

typedef void* StringBuilder;

StringBuilder stringBuilder_init(void);
bool string_isEmpty(StringBuilder string);
void stringBuilder_appendChar(char c, StringBuilder string);
void stringBuilder_append(char* anything, StringBuilder string);
void stringBuilder_pop(StringBuilder string);
void print_s(StringBuilder string);
int string_len(StringBuilder string);
void stringBuilder_destroy(StringBuilder* string);

#endif /* stringBuilder_h */
