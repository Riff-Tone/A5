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
#include <math.h>
#include <time.h>

#define size 10

typedef struct Player {
	 char playerName[size];
	 int score;
} Player;

Player scoreBoard[5];

int playersInScoreBoard = 0;

void initalizeArray(void){
	for(int i =0; i<5;i++){
		scoreBoard[i].score = -1;
	}
}

void updateArray(Player champ){
	int playerScore = champ.score;
	int index = -1;
	
	for(int i=0;i<5;i++){ //finds an index where the champ, belongs
		if(scoreBoard[i].score == -1){ //finds an empty element and sets it to champ, therfore we  dont need to continue.
			scoreBoard[i] = champ;
			return;
		}
		if(scoreBoard[i].score > playerScore){
			index = i;
			break;
		}
	}
	
	for (int i = 4; i > index; i--) { // nice much more compact,instead of 3 for loops, idiot...
		 scoreBoard[i] = scoreBoard[i - 1];
	}
	scoreBoard[index] = champ;
}

void insertPlayer(Player champ){
	//lowest score means the highest guess a player made.
	
	if(playersInScoreBoard==0){scoreBoard[0] = champ; playersInScoreBoard++; ; return;}
	
	int lowestScore = scoreBoard[playersInScoreBoard - 1].score;
	
	if(playersInScoreBoard ==5 && champ.score > lowestScore){return;}
	
	updateArray(champ);
	if(playersInScoreBoard != 5){playersInScoreBoard++;}
	//make writeFile function,
}

void setPlayer(char Name[size], int Score){
	// at this stage im assuming the player has finsihed the game, meaning name and score has already been set by the player.
	
	Player newPlayer;
	strcpy(newPlayer.playerName, Name);
	newPlayer.score = Score;
	insertPlayer(newPlayer);
}


void printBoard(void){
	for (int i =0; i<playersInScoreBoard; i++) {
		int guess = scoreBoard[i].score;
		if(guess == 1){
			printf("%d. %s with %d guess\n",i+1,scoreBoard[i].playerName, guess);
		}else{
			printf("%d. %s with %d guesses\n",i+1,scoreBoard[i].playerName, guess);
		}
	}
}


void readFile(void) {
	 // Define the file path
	 const char *FILENAME = "/Users/riff/Documents/cse240/A5/Champions.txt";
	 FILE* fp = fopen(FILENAME, "r");

	 if (fp != NULL) {  // If the file exists
		  char Name[size];
		  int Score;

		  while (fscanf(fp, "%d %s", &Score, Name) != EOF) {
				setPlayer(Name, Score);
		  }

		  fclose(fp);
	 } else {  // If the file doesn't exist, create it
		  fp = fopen(FILENAME, "w");
		  fclose(fp);
	 }
}

void writeFile(void) {
	 const char *FILENAME = "/Users/riff/Documents/cse240/A5/Champions.txt";
	 FILE* fp = fopen(FILENAME, "w");

	 //write the score to the file
	 for (int i = 0; i < 5; i++) {
		  // Checks to see if the score is valid (not -1 meaning uninitialized)
		  if (scoreBoard[i].score != -1) {
				fprintf(fp, "%d %s\n", scoreBoard[i].score, scoreBoard[i].playerName);
		  }
	 }

	 fclose(fp);
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

int guessScore(void){
	srand((unsigned int)time(0)); //thank you stack overflow post from 10 years ago
	int dumbassCounter = 0;
	char w = 'w';
	int randomNum =  rand() % (91) + 10;
	float numToGuess = sqrt(randomNum);
	int guess;
	
	while(w =='w'){
		printf("%fis the square root of what number?Guess a value between 10 and 100:",numToGuess);
		scanf("%d",&guess);
		clearInputBuffer();
		if(guess == randomNum){
			printf("Hell yeah!!!\n");
			dumbassCounter++;
			if(dumbassCounter == 1){
				printf("You made %d guess\n", dumbassCounter);
			}else{
				printf("You made %d guesses\n", dumbassCounter);
			}
			break;
		}
		if(guess > randomNum){
			printf("Too high, guess again: \n");
		}
		if(guess < randomNum){
			printf("Too low, guess again: \n");
		}
		dumbassCounter++;
	}
	return dumbassCounter;
}


void getNewPlayer(void){
	char newPlayer[size];
	printf("Please enter your name to start: ");
	scanf("%9s",newPlayer); //i need to properly make sure if the name inserted is less than 10char i need it to still read it and save the name
	int score = guessScore();
	
	setPlayer(newPlayer, score);
}

int main(int argc, const char * argv[]) {
	char Game = toQuit();
		initalizeArray();
		readFile();
	while(Game != 'q'){
		 getNewPlayer();
		 printf("Here are the current leaders: \n");
		 printBoard();
	 	Game = toQuit();
	 }
	writeFile();
	 printf("thanks for playing\n");
	return 0;
}
