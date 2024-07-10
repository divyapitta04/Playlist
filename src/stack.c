#include "../include/stack.h"

Stack* createStack(){
	Stack* newstack = (Stack*)malloc(sizeof(Stack));
	newstack->last = NULL;
	newstack->size = 0;
	return newstack;
}

void push(Stack* stackptr, const char* _songname){
	Node* newnode = (Node*)malloc(sizeof(Node));
	//newnode->songptr = (Song*)_songptr;
	strcpy(newnode->songName, _songname);
	newnode->next = stackptr->last;
	stackptr->last = newnode;
	stackptr->size++;
}

Node* pop(Stack* stackptr){
	if(stackptr->size == 0){
		printf("no elements in stack \n"); return NULL;
	}
	Node* popednode;
	popednode = stackptr->last;
	stackptr->last = popednode->next;
	popednode->next = NULL;
	stackptr->size--;
	return popednode;
}

unsigned isEmpty(Stack* stackptr){
	if(stackptr->size == 0) return 1;
	else return 0;
}

void freeStack(Stack* stackptr){
	while(!isEmpty(stackptr)) free(pop(stackptr));
}
