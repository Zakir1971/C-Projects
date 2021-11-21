#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define DICTIONARY "words.txt"
void GetRandomWord(char *w);
void InitialiseGuess(char *w, int n);
void ProcessOneGuess(char *w, char *g);
int WordGuessed(char *g);

int main(void)
{
	char secretWord[100];
	char guess[100];
	int gameOver = 0;
	srand((unsigned int)time(NULL));
	GetRandomWord(secretWord);
	InitialiseGuess(guess, (int)strlen(secretWord));
	while (!gameOver) {
		ProcessOneGuess(secretWord, guess);
		gameOver = WordGuessed(guess);
	}
	printf("\nWell done - the word was: %s\n", secretWord);
return 0;
}
////////////////////
void GetRandomWord(char *w)
{
	FILE *fp;
	int numWords, pos, i;
	fp = fopen(DICTIONARY, "r");
	fscanf(fp, "%d", &numWords);
	pos = rand() % numWords;
	for (i = 0; i < pos; i++) {
		fscanf(fp, "%s", w);
	}
	fscanf(fp, "%s", w);
}
void InitialiseGuess(char *w, int n)
{
	int i;
	for (i = 0; i < n; i++)
	w[i] = '_';
	w[n] = '\0';
}
void ProcessOneGuess(char *w, char *g)
{
	int i;
	char input[10];
	for (i = 0; g[i] != '\0'; i++) {
		printf("%c ", g[i]);
		}
	printf("\nEnter guess: ");
	scanf("%s", input);
	for (i = 0; g[i] != '\0'; i++) {
		if (w[i] == input[0])
			g[i] = input[0];
		}
}
int WordGuessed(char *g)
{
	int i;
	int countBlanks = 0;
	for (i = 0; g[i] != '\0'; i++) {
		if (g[i] == '_')
			countBlanks++;
		}
	return countBlanks == 0;
}