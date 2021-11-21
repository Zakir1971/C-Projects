#define NUM_ROWS 8
#define NUM_COLS 8
#define LEFTBLANK -2
#define DEAD 0
#define BOUNDARY -1
#define LIVE 254u

#define MAX 100
struct Coordinates{
	int x;
	int y;
};
void InitialiseGrid(int grid[NUM_ROWS][NUM_COLS])
{
	int i, j;
	//printf("Define the InitialiseFloor() function\n");
	for(i=0;i<NUM_ROWS;i++)
	{
		for(j=0;j<NUM_COLS;j++)
		{
			grid[i][j]=DEAD;
			if(i==0 || i==NUM_ROWS-1 || j==0 || j==NUM_COLS-1)
				grid[i][j]=BOUNDARY;
			if((i==1 && j>=1 && j<NUM_COLS-1)|| (i==NUM_ROWS-2 && j>=1 && j<NUM_COLS-1)||(i>=1 && i<NUM_ROWS-1 && j==1)||(i>=1 && i<NUM_ROWS-1 && j==NUM_COLS-2))
				grid[i][j]=LEFTBLANK;
				
		}
	}

}
/////////////////
void PrintGrid(int grid[NUM_ROWS][NUM_COLS])
{
	int i, j;
	//printf("Define the PrintFloor() function\n");
	for(i=0;i<NUM_ROWS;i++){
		for(j=0;j<NUM_COLS;j++){
			if(grid[i][j]==BOUNDARY)
				printf("%c",'X');
			else if(grid[i][j]==DEAD)
				printf("%c",' ');
			else if(grid[i][j]==LEFTBLANK)
				printf("%c",' ');
			else if(grid[i][j]==LIVE)
				printf("%c",grid[i][j]);
			if(j==NUM_COLS-1)
				printf("\n");		
		}
	}	
}
void CreateGeneration0(int grid[NUM_ROWS][NUM_COLS])
{
	int i, j;
	for(i=2;i<NUM_ROWS-2;i++){
		for(j=2;j<NUM_COLS-3;j++){
			if(i==2)
				grid[i][i+1]=LIVE;
			if(i==3)
				grid[i][i+1]=LIVE;
			if(i==4)
				grid[i][j]=LIVE;
				
		}
	}
}

struct Coordinates* CoordOfDeadToBecomeAlive(int grid[NUM_ROWS][NUM_COLS])//
{
		int i, j;
		int countLiveAroundDead=0;
		int k=0;
		static struct Coordinates dead[MAX];
		
	for(i=2;i<NUM_ROWS-2;i++){
		for(j=2;j<NUM_COLS-2;j++){
			if(grid[i][j]==DEAD)
			{
				if(grid[i+1][j]==LIVE)
					countLiveAroundDead++;
				if(grid[i][j-1]==LIVE)
					countLiveAroundDead++;
				if(grid[i-1][j]==LIVE)
						countLiveAroundDead++;
				if(grid[i][j+1]==LIVE)
						countLiveAroundDead++;
				if(grid[i-1][j-1]==LIVE)
						countLiveAroundDead++;
				if(grid[i-1][j+1]==LIVE)
						countLiveAroundDead++;
				if(grid[i+1][j-1]==LIVE)
						countLiveAroundDead++;
				if(grid[i+1][j+1]==LIVE)
						countLiveAroundDead++;
					
				if(countLiveAroundDead==3)
				{
					dead[k].y=i;
					dead[k].x=j;
					//printf("\n%d,%d",i,j);
					k++;
				}
				countLiveAroundDead=0;	
				
			}
			
			
		}
}

//for(int b=0;b<k;b++){
	//printf("i=%d,j=%d\n",dead[b].y,dead[b].x);
//}
return &dead;
}
//////////////////////
struct Coordinates* CoordOfAliveToBecomeDead(int grid[NUM_ROWS][NUM_COLS])//
{
		int i, j;
		int countLivesAroundAlive=0;
		int k=0;
		static struct Coordinates live[MAX];
		
	for(i=2;i<NUM_ROWS-2;i++){
		for(j=2;j<NUM_COLS-2;j++){
			if(grid[i][j]==LIVE)
			{
				if(grid[i+1][j]==LIVE)
					countLivesAroundAlive++;
				if(grid[i][j-1]==LIVE)
					countLivesAroundAlive++;
				if(grid[i-1][j]==LIVE)
						countLivesAroundAlive++;
				if(grid[i][j+1]==LIVE)
						countLivesAroundAlive++;
				if(grid[i-1][j-1]==LIVE)
						countLivesAroundAlive++;
				if(grid[i-1][j+1]==LIVE)
						countLivesAroundAlive++;
				if(grid[i+1][j-1]==LIVE)
						countLivesAroundAlive++;
				if(grid[i+1][j+1]==LIVE)
						countLivesAroundAlive++;
					
				if(countLivesAroundAlive>3 || countLivesAroundAlive==1)
				{
					live[k].y=i;
					live[k].x=j;
					//printf("\n%d,%d",i,j);
					k++;
				}
				countLivesAroundAlive=0;	
				
			}
			
			
		}
}
return &live;
}
//////////////////
struct Coordinates* CoordOfAliveToRemainAlive(int grid[NUM_ROWS][NUM_COLS])//
{
		int i, j;
		int countLivesAroundAlive=0;
		int k=0;
		static struct Coordinates live[MAX];
		
	for(i=2;i<NUM_ROWS-2;i++){
		for(j=2;j<NUM_COLS-2;j++){
			if(grid[i][j]==LIVE)
			{
				if(grid[i+1][j]==LIVE)
					countLivesAroundAlive++;
				if(grid[i][j-1]==LIVE)
					countLivesAroundAlive++;
				if(grid[i-1][j]==LIVE)
						countLivesAroundAlive++;
				if(grid[i][j+1]==LIVE)
						countLivesAroundAlive++;
				if(grid[i-1][j-1]==LIVE)
						countLivesAroundAlive++;
				if(grid[i-1][j+1]==LIVE)
						countLivesAroundAlive++;
				if(grid[i+1][j-1]==LIVE)
						countLivesAroundAlive++;
				if(grid[i+1][j+1]==LIVE)
						countLivesAroundAlive++;
					
				if(countLivesAroundAlive==2|| countLivesAroundAlive==3)
				{
					live[k].y=i;
					live[k].x=j;
					//printf("\n%d,%d",i,j);
					k++;
				}
				countLivesAroundAlive=0;	
				
			}
			
			
		}
}
//int len=sizeof(live)/(2*sizeof(int));
//printf("\nlen=%d",len);
return &live;
}
//////////////
void UpdateGrid(int grid[NUM_ROWS][NUM_COLS],struct Coordinates*DeadToLive,struct Coordinates*LiveToDead,struct Coordinates*LiveToLive)
{
	int b;
	int len1=sizeof(DeadToLive)/(sizeof(int));
	int len2=sizeof(LiveToDead)/(sizeof(int));
	int len3=sizeof(LiveToLive)/(sizeof(int));
	for( b=0;b<len3;b++){
		grid[LiveToLive[b].y][LiveToLive[b].x]=LIVE;
	//printf("i=%d,j=%d\n",LiveToDead[b].y,LiveToDead[b].x);
	}
	for( b=0;b<len1;b++){
		grid[DeadToLive[b].y][DeadToLive[b].x]=LIVE;
	
	}
	for( b=0;b<len2;b++){
		grid[LiveToDead[b].y][LiveToDead[b].x]=DEAD;
	
	}
	
}
////////////

int main()
{
	int gen ;
	
	int grid[NUM_ROWS][NUM_COLS];
	
 	struct Coordinates* DeadToLive;
	struct Coordinates*LiveToDead;
	struct Coordinates*LiveToLive;
	/* Print banner */
	printf("............**********************************............\n");
	printf("............*  GAME OF LIFE SIMULATION *............\n");
	printf("............**********************************............\n");
	printf("For requirment details refer to:\n");
	printf("ENGGEN131_C_Coursebook_2021.pdf\n");
	printf("PAGE:101\n");
	/* Initialise the yard grid grid and add containers */
	InitialiseGrid(grid);
	CreateGeneration0(grid);
	printf("Generation:0\n");
	PrintGrid(grid);
	printf("\nEnter number of generations to produce\n");
	scanf("%d", &gen);
for(int i=0;i<gen;i++)
{
	DeadToLive=CoordOfDeadToBecomeAlive(grid);//live
	LiveToDead=CoordOfAliveToBecomeDead(grid);//dead
	LiveToLive=CoordOfAliveToRemainAlive(grid);//live
	UpdateGrid(grid,DeadToLive,LiveToDead,LiveToLive);
	printf("Generation:%d\n",i+1);
	PrintGrid(grid); 
}
  
    
}