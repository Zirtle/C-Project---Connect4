#include <stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX 20

void initBoard(char board[MAX][MAX],int row,int col);
void printBoard(char board[MAX][MAX],int row,int col);
void play(char board[MAX][MAX],int row,int col,int *row_play,int *col_play,char icon);
int check(char board[MAX][MAX],int row,int col,int row_play,int col_play,char icon);
void delay(int ms);

int main()
{
    char board[MAX][MAX];
    int row,col;            //row and col store no of rows and columns
    int col_play,row_play; //row_play and col_play store location of last played piece
    char icon='X';         //player icon
    int n;
flag:
    printf("Enter 1 for default grid size (6x7)\n");
    printf("Enter 2 for custom grid size\n");
    scanf("%d",&n);
    //initialising row and col to default grid size
    if(n==1)
    {
        row=6;
        col=7;
    }
    //taking in user grid size
    else if(n==2)
    {
        printf("\nEnter the grid size (in format of RxC)\n");
        scanf("%dx%d",&row,&col);
        if((row*col<7) || (row<4 && col<4))  //checking if any players victory is possible on given grid
        {
            printf("Grid size too small\n");
            goto flag;
        }
    }
    else
    {
        printf("Invalid Choice\n");
        goto flag;
    }
    system("cls");
    initBoard(board,row,col);   //initializing board
    printBoard(board,row,col);
    int count=0;
    while(1)
    {
        printf("Player %c's turn\n",icon);
        play(board,row,col,&row_play,&col_play,icon);
        system("cls");
        printBoard(board,row,col);
        if(check(board,row,col,row_play,col_play,icon)) //checking if player has won
        {
            printf("\n\nPlayer %c's victory\n",icon);
            break;
        }
        icon=(icon=='X')? 'O':'X';   //changing player
        count++;
        if(count==row*col)    //checking if grid is full
        {
            printf("Draw\n");
            break;
        }
    }
    getchar();
    getchar();
    return 0;
}


//function to initialize board
void initBoard(char board[MAX][MAX],int row,int col)
{
    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
            board[i][j]=' ';
    }
}


//function to display board
void printBoard(char board[MAX][MAX],int row,int col)
{
    int i;
    for(i=0;i<col;i++)
        printf("  %d ",i+1);
    printf("\n");
    for(i=0;i<col;i++)
        printf("|===");
    printf("|\n");
    for(i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
            printf("| %c ",board[i][j]);
        printf("|\n");
        for(int j=0;j<col;j++)
            printf("|---");
        printf("|\n");
    }
}


//function to play each person turn
void play(char board[MAX][MAX],int row,int col,int *row_play,int *col_play,char icon)
{
    int n;
flag:
    while(1)     //choosing column to put piece in
    {
        printf("Choose column to play\n");
        scanf("%d",&n);
        if(n>=1 && n<=col)
            break;
        else
            printf("Invalid choice\n");
    }
    n--;
    *col_play=n;   //noting the column in which player has played
    int i;
    for(i=row-1;i>=0;i--)  //finding lowest empty row
    {
        if(board[i][n]==' ')
        {
            break;
        }
    }
    if(i==-1)//checking if piece was was actually dropped in column
    {
        printf("Column full\n");
        goto flag;
    }
    *row_play=i;   //noting in which row piece was dropped
    for(int j=0;j<i;j++) //loop to provide animation for dropping piece in
    {
        system("cls");
        board[j][n]=icon;
        printBoard(board,row,col);
        board[j][n]=' ';
        delay(200);
    }
    board[i][n]=icon;
}


//function to check for victory
int check(char board[MAX][MAX],int row,int col,int row_play,int col_play,char icon)
{
    int k;
    //checking for horizontal victory
    //in horizontal victory last played piece can be 1st,2nd,3rd,4th in winning combination
    //so we check all 4 possibilities
    for(k=0;k<4;k++)
    {
        int i;
        for(i=k;i>k-4;i--)
        {
            if(board[row_play][col_play+i]!=icon)//checking for other icons
                break;
        }
        if(i==k-4)
            return 1;
    }

    //checking for vertical victory
    //vertical victory is only possible in 1 way
    //where last played piece is highest
    for(k=0;k<4;k++)
    {
        if(board[row_play+k][col_play]!=icon)
            break;
    }
    if(k==+4)
        return 1;

    //checking for right down diagonal victory
    //like horizontal victory diagonal victory is possible in 4 ways
    //so we check all 4 possibilities
    for(k=0;k<4;k++)
    {
        int i;
        for(i=k;i>k-4;i--)
        {
            if(board[row_play+i][col_play+i]!=icon)
                break;
        }
        if(i==k-4)
            return 1;
    }

    //checking for right up diagonal victory
    //like horizontal victory diagonal victory is possible in 4 ways
    //so we check all 4 possibilities
    for(k=0;k<4;k++)
    {
        int i;
        for(i=k;i>k-4;i--)
        {
            if(board[row_play+i][col_play-i]!=icon)
                break;
        }
        if(i==k-4)
            return 1;
    }
    return 0;
}
void delay(int ms)   //function to simulate delay
{
    long pause;
    clock_t now,then;

    pause = ms*(CLOCKS_PER_SEC/1000);  //converting milliseconds to clock cycles
    now = then = clock();
    while( (now-then) < pause )
        now = clock();
}
