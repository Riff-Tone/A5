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
} Player;

Player scoreBoard[5];// first place!!!

int topScore =0;
int lowestScore = -1;
int playersInScoreBoard = 0;

void insertPlayer(Player yur){
	if(playersInScoreBoard != 5 && yur.score < lowestScore){

	}
	if(yur.score > lowestScore){

	}
	scoreBoard[playersInScoreBoard] = yur;
}
void setPlayer(char Name[size], int Score){
	// at this stage im assuming the player has finsihed the game, meaning name and score has already been set by the player.
	
	Player newPlayer;
	strcpy(newPlayer.playerName, Name);
	newPlayer.score = Score;
	insertPlayer(newPlayer);
	
}


void printInfo(void){
	for (int i =0; i<5; i++) {
		printf("%p",&scoreBoard[i]);
	}
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
				setPlayer(Name, atoi(Score));
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
	scanf("%10c",newPlayer); //i need to properly make sure if the name inserted is less than 10char i need it to still read it and save the name
	
	char score[] ={'2','3'}; // replace this with the gae fucntion that returns the num of guesses of the player. so we wont need atoi, since the function will keep track in ints
	
	setPlayer(newPlayer, atoi(score));
	
	for (int i=0; i<size; i++) {
		printf("%c",newPlayer[i]);
	}
	
//	insertPlayer(newPlayer, 0);
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
