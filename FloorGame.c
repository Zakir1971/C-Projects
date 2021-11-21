#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define NUM_ROWS 8
#define NUM_COLS 8

#define VACANT 0
#define BOUNDARY -1
#define ENTRY -2
#define EXIT -3

#define FIRSTCONTAINER 'A'

/***********************************************************/
/***********************************************************/
/******* ADD THE REQUIRED FUNCTIONS BELOW THIS POINT *******/
/***********************************************************/
/***********************************************************/

/*
-----------------------------Helper funtions below--------------
	The helper function FindLargestValue() is called from the Function AddContainer() and is 
used to find largest existing value in terms of ASCII code, representing character like A, B, C etc
for a container INSIDE the grid. The found value is incremented by 1 to name new container to 
be added later by the command in the calling function.
*/
int FindLargestValue(int floor[NUM_ROWS][NUM_COLS])
{
	int largesttSoFar = floor[1][1];
	int i;

	for (i = 1; i < NUM_ROWS-1; i++) {
		for(int j=1;j<NUM_COLS-1;j++){
			if (floor[i][j] > largesttSoFar) {
			largesttSoFar = floor[i][j];
			}
		}
	}
return largesttSoFar;
}
/*
The helper function FindColPosition() is called from the Function AddContainer() and is 
used to find jth coordinate in (i,j) using 'position' parameter passed. Using this jth value we can 
find coresponding ith coordinate in the calling function. This (i,j) represents left-most or top-most location of 
a container
*/
int FindColPosition(int floor[NUM_ROWS][NUM_COLS], int position)
{
	int j,posCoordinateJ;
	for(j=1;j<NUM_COLS-1;j++)
	{

		if((position-j)%NUM_COLS==0)
		{
			posCoordinateJ=j;
		}
	}
	return posCoordinateJ;
}
/*
The helper function IfCellsEmpty() is called from the Function AddContainer() and is 
used to check and ensure the availabilty of cells at the specified location for insertion
of new container cells. If all the desired consecutive positions are VACANT then insertion
is possible otherwise NOT. IfCellsEmpty() returns -1 in case any of the specified locations is NOT VACANT,
otherwise it returns 1 if all the required locations are VACANT
*/
int IfCellsEmpty(int floor[NUM_ROWS][NUM_COLS], int size,int coordinateI,int CoordinateJ, int direction)
{
	int length;
	int isVacant=-1;
	
		if (direction==0)//horizontal
		{
			for(length=CoordinateJ;length<CoordinateJ+size;length++)
			{
				if (floor[coordinateI][length]!=VACANT)
					return -1;
				else
				{
					isVacant=1;
				}
				
			}
		}
		else if (direction==1)
		{
			for(length=coordinateI;length<coordinateI+size;length++)
			{
				if (floor[length][CoordinateJ]!=VACANT)
					return -1;
				else
				{
					isVacant=1;
				}		
			}
		}
	return isVacant;
}
/*
The helper function SearchFirstOccuranceContainer() is called from the Function LocateContainer() and is 
used to search for first occurance of move(Letter/Container) inside grid, if container is found store its
left-most or upper-most location in the pointer variables *rowStart and *colStart.
*/
int SearchFirstOccuranceContainer(int floor[NUM_ROWS][NUM_COLS], char move, int* rowStart, int* colStart){
	int i,j;
				
	for (i = 1; i < NUM_ROWS-1; i++) 
	{
		for(j=1;j<NUM_COLS-1;j++)
		{
			
				if (floor[i][j] ==move)
				{
					*rowStart=i;
					*colStart=j;
					return 1;
				}
				
		
		}
	}
	return -1;	
}
/*
The helper function HorizontalMove() is called from the Function MoveContainer() and is 
used to move the container horizontally(left or right) depending on direction specified by the parameter 
leftRight. If leftRight=-1, container will move to the decreasing x-values, which means to the left, 
otherwise if leftRight=1 container will move to the increasing x-values, which means to the right.
For movement to take place, values are swapped until the container hits non-VACANT cell. Also this function
returns the parameter 'Result' specifying what type of cell it is, in its neighbourhood
*/
int HorizontalMove(int floor[NUM_ROWS][NUM_COLS], int r0, int c, int length,  int leftRight){
	int temp,result,k=0;
		while(floor[r0][c+leftRight*(k+1)]==VACANT)//while space is available on left or right of container
		{
			for(int i=0;i<length;i++)
			{
				//swap a vacant position with a container
				temp=floor[r0][c+leftRight*(k+1-i)];
				floor[r0][c+leftRight*(k+1-i)]=floor[r0][c+leftRight*(k-i)];
				floor[r0][c+leftRight*(k-i)]=temp;
			}
				
			k++;
		}
		// check container value if in contact with non-vacant cells including boundary cells
		if(floor[r0][c+leftRight*(k+1)]==ENTRY)
			result=1;
		else if(floor[r0][c+leftRight*(k+1)]==EXIT)
			result=2;
		else 
			result=0;
return result;
}
/*
The helper function VerticalMove() is called from the Function MoveContainer() and is 
used to move the container vetically(up or down) depending on direction specified by parameter 
upDown. If upDown=-1, container will move to the decreasing y-values, which means to upwards, 
otherwise if upDown=1, container will move to the increasing y-values, which means to downwards.
For movement to take place, values are swapped until the container hits non-VACANT cell. Also this function
returns the parameter 'Result' specifying what type of cell it is in its neighbourhood
*/
int VerticalMove(int floor[NUM_ROWS][NUM_COLS], int r, int c0, int length,  int upDown){
	int i,temp,result,k=0;
		while(floor[r+upDown*(k+1)][c0]==VACANT)
		{
			for(i=0;i<length;i++)
			{
				temp=floor[r+upDown*(k+1-i)][c0];
				floor[r+upDown*(k+1-i)][c0]=floor[r+upDown*(k-i)][c0];
				floor[r+upDown*(k-i)][c0]=temp;
			}
				
			k++;
		}
		
		if(floor[r+upDown*(k+1)][c0]==ENTRY)
			result=1;
		else if(floor[r+upDown*(k+1)][c0]==EXIT)
			result=2;
		else 
			result=0;
return result;
}

/*
-----------------Calling functions below---------------------
All the functions other than helper functions are as under.
These functions perform functionality as per requirement of project. The functionality 
of these functions is described in the requirment document so they need no comments. 
*/
/* Function to fill the array 'floor' with various constant values like BOUNDARY, ENTRY, EXIT etc 
depending upon the parameter passed as per requirment given in the document */
void InitialiseFloor(int floor[NUM_ROWS][NUM_COLS], char entryboundary, int index)
{
	int i, j;
	//printf("Define the InitialiseFloor() function\n");
	for(i=0;i<NUM_ROWS;i++)
	{
		for(j=0;j<NUM_COLS;j++)
		{
			floor[i][j]=VACANT;
			if(i==0 || i==NUM_ROWS-1 || j==0 || j==NUM_COLS-1)
				floor[i][j]=BOUNDARY;
				
		}
	}
	if(entryboundary=='L')
	{
		floor[index][0]=ENTRY;
		floor[index][NUM_COLS-1]=EXIT;
	}
	if(entryboundary=='R')
	{	
		floor[index][NUM_COLS-1]=ENTRY;
		floor[index][0]=EXIT;	
	}
	if(entryboundary=='T')
	{	
		floor[0][index]=ENTRY;
		floor[NUM_ROWS-1][index]=EXIT;	
	}
	if(entryboundary=='B')
	{	
		floor[0][index]=EXIT;
		floor[NUM_ROWS-1][index]=ENTRY;	
	}
}
/*
Function to print floor pattern on console using the info stored in array 'floor' 
*/
void PrintFloor(int floor[NUM_ROWS][NUM_COLS])
{
	int i, j;
	//printf("Define the PrintFloor() function\n");
	for(i=0;i<NUM_ROWS;i++){
		for(j=0;j<NUM_COLS;j++){
			if(floor[i][j]==BOUNDARY)
				printf("%c",'@');
			else if(floor[i][j]==ENTRY)
				printf("%c",'U');
			else if(floor[i][j]==EXIT)
				printf("%c",'X');
			else if(floor[i][j]==VACANT)
				printf("%c",' ');
			else
				printf("%c",floor[i][j]);
			if(j==NUM_COLS-1)
				printf("\n");		
		}
}
}
/*
Funtion to return total free area avaiable inside grid where containers may be added.
area of single cell is cellArea=length*width. This area is summed in a loop every time if found free or VACANT
*/
double FloorAreaAvailable(int floor[NUM_ROWS][NUM_COLS], double length, double width)
{
	double free = 0.0;

	//calculate the area of each grid cell
	double cellArea;
		cellArea=length*width;
	for(int i=1;i<NUM_ROWS-1;i++)
	{
		for(int j=1;j<NUM_COLS-1;j++)
		{
			if(floor[i][j]==VACANT)
				free=free+cellArea;
				
		}
	}	
return free;
}

void AddContainer(int floor[NUM_ROWS][NUM_COLS], int position, int size, int direction)
{
	int length,k;
	int largestValue;
	int I,J;
	
	J=FindColPosition(floor,position);
	I=(position-J)/NUM_COLS;		
	largestValue=FindLargestValue(floor);
		
	if(largestValue==0)
		largestValue=FIRSTCONTAINER;
	else
		largestValue=largestValue+1;
	if(direction==0)//if horizontal direction
	{
		length=J+size;
		if(IfCellsEmpty(floor, size,I,J, direction)==1)
		{
			for(k=J;k<length;k++)
				floor[I][k]=largestValue;
		}
	}
	else if (direction==1)
	{
		length=I+size;
		if(IfCellsEmpty(floor, size,I,J, direction)==1)
		{
			for(k=I;k<length;k++)
				floor[k][J]=largestValue;
		}
				
	}		
	
}


int LocateContainer(int floor[NUM_ROWS][NUM_COLS], char move, int* rowStart, int* colStart, int* rowEnd, int* colEnd)
{
	int i, j;	
	int isBlocked=0,foundContainer;
	
	////search for first occurance of move(a letter representing container), 
	//if found store the location in the pointers variables *rowStart and *colStart
	foundContainer=SearchFirstOccuranceContainer(floor, move, rowStart, colStart);
	///if found move on searching remaining occurances of move until last occurance and then store the location of move itne pointers variables
	if (foundContainer==1)
	{
	
		for (i = 1; i < NUM_ROWS-1; i++) 
		{
			for(j=1;j<NUM_COLS-1;j++)
			{
				if (floor[i][j] ==move)
				{
				*rowEnd=i;
				*colEnd=j;	
				}
			}
		}
		if(*colEnd-*colStart!=0 && (floor[*rowStart][*colStart-1]==VACANT || floor[*rowStart][*colEnd+1]==VACANT))
			isBlocked=1;//NOT blocked
		else if(*rowEnd-*rowStart!=0 && (floor[*rowStart-1][*colStart]==VACANT || floor[*rowEnd+1][*colStart]==VACANT))
			isBlocked=1;
	}
	return isBlocked;

}

int MoveContainer(int floor[NUM_ROWS][NUM_COLS], int r0, int c0, int r1, int c1, int isBlocked)
{
	int direction;
	int leftRight,upDown,length, result;
	if(r1-r0==0)//if x-coordinate does not change, i,e container lies in a row
		direction=0;//horizontal
	else
		direction=1;//vertical
	
	if(direction==0 && isBlocked==1)//container lying horizontal and is movable
	{
		length=c1-c0+1;
		if(floor[r0][c0-1]==VACANT)//left-side vacant
		{//move left
			leftRight=-1;//move left
			result=HorizontalMove(floor, r0, c0, length,  leftRight);	
		}
		else////right-side vacant
		{
			leftRight=1;//move right
			result=HorizontalMove(floor, r0, c1,length,  leftRight);
		}
	}
	if(direction==1 && isBlocked==1)//container lying vertical and is movable
	{
		length=r1-r0+1;
		if(floor[r0-1][c0]==VACANT)//up vacant
		{
			upDown=-1;//move up
			result=VerticalMove(floor, r0, c0, length,  upDown);	
		}
		else//move down
		{
			upDown=1;
			result=VerticalMove(floor, r1, c0, length,  upDown);
		}
	}
	if(direction==0 && isBlocked==0)// container lying horizontal and is immovable/stuck
	{
		if(floor[r0][c0-1]==ENTRY || floor[r0][c1+1]==ENTRY)
			result=1;
		else if(floor[r0][c0-1]==EXIT || floor[r0][c1+1]==EXIT)
			result=2;
		else 
			result=-1;
	}
	if(direction==1 && isBlocked==0)//container lying vertical and is immovable/stuck
	{
		if(floor[r0-1][c0]==ENTRY || floor[r1+1][c0]==ENTRY)
			result=1;
		else if(floor[r0-1][c0]==EXIT || floor[r1+1][c0]==EXIT)
			result=2;
		else 
			result=-1;
	}
return result;
} 



/***********************************************************/
/***********************************************************/
/********* DO NOT MODIFY ANY CODE BELOW THIS POINT *********/
/***********************************************************/
/***********************************************************/

/* Function to obtain capital letter as input */
char GetMove(void)
{
	char move;
	printf("\nMove container: ");
	scanf("%c", &move);
	// Ignore non-capital letter inputs
	while ((move < 'A') || (move > 'Z')) {
		scanf("%c", &move);
	}
	return move;
}

/* The main Container Yard simulation */
int main(void)
{
	int gameOver = 0;
	int isBlocked = 0;
	int floor[NUM_ROWS][NUM_COLS];
	int rowStart, colStart, rowEnd, colEnd;
	char input;

	/* Print banner */
	printf("............**********************************............\n");
	printf("............* CONTAINER YARD GAME SIMULATION *............\n");
	printf("............**********************************............\n");
	
	/* Initialise the yard floor grid and add containers */
	InitialiseFloor(floor, 'R', 3);
	AddContainer(floor, 28, 2, 0);
	AddContainer(floor, 11, 3, 1);
	AddContainer(floor, 41, 2, 1);
	AddContainer(floor, 42, 2, 1);
	AddContainer(floor, 42, 2, 1);
	AddContainer(floor, 34, 2, 0);
	AddContainer(floor, 36, 3, 1);
	AddContainer(floor, 37, 2, 1);
	AddContainer(floor, 53, 2, 0);
	AddContainer(floor, 30, 3, 1);

	/* Print status */
	printf("ENGGEN131 2021 - C Project\nContainer Yard!  The containers are rushing in!\n");
	printf("In fact, %.2f sq ft of the yard floor is available for containers!\n\n", FloorAreaAvailable(floor, 20.5, 10.3));

	/* Main simulation loop */
	while (gameOver != 2) {
		PrintFloor(floor);
		input = GetMove();
		isBlocked = LocateContainer(floor, input, &rowStart, &colStart, &rowEnd, &colEnd);
		gameOver = MoveContainer(floor, rowStart, colStart, rowEnd, colEnd, isBlocked);
	}

	/* A container is ready to exit - the simulation is over */
	PrintFloor(floor);
	printf("\nCongratulations, you've succeeded!");

	return 0;
}
