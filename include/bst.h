#ifndef _Tree_H_
#define _Tree_H_

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include <string.h>
#define MAXLENGTH 50
#define LEFT 'L'
#define RIGHT 'R'
#define DIFF(string1, string2) strcmp(string1, string2)

typedef struct Song{
	char songName[MAXLENGTH];
	struct Song *parent, *left, *right;
	//this will not be used here but will be useful for avl tree
	unsigned height;
}Song;

typedef struct Tree{
	Song* root;
}Tree;

// -- will be reused in avl tree
Tree* createTree();

Song* searchElement(Song* songptr, const char* name);

Song* insertSong( const char* name);

//finds the no of children of the given song node
unsigned NoofChildren(Song* songptr);

void inorderTraversal(Song*, Queue* );

//finds the next smaller name of the given songptr
Song* findSuccessor(Song* );

// --will be reused in avl tree

//takes the root of the tree as input and returns the root of the tree after
//doing necessary changes
Song* insertElement(Song* songptr, const char* name);

//takes the root of the tree as input and returns the root of the tree after
//doing necessary changes
Song* deleteElement(Song* songptr, const char* element);
#endif
