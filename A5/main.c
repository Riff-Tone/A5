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
	
	Player updatedArray[5];
	//fills the updated array
	for(int i = 0;i<index;i++){
		updatedArray[i] = scoreBoard[i];
	}
	
	updatedArray[index] = champ;
	
	for (int i = index; i<4; i++) {
		updatedArray[i+1] = scoreBoard[i];
	}
	
	//sets scoreboard to the updated array
	for (int i =0; i<5; i++) {
		scoreBoard[i] = updatedArray[i];
	}
}

void insertPlayer(Player champ){
	//lowest score means the highest guess a player made.
	int lowestScore = scoreBoard[playersInScoreBoard].score;
	
	if(playersInScoreBoard==0){scoreBoard[0] = champ;}
	
	if(playersInScoreBoard ==5 && champ.score > lowestScore){return;}
	
	updateArray(champ);
	playersInScoreBoard++;
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
		printf("%s\n",scoreBoard[i].playerName);
	}
}


void readFile(void){
//here we need to open the file, if it does not exist we create it
const char *FILENAME ="/Users/riff/Documents/cse240/A5/Champions.txt";
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
	int dumbassCounter = 0;
	char w = 'w';
	int randomNum =  rand() % (89) + 10;
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
			dumbassCounter++;
		}
		if(guess < randomNum){
			printf("Too low, guess again: \n");
			dumbassCounter++;
		}
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
	initalizeArray();
	readFile();
	 char Game = toQuit();
//	readFile();
//	getNewPlayer();
//	printInfo();
	 while(Game != 'q'){
		 getNewPlayer();
		 printf("Here are the current leaders: \n");
		 printBoard();
	 	Game = toQuit();
	 }
	 printf("thanks for playing\n");
	
	return 0;
}
