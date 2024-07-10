#ifndef _QUEUE_H
#define _QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLENGTH 50

typedef struct QueueNode{
	char name[MAXLENGTH];
	struct QueueNode* next;
}QueueNode;

typedef struct Queue{
	QueueNode* head;
	unsigned size;
	QueueNode* last;
}Queue;

Queue* createQueue();

void enqueue(Queue*, const char* _name);

QueueNode* dequeue(Queue*);

void destroyQueue(Queue*);

void printallElements(Queue*);
#endif

