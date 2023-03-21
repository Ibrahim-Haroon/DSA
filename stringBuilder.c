//
//  stringBuilder.c
//  data_structures_and_algorithms
//
//  Created by Ibrahim Haroon on 3/15/23.
//

#include "stringBuilder.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct string{
    int size;
    int capacity;
    char* word;
}String;
static bool string_isFull(StringBuilder string);      //private
static void increaseStringSize(StringBuilder string);//private

StringBuilder stringBuilder_init(void) {
    String* string = (String*) malloc(sizeof(String));
    if (string == NULL) {
        fprintf(stderr, "Failed to allocate space for string\n");
        exit(EXIT_FAILURE);
    }
    string ->size = 0;
    string ->capacity = 7;
    string ->word = (char*) malloc(sizeof(char) * string ->capacity);
    if (string ->word == NULL) {
        fprintf(stderr, "Failed to allocate space for word\n");
        free(string);
        exit(EXIT_FAILURE);
    }
    string ->word[string ->size] = '\0'; //null terminate word
    return string;
}

bool string_isEmpty(StringBuilder string) {
    if (string == NULL) {
        printf("Don't pass NULL\n");
        return NULL;
    }
    String* curr_string = (String*)string;
    if (curr_string ->size <= 0) return true;
    return false;
}

bool string_isFull(StringBuilder string) {
    String* curr_string = (String*)string;
    if (curr_string ->size >= curr_string ->capacity) return true;
    return false;
}

#define LOAD_FACTOR (2)
void increaseStringSize(StringBuilder string) {
    String* curr_string = (String*)string;
    char* largerWord = (char*) malloc(sizeof(char) * (curr_string ->capacity * LOAD_FACTOR));
    if (largerWord == NULL) {
        fprintf(stderr, "Failed to append, HEAP is full!\n");
        exit(EXIT_FAILURE);
    }
    //copy word into new word
    for (int i = 0; i < curr_string ->size; i++) {
        largerWord[i] = curr_string ->word[i];
    }
    free(curr_string ->word);
    curr_string ->word = largerWord;
    curr_string ->capacity *= LOAD_FACTOR;
    return;
}

int stringLen(char* string) {
    int len = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        len++;
    }
    return len;
}

void stringBuilder_appendChar(char c, StringBuilder string) {
    if (string_isFull(string)) increaseStringSize(string);
    String* curr_string = (String*)string;
    curr_string ->word[curr_string ->size++] = c;
    curr_string->word[curr_string ->size] = '\0';
    return;
}

void stringBuilder_append(char* anything, StringBuilder string) {
    if (anything == NULL || *anything == '\0') return; //cannot enter invalid or empty string
    String* curr_string = (String*)string;
    for (int i = 0; i < stringLen(anything); i++) {
        if (string_isFull(string)) increaseStringSize(string);
        curr_string ->word[curr_string ->size++] = anything[i];
    }
    curr_string ->word[curr_string ->size] = '\0'; //null terminate string
    return;
}

void stringBuilder_pop(StringBuilder string) {
    if (string_isEmpty(string)) return;
    String* curr_string = (String*)string;
    curr_string ->size--;
    curr_string ->word[curr_string ->size] = '\0';
    return;
}

void print_s(StringBuilder string) {
    if (string_isEmpty(string)) {
        printf("EMPTY\n");
        return;
    }
    String* curr_string = (String*)string;
    printf("%s\n", curr_string ->word);
    return;
}

int string_len(StringBuilder string) {
    if (string_isEmpty(string)) return -1;
    String* curr_string = (String*)string;
    return curr_string ->size;
}

void stringBuilder_destroy(StringBuilder* string) {
    if (string_isEmpty(*string)) {
        free(*string);
        *string = NULL;
        return;
    }
    String** curr_string = (String**)string;
    free((*curr_string) ->word);
    free(*string);
    *string = NULL;
}
