#include "../include/avl.h"
#include <math.h>

unsigned calcHeightavl(Song* songptr){
	if(songptr == NULL) return 0;
	else return songptr->height;
}

//checks whether the given songptr is balanced or not
unsigned isBalanced(Song* songptr){
	int diff = calcHeightavl(songptr->left) - calcHeightavl(songptr->right);
	if(abs(diff) > 1) return 0;
	else return 1;
}


unsigned max(unsigned height1, unsigned height2){
	if(height1 >= height2) return height1;
	else return height2;
}

//rotates in anti clockwise sense
Song* leftRotation(Song* node){
	Song* nodeRight = node->right;
    Song* nodeRightLeft = nodeRight->left;
    nodeRight->left = node;
    node->right = nodeRightLeft;
    node->height = 1+max(calcHeightavl(node->left), calcHeightavl(node->right));
    nodeRight->height = 1+max(calcHeightavl(nodeRight->left), calcHeightavl(nodeRight->right));

    return nodeRight;
}

//rotates in clockwise sense
Song* rightRotation(Song* node) {

    Song *nodeLeft = node->left;
    Song *nodeLeftRight = nodeLeft->right;
    nodeLeft->right = node;
    node->left = nodeLeftRight;
    node->height = 1+max(calcHeightavl(node->left), calcHeightavl(node->right));
    nodeLeft->height =1+ max(calcHeightavl(nodeLeft->left), calcHeightavl(nodeLeft->right));

    return nodeLeft;

}

Song* rebalance(Song* songptr,const char* name){
	int diff = calcHeightavl(songptr->left) - calcHeightavl(songptr->right);
	if(isBalanced(songptr)) return songptr;
	else if(diff > 1 && DIFF(name, songptr->left->songName) < 0){
		return rightRotation(songptr);
	}
	else if(diff < -1 && DIFF(name, songptr->right->songName) > 0){
		return leftRotation(songptr);
	}
	else if(diff > 1 && DIFF(name, songptr->left->songName) > 0){
		songptr->left = leftRotation(songptr->left);
		return rightRotation(songptr);
	}
	else if(diff < -1 && DIFF(name, songptr->right->songName) < 0){
		songptr->right = rightRotation(songptr->right);
		return leftRotation(songptr);
	}
	return songptr;
}

Song* insertElementavl(Song* songptr, const char* name){
	if(songptr == NULL){
		return insertSong(name);
	}
	else if(strcmp(name, songptr->songName) < 0 ) songptr->left = insertElementavl(songptr->left, name);
	else if(strcmp(name, songptr->songName) > 0 ) songptr->right = insertElementavl(songptr->right, name);
	else if(strcmp(name, songptr->songName) == 0) {
		printf("Song already exists\n");
		return songptr;
	}
	songptr->height = 1 + max(calcHeightavl(songptr->left), calcHeightavl(songptr->right));
	songptr = rebalance(songptr, name);
	return songptr;
}

Song* deleteElementavl(Song* songptr, const char* name){
	if(songptr == NULL){
		printf("Song: %s is not found \n",songptr->songName);
		return songptr;
	}
	else if(DIFF(name, songptr->songName) < 0) songptr->left = deleteElementavl(songptr->left, name);
	else if(DIFF(name, songptr->songName) > 0) songptr->right = deleteElementavl(songptr->right, name);
	else if(DIFF(name, songptr->songName) == 0){
		Song* temp;
		if(NoofChildren(songptr) == 0){
			//deleting a leaf
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
			songptr->right = deleteElementavl(songptr->right, successor->songName);
		}
	}
	songptr->height =1 + max(calcHeightavl(songptr->left), calcHeightavl(songptr->right));
	int diff = calcHeightavl(songptr->left) - calcHeightavl(songptr->right);
	if(isBalanced(songptr)) return songptr;
    if(diff<=1 && diff>=-1)
    return songptr;
	//right right unbalanced tree
	else if(diff<-1 && calcHeightavl(songptr->right->left)-calcHeightavl(songptr->right->right)<=0) return leftRotation(songptr);
	//left left unbalanced tree
    else if(diff>1 && calcHeightavl(songptr->left->left)-calcHeightavl(songptr->left->right)>=0) return rightRotation(songptr);
	//right left unbalanced tree
    else if(diff<-1 && calcHeightavl(songptr->left->left)-calcHeightavl(songptr->left->right)>0) {
		   songptr->right = rightRotation(songptr->right);
        	return leftRotation(songptr);
	}
	//left right unbalanced tree
	else if(diff>1 && calcHeightavl(songptr->left->left)-calcHeightavl(songptr->left->right)<0) {
		songptr->left = leftRotation(songptr->left);
		return rightRotation(songptr);}
	return songptr;
}
