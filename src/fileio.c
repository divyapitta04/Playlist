#include "../include/fileio.h"

const char* readFromFile(const char* filename){
	FILE* fp;
	static char string[50*MAXLENGTH];
	fp = fopen(filename, "r");
	if(fp == NULL) {
		printf("Error in opening the file\n"); EXIT_FAILURE;
	}
	fgets(string,50*MAXLENGTH, fp);
	fclose(fp);
	return string;
}

//Takes a big string, splits it into multiple strings and each string is
//stored in a Queue;
Queue* splitString(const char* string, const char delim){
	Queue* splitParts = createQueue();
	char temp[MAXLENGTH];
	unsigned count = 0;
	for(unsigned i=0; i<=strlen(string); i++){
		if(*(string+i) != delim ) temp[i-count] = *(string+i);
		else {
			temp[i] = '\0';
			enqueue(splitParts, temp);
			count = i+1;
		}
	}
	return splitParts;
}

//Insertes each elements from queue to the bst
Tree* constructTree(Queue* queueptr){
	Tree* SongsLibrary = createTree();
	while(queueptr->size != 0){
	//	SongsLibrary->root = insertElement(SongsLibrary->root, dequeue(queueptr)->name);
		char* songname = dequeue(queueptr)->name;
		SongsLibrary->root = insertElement(SongsLibrary->root, songname);
	}
	return SongsLibrary;
}

//Combines all the above defined peice wise functions
Tree* BuildLibrary(const char* filename){
	char* string = (char*)readFromFile(filename);
	Queue* split = splitString(string, ':');
	printf("Songs in the text file are added into Library\n");
	//printallElements(split);
	return constructTree(splitString(readFromFile(filename),':'));
}
