#include "../include/bst.h"
#include "../include/avl.h"
#include "../include/fileio.h"

Tree* createPlaylist(Tree*);
void playnext(Tree*, Stack*, Queue*);
void playPrevious(Stack*);


int main(){
	Tree* newlibrary = BuildLibrary("songs.txt");
	char answer[3];
	//for deletion
	printf("Do you want to delete song from library y/n? \n");
	scanf("%s",answer);
	if(strcmp(answer,"y") == 0 || strcmp(answer,"Y") == 0){
		char songName[MAXLENGTH];
		printf("Enter -1 to end deletion process\n");
		while(1){
		scanf("%s",songName);
		if(strcmp(songName,"-1") == 0) break;
		deleteElement(newlibrary->root, songName);
		}
	}
	Tree* playlist = createPlaylist(newlibrary);
	//for deletion
	printf("Do you want to delete song from playlist y/n? \n");
	scanf("%s",answer);
	if(strcmp(answer,"y") == 0 || strcmp(answer,"Y") == 0){
		char songName[MAXLENGTH];
		printf("Enter -1 to end deletion process\n");
		while(1){
		scanf("%s",songName);
		if(strcmp(songName, "-1") == 0) break;
		deleteElement(playlist->root, songName);
		}
	}
	Stack* history = createStack();
	Queue* play = createQueue();
	printf("Enter n to play next p k to play previous k and e to end\n");
	char input[MAXLENGTH];
	while(1){
		scanf("%s",input);
		if(DIFF(input, "e") == 0){printf("Bye\n"); break;}
		else if(DIFF(input,"n") == 0) playnext(playlist,history, play);
		else if(DIFF(input,"p") == 0) playPrevious(history);
	}

}

Tree* createPlaylist(Tree* library){
	Tree* playlist = createTree();
	printf("Enter song name and -1 to stop creating playlist\n");
	while(1){
		char songInput[MAXLENGTH];
		scanf("%s",songInput);
		if(DIFF(songInput,"-1") == 0) break;
		Song* songptr = searchElement(library->root, songInput);
		if(songptr == NULL){
			printf("Song is not found in library\n");
			continue;
		}
		printf("Song: %s found and added to playlist\n",songptr->songName);
		playlist->root = insertElementavl(playlist->root, songptr->songName);
	}
	printf("Playlist created\n");
	return playlist;
}

void playnext(Tree* playlist, Stack* history, Queue* play){
	if(play->size == 0) inorderTraversal(playlist->root, play);
	QueueNode* playingSong = dequeue(play);
	printf("Playing :%s\n",playingSong->name);
	//pushes the song into history stack
	push(history, playingSong->name);
}

//enqueues n no of songs from stack into a temp queue and call playnext function
//with that queue
void playPrevious(Stack* history){
	unsigned Number,count = 0;
	Queue* tempQueue = createQueue();
	scanf("%u",&Number);
	while(Number --){
		if(history->size == 0){
			printf("No songs in the history\n");
			break;
		}
		Node* recentSong = pop(history);
		enqueue(tempQueue, recentSong->songName);
		count++;
	}
	while(count--){
		playnext(NULL , history, tempQueue);
	}
}

