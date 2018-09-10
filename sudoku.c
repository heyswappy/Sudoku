/*
	C PROGRAM TO SOLVE SUDOKU
	AUTHOR: SWAPNIL SAXENA
	COMPUTER SCIENCE AND ENGINEERING
	JAYPEE INSTITUTE OF INFORMATION TECHNOLOGY
*/

#include<stdio.h>
#include<stdlib.h>
#define and &&
#define or ||

int **mainCopy;
int **copyCopy;

void concierge();
void reset();
int checkRow(int r, int n);
int checkCol(int c, int n);
int checkGrid(int r, int c, int n);
void show(int **a);
int sudoku(int a);

void main()
{
	concierge();
	for(int i = 0;i<9;i++)
	{
		for(int j = 0;j<9;j++)
		{
			scanf("%d",mainCopy[i]+j);
		}
	}
	reset();
	show(mainCopy);
	sudoku(0);
	printf("\n\n");
	show(copyCopy);
}

void concierge()
{
	mainCopy = (int **)calloc(sizeof(int *),9);
	copyCopy = (int **)calloc(sizeof(int *),9);
	for(int i =0; i<9;i++)
	{
		mainCopy[i] = (int *)calloc(sizeof(int),9);
		copyCopy[i] = (int *)calloc(sizeof(int),9);
	}
}
void reset()
{
	for(int i = 0;i<9;i++)
	{
		for(int j = 0;j<9;j++)
		{
			copyCopy[i][j] = mainCopy[i][j];
		}
	}
}

int checkRow(int r, int n)
{
	for(int i = 0;i<9;i++)
	{
		if (copyCopy[r][i] == n)
		{return 0;}
	}
	return 1;
}

int checkCol(int c, int n)
{
	for(int i = 0;i<9;i++)
	{
		if (copyCopy[i][c] == n)
		{return 0;}
	}
	return 1;
}

int checkGrid(int a, int b, int n) // row,column
{
	int r = 0;
	int c = 0;
	switch(a)
	{
		case 0:
		case 1:
		case 2: r = 0; break;
		case 3:
		case 4:
		case 5: r = 3; break;
		case 6:
		case 7:
		case 8: r = 6; break;
	}
	switch(b)
	{
		case 0:
		case 1:
		case 2: c = 0; break;
		case 3:
		case 4:
		case 5: c = 3; break;
		case 6:
		case 7:
		case 8: c = 6; break;
	}
	for(int i=r;i<(r+3);i++)
	{
		for(int j=c;j<(c+3);j++)
		{
			if (copyCopy[i][j] == n)
			{return 0;}
		}
	}
	return 1;
}

void show(int **ptr)
{
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			printf("%d ",ptr[i][j]);
		}
		printf("\n");
	}
}

int sudoku(int a)
{
	//printf("\nFUNCTION CALL->%d\n",a);
	/*if(a>70)
	{show(copyCopy);}*/
	int c = a%9;
	int r = a/9;
	int status = 0;
	int i = 0;
	
	if(copyCopy[r][c]!=0)
	{
		//check if board ends with a constant
		if((a+1)==81)
		{
			status = 1;
			return status;
		}
		// already set data
		status = sudoku(a+1);
		return status;
	}
	
	// check possibilites
	for(i = 1; i < 10; i++)
	{
		if((checkRow(r,i))and(checkCol(c,i))and(checkGrid(r,c,i)))
		{
			//the code runs if no duplicacy found
			//printf("POSSIBILITY for r=%d c=%d n=%d\n",r,c,i );
			copyCopy[r][c] = i;
			if((a+1) != 81)
			{
				//printf("HERE %d \n",a+1);
				status = sudoku(a+1);
			}
			else
			{
				//the code runs if the board ends
				//printf("DONE\n");
				status = 1;
				return status;
			}
		}
		else{continue;}
		//if wrong assumption the status is zero hence reset the move
		if(!status)
		{ 
			//printf("WRONG ASSUMPTION %d %d\n",r,c);
			// reset he element
			copyCopy[r][c] = mainCopy[r][c];
			continue;
		}
		else{return status;}
	}
	
	if (i == 10)
	{
		// wrong assumption
		//printf("WRONG ASSUMPTION AFTER FULL LOOP r=%d c=%d\n",r,c);
		status = 0;
		return status;
	}
	return status;
}
