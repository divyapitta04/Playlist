#include "../include/queue.h"

Queue* createQueue(){
	Queue* newQueue = (Queue*)malloc(sizeof(Queue));
	if(newQueue == NULL){
		printf("Error in creating a Queue\n");
	}
	newQueue->head = NULL;
	newQueue->size = 0;
	newQueue->last = NULL;
	return newQueue;
}

void enqueue(Queue* queueptr,const char* name){
	QueueNode* newnode = (QueueNode*)malloc(sizeof(QueueNode));
	strcpy(newnode->name,name);
	newnode->next = queueptr->head;
	queueptr->head = newnode;
	if(!queueptr->size){
		queueptr->last = queueptr->head;
	}
	queueptr->size++;
}

QueueNode* dequeue(Queue* queueptr){
	if(!queueptr->size || (queueptr == NULL)){
		printf("No QueueNodes are present\n");
		return NULL;
	}
	QueueNode* popedQueueNode = queueptr->last;
	queueptr->size--;
	QueueNode* nodeptr = queueptr->head;
	for(unsigned i=1;i<queueptr->size;i++){
		nodeptr = nodeptr->next;
	}
	queueptr->last = nodeptr;
	return popedQueueNode;
}

void destroyQueue(Queue *queueptr){
	QueueNode* temp;
	while(queueptr->head != NULL){
		temp = queueptr->head;
		queueptr->head = queueptr->head->next;
		free(temp);
	}
	free(queueptr);
}

void printallElements(Queue* queueptr){
	while(queueptr->size ){
		printf(" %s\n",dequeue(queueptr)->name);
	}
}
