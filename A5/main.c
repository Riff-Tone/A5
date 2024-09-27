/*
 * Created on september 25 1:08pm
 * by Diego Gayosso Hernandez on xcode
 *
 *Alright game plan
 *When the program first executes i want it to read the champion.txt file, to get the record of the previous players
 * So i need a function that reads the file, another that sets the players info, and another that orders them correctly
 *
 *then the easy part, get name from player, create struct from them and play the game, count the number of guess till they get it right
 *
 *then we check if we have more than 5 players, and if the user score is less than or equal to the top or more than the bottom,
 * promt them the leader board, this function will start at the head node, and iterate till we get to the last
 * repeat till the user, quits the game, there we rewrite the champion file and put our new scoreboard
 * in formal of score playName
 * in each new line.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define size 10

typedef struct Player {
	 char playerName[size];
	 int score;
	 struct Player *next;
} Player;

Player *head = NULL;// first place!!!

int topScore;
int lowestScore;
int playersInScoreBoard;

void insertPlayer(char Name[size], char Score[size]){
	//creates player node in the heap, then we set Name and parse score, into the struct of node
	Player *node = (Player *)malloc(sizeof(Player));
	if (node != NULL) {
		 printf("Memory allocation did not failed\n");
		 return;
	}
	node->score=atoi(Score);
	
	if(head != NULL){//after the first game we will have players so this will be true most of the time

		return;
	}
	//for first games/empty file we need to set the new player as the lead,
	head = node;
}

void printInfo(void){
	printf("%s, %d", head->playerName, head->score);
}


void readFile(void){
//here we need to open the file, if it does not exist we create it
const char *FILENAME ="Champions.txt";
	FILE* fp = NULL;
	fp = fopen(FILENAME,"r");

	if(fp!=NULL){//the file does exist so we need to read it, its a bit ugly like me but it works i guess
		int a = 0;
		int b = 0;
		char Score[size];
		char Name[size];
		char c;

		while((c=fgetc(fp)) != EOF){
			if(c == '\n'){
				insertPlayer(Name, Score);
				for(int i=0;i<size;i++){
					Score[i] = '\0';
					Name[i] = '\0';
				}
				a=0;
				b=0;
			continue;
			}
			if (isalpha(c)) {
				Name[a] = c;
				a++;
			} else if (isdigit(c)) {
				Score[b] = c;
				b++;
			}
		}
		fclose(fp);
		return;
	}
	fp = fopen(FILENAME,"w");//if the file doesnt exist we create it
}

void clearInputBuffer(void) { //from A4
	 int c;
	 while ((c = getchar()) != '\n' && c != EOF) { }
}

char toQuit(void){ //from A4
	char input;
	printf("Welcome! Press 'q' to quit or any other key to continue: ");
	scanf("%c",&input);
	clearInputBuffer();
	return input;
}

void getNewPlayer(void){
	char newPlayer[size];
	printf("Enter name: ");
	scanf("%10c",newPlayer);
	insertPlayer(newPlayer, 0);
}

int main(int argc, const char * argv[]) {
	// char Game = toQuit();
	readFile();
	getNewPlayer();
	printInfo();
	// while(Game != 'q'){

	// 	Game = toQuit();
	// }
	// printf("thanks for playing\n");
	
	return 0;
}
