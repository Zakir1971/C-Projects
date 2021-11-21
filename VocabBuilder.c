#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define DICTIONARY "wordList.txt"
#define MAXWORDS 2000
#define MAXCHAR 100
#define OPTIONS 5
void GetRandomWord(char *w,char *M,int n);
void GetListOfWords(char *M,char (*wl)[],int n,int *);
void DisplayOptions(char *w, char *M,char list[MAXWORDS][MAXCHAR],int Listlength);
int WordGuessed(char *M);
void getNumberOfLines(int *n);

int main(void)
{
	char secretWord[MAXCHAR];
	char secretWordMean[MAXCHAR];
	char list[MAXWORDS][MAXCHAR];
	char guess[MAXCHAR];
	int numberOfLinesInDict,listLength;
	int gameOver = 0;
	srand((unsigned int)time(NULL));
	
	getNumberOfLines(&numberOfLinesInDict);
	
	while (!gameOver) {
		GetRandomWord(secretWord,secretWordMean,numberOfLinesInDict);
		GetListOfWords(secretWordMean,list,numberOfLinesInDict,&listLength);
		DisplayOptions(secretWord, secretWordMean,list,listLength);
		gameOver=WordGuessed(secretWordMean);
	}
	

return 0;
}
////
void GetRandomWord(char *w,char *M,int numOfLines)
{
	FILE *fp;
	int  pos, i;
	fp = fopen(DICTIONARY, "r");
	// Extract characters from file and store in character c
   
	//fseek(fp, 0L, SEEK_SET);
	fscanf(fp, "%s%s", w,M);
	pos = rand() % numOfLines;//pos=0 to numOfLines-1
	for (i = 0; i < pos; i++) {
			fscanf(fp, "%s%s", w,M);
		}
	fscanf(fp, "%s%s", w,M);
	fclose(fp);
}
void DisplayOptions(char *w, char *M, char list[MAXWORDS][MAXCHAR],int Listlength)
{
	int i,j;
	
	for (j = 0; w[j]!='\0'; j++)
	{
		w[j]=w[j]-32;
	}
	printf("The word %s Means:\n", w);
	for (i = 0; i < Listlength; i++)
	{
		printf("%d) %s\n",i+1, list[i]);
	}
	
	
}
void GetListOfWords(char *M,char (*wl)[MAXCHAR],int numOfLines,int *len)
{
	FILE *fp;
	int  pos, i;
	int listLen=0,k=0;
	char word[MAXCHAR],mean[MAXCHAR],temp[MAXCHAR];
	fp = fopen(DICTIONARY, "r");
	// Extract characters from file and store in character c
   
	//fseek(fp, 0L, SEEK_SET);
	fscanf(fp, "%s%s", word,mean);//to skip first line header

	while(fscanf(fp, "%s%s", word,mean)!=EOF)
	{
		if(strcmp(mean,M)==0){
		
			//fscanf(fp, "%s %s", word,mean);
				strcpy(wl[listLen],mean);
				//printf("mar=%s",mean);
				listLen++;
				//k++;
				break;
			}
				
		}
		fseek(fp, 0L, SEEK_SET);
		fscanf(fp, "%s%s", word,mean);
		fscanf(fp, "%s%s", word,mean);
		pos = rand() % numOfLines/4;//pos=0 to numOfLines-1
	for (i = 0; i < pos; i++) {
			fscanf(fp, "%s%s", word,mean);
		}
		fscanf(fp, "%s%s", word,mean);
		while(listLen!=OPTIONS)
		{fscanf(fp, "%s%s", word,mean);
			if(strcmp(mean,M)!=0)
				{
				strcpy(wl[listLen],mean);
				listLen++;	
				}
		}
		//swap meanings string with another randomly
		pos = (rand() % (listLen-1))+1;
		strcpy(temp, wl[0]);
    	strcpy(wl[0], wl[pos]);
    	strcpy(wl[pos], temp);	
	
	*len=listLen;
	fclose(fp);
}
	
void getNumberOfLines(int *n)
{
	FILE *fp;
	int count=0;
	fp = fopen(DICTIONARY, "r");
	// Extract characters from file and store in character c
    for (char c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
	*n = count;
	fclose(fp);
}
int WordGuessed(char *M)
{
	int i;
	int incorrect=1,toContinue = 0;
	char yourOption[MAXCHAR];
	char gamecontinue[10];
	while(incorrect)
	{
			scanf("%s",yourOption);
		if(strcmp(yourOption,M)==0)
		{
			printf("Correct!\n");
			//isCorrect++;
			incorrect=0;
			printf("Do you want to continue?\n Y/N?\n");
			scanf("%s",gamecontinue);
			if (gamecontinue[0]=='y'|| gamecontinue[0]=='Y')
				toContinue++;
			else
				toContinue=0;
				
		}
		else
		{
			printf("Wrong! Try agian.\n");
			incorrect=1;
		}
	}
	
	
	return toContinue == 0;
}