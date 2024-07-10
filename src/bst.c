#include "../include/bst.h"
#include <string.h>

Tree* createTree(){
	Tree* newtree = (Tree*)malloc(sizeof(Tree));
	if(newtree == NULL){
		printf("Error in creating a tree\n"); EXIT_FAILURE;
	}
	newtree->root = NULL;
	return newtree;
}

Song* searchElement(Song* nodeptr, const char* name){
	Song* songptr = nodeptr;
	if(songptr == NULL){
		//printf("No element found in the tree\n");
		return NULL;
	}
	else{
		if(strcmp(name, songptr->songName) == 0) return songptr;
		else if(strcmp(name, songptr->songName) < 0) return searchElement(songptr->left,name);
		else return searchElement(songptr->right,name);
	}
}

unsigned calcHeight(Song* songptr){
	if(songptr == NULL) return 0;
	else return songptr->height;
}

Song* insertSong(const char* name){
	Song* newsong = (Song*)malloc(sizeof(Song));
	strcpy(newsong->songName, name);
	newsong->left = NULL;
	newsong->right = NULL;
	newsong->height = 1;
	return newsong;
}

Song* insertElement(Song* songptr, const char* name){
	//if has no root
	if(songptr == NULL) return insertSong(name);
	else if(DIFF(name,songptr->songName) < 0) songptr->left =  insertElement(songptr->left, name);
	else if(DIFF(name,songptr->songName) > 0) songptr->right =  insertElement(songptr->right, name);
	else if(DIFF(name,songptr->songName) == 0) {
		printf("Song already exists\n");
		return songptr;
	}
	return songptr;
}

Song* findSuccessor(Song* songptr){
	Song* successor;
	songptr = songptr->right;
	if(songptr != NULL){
		//go to the right node and move on to left until you find no left node
		while(1){
			if(songptr->left == NULL){successor = songptr; break;}
			songptr = songptr->left;
		}
	}
	//if there is no right child to the given node
	else{
		successor = songptr->parent;
		while(1){
			if(DIFF(successor->songName, songptr->songName) > 0) break;
			successor = successor->parent;
		}
	}
	return successor;
}

unsigned NoofChildren(Song* songptr){
	if((songptr->left == NULL) && (songptr->right == NULL)) return 0;
	else if(songptr->left == NULL ) return RIGHT;// has only right child
	else if(songptr->right == NULL) return LEFT;// has only left child
	else return 2;
}

Song* deleteElement(Song* songptr, const char* name){
	if(songptr == NULL){
		printf("Song: %s is not found \n",songptr->songName);
		return songptr;
	}
	else if(DIFF(name, songptr->songName) < 0) songptr->left = deleteElement(songptr->left, name);
	else if(DIFF(name, songptr->songName) > 0) songptr->right = deleteElement(songptr->right, name);
	else if(DIFF(name, songptr->songName) == 0){
		Song* temp;
		if(NoofChildren(songptr) == 0){
			temp = songptr; songptr = NULL;
			free(temp);
			return songptr;
		}
		else if(NoofChildren(songptr) == RIGHT || NoofChildren(songptr) == LEFT){
			//no left child
			if(NoofChildren(songptr) == RIGHT) temp = songptr->right;
			else temp = songptr->left;
			*songptr = *temp;
			free(temp);
		}
		else{
			//has two children
			Song* successor = findSuccessor(songptr);
			strcpy(songptr->songName, successor->songName);
			songptr->right = deleteElement(songptr->right, successor->songName);
		}
	}
	return songptr;
}



void inorderTraversal(Song* songptr,Queue* inorderQueue){
	if(songptr == NULL) return;
	inorderTraversal(songptr->left, inorderQueue);
	enqueue(inorderQueue, songptr->songName);
	inorderTraversal(songptr->right, inorderQueue);
}
