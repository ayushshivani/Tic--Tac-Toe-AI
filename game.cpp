#include <bits/stdc++.h>
#include <stdlib.h>

using namespace std;

struct move{
	int row,col;
};

char board[3][3];
int p1=0,p2=0;
char player1='X',player2 = 'O';



void make_board(void)
{
	system("clear");
	for (int i = 0; i <3; ++i)
	{
		for (int j = 0; j <3; ++j)
		{
			printf("%c ",board[i][j] );
		}
		printf("\n");
	}
}

int check_com(int x)
{
	for (int i = 0; i < 3; ++i)
	{
		if (board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][0]!='_')
		{
			if (board[i][1] == player1)
			{
				if (x==1) p1 =1;
				
				return 10;		
			}
			else if (board[i][1]==player2)
			{
				if (x==1)p2 =1;
				
				return -10;	
			}
		}
	}

	//checking vertically
	for (int i = 0; i < 3; ++i)

	{
		
		if (board[0][i]==board[1][i] && board[0][i]==board[2][i] && board[0][i]!='_')
		{
			if (board[0][i] == player1)
			{
				if (x==1)p1 =1;
				// printf("Player 1 wins\n");
				return 10;		
			}
			else if (board[0][i]==player2)
			{
				if (x==1)p2 =1;
				
				return -10;	
			}
		}
	}

	//checking diagonally
	if (board[0][0]==board[1][1] && board[0][0]==board[2][2] && board[1][1]!='_')
	{
		if (board[0][0] == player1)
		{
			if (x==1)p1 =1;
			
			return 10;		
		}
		else if (board[0][0]==player2)
		{
			if (x==1)p2 =1;
			// printf("Player 2 wins\n");
			return -10;	
		}
	}
	if (board[0][2]==board[2][0] && board[0][2]==board[1][1] && board[1][1]!='_')
	{
		if (board[1][1] == player1)
		{
			if (x==1)p1 =1;
			// printf("Player 1 wins\n");
			return 10;		
		}
		else if (board[1][1]==player2)
		{
			if (x==1)p2 =1;
			// printf("Player 2 wins\n");
			return -10;	
		}
	}
}

int board_full()
{
	for (int i = 0; i <3; ++i)
	{
		for (int j = 0; j <3; ++j)
		{
			if (board[i][j]=='_')
			{
				return 0;
			}
		}
	}
	return 1;
}

int check_input(int row,int col)
{
	if (board[row][col]=='_')
	{
		return 1;
	}
	return 0;
}

void take_input(int row,int col,char c)
{
	board[row][col]=c;
	return ;
}

int minimax(int d,bool isMax)
{
	// printf("%d\n",isMax );
	int score = (check_com(0));
	if (score == 10 )
	{
		return score-d;
	}
	if (score == -10 )
	{
		return score+d;
	}
	
	if (isMax)
	{
		int best = 1000;
		for (int i = 0; i < 3; ++i)
		{
			for (int j= 0; j < 3; ++j)
			{
				if (board[i][j] == '_')
				{
					board[i][j] = player2;
					best = max(best,minimax(d+1,!isMax));
					board[i][j] = '_';
				}
			}
		}
		return best-d ; 
	}
	else
	{
		int best = 1000;
		for (int i = 0; i < 3; ++i)
		{
			for (int j= 0; j < 3; ++j)
			{
				if (board[i][j] == '_')
				{
					board[i][j] = player1;
					best = min(best,minimax(d+1,!isMax));
					board[i][j] = '_';
				}
			}
		}
		return best+d;
	}
}


int optimal_move()
{
	int val = -1000;
	int r = -1,c=-1;
	int val2;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			if (board[i][j]=='_')
			{
				board[i][j]=player2;
				val2 = minimax(0,0);
				board[i][j]= '_';
				if (val2>val)
				{
					r = i;
					c = j;
					val = val2;
				}
			}
		}
	}
	board[r][c] = player2;
}

int main()
{
	ios_base::sync_with_stdio(false);
	int i=0,row=0,col=0;
	int c=0;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			board[i][j]='_';
			printf("%c  ", board[i][j]);
		}
		printf("\n");
	}
	for (int j = 0; j < 9 ; ++j)
	{
		make_board();
		if (i%2==0)
		{
			printf("Player 1\n");
			scanf("%d %d",&row,&col);
			if (check_input(row-1,col-1))
			{
				i++;
				take_input(row-1,col-1,player1);
			}
		}
		else
		{	
			optimal_move();
			i++;
		}
		
		check_com(1);
		if (board_full())
		{
			printf("Draw\n");
			return 0;
		}
		if (p1==1)
		{
			printf("You win\n");
			return 0;
		}
		else if (p2==1)
		{
			printf("You Lose\n");
			return 0;
		}	
	}
	return 0;
}