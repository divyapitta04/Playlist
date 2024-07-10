#ifndef _FILE_IO_H
#define _FILE_IO_H

#include <stdio.h>
#include <stdlib.h>
#include "../include/queue.h"
#include "../include/avl.h"
#define MAXLENGTH 50

//takes filename as input and returns the string of songs
const char* readFromFile(const char* filename);

//takes a big string and delim character and splits the string
//and stores each split string in a queue and returns that queue
Queue* splitString(const char* , const char );

//takes the above queue and performs insertion on all elements of the
//queue
Tree* constructTree(Queue*);

//combines the above three functions and returns the bst tree pointer
Tree* BuildLibrary(const char* filename);

#endif
