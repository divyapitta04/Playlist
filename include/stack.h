#ifndef _STACK_H_
#define _STACK_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLENGTH 50


typedef struct Node{
	char songName[MAXLENGTH];
	struct Node* next;
}Node;

typedef struct Stack{
	Node* last;
	unsigned size;
}Stack;

Stack* createStack();

void push(Stack*, const char*);

Node* pop(Stack*);

unsigned isEmpty(Stack*);

void freeStack(Stack*);
#endif
