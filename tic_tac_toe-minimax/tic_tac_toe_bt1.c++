#include<bits/stdc++.h>
using namespace std;

#define computer 1
#define human 2
#define side 3
#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'
// int minimax(char board[][side], int depth, bool isAi);

void showBoard(char board[side][side])
{
    printf("\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("\t\t\t---------------\n");
    printf("\t\t\t %c | %c | %c  \n", board[1][0], board[1][1], board[1][2]);
    printf("\t\t\t---------------\n");
    printf("\t\t\t %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);
}

void showInstructions()
{
    printf("\nChoose a cell number from 1 to 9 as shown below & play: \n\n");

    printf("\t\t\t 1 | 2 | 3 \n");
    printf("\t\t\t-----------\n");
    printf("\t\t\t 4 | 5 | 6 \n");
    printf("\t\t\t-----------\n");
    printf("\t\t\t 7 | 8 | 9 \n\n");
}

void initialise(char board[side][side])
{
    for (int i = 0; i < side; i++)
    {
        for (int j = 0; j < side; j++)
            board[i][j] = '*';
    }
}

void declareWinner(int whoseTurn)
{
    if (whoseTurn == computer)
        printf("Computer has won.\n");
    else
        printf("HUMAN has won.\n");
}

bool rowCheck(char board[][side])
{
    for (int i = 0; i < side; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '*')
            return true;
    }
    return false;
}
bool columnCheck(char board[][side])
{
    for (int i = 0; i < side; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '*')
            return true;
    }
    return false;
}
bool diagonalCheck(char board[][side])
{
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '*')
        return true;
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '*')
        return true;

    return false;
}

bool gameOver(char board[][side])
{
    return (rowCheck(board) || columnCheck(board) || diagonalCheck(board));
}

int minimax(char board[][side], int depth, bool isAi)
{
    int s = 0;
    int bs = 0;
    // int draw=0;
    

  if(gameOver(board) != false)
    {
        if(isAi == true)
            return (-10);
        else if(isAi == false)
            return (10);
    }
    else 
    { 

        if(depth < 9)
        {
            if(isAi == true)
            {
                bs = -999;
                for(int i = 0; i < side; i++)
                {
                    for(int j = 0; j < side; j++)
                    {
                        if(board[i][j] == '*')
                        {
                            board[i][j] = COMPUTERMOVE;
                            s = minimax(board, depth + 1, false);
                            board[i][j] = '*';
                            if(s > bs)
                                bs = s;
                        }
                    }
                }
                return (bs);
            }
            // human chance
            else 
            {
                bs = 999;
                for(int i = 0; i < side; i++)
                {
                    for(int j = 0; j < side; j++)
                    {
                        if(board[i][j] == '*')
                        { board[i][j] = HUMANMOVE;
                            s = minimax(board, depth + 1, true);
                            board[i][j] = '*';
                            if(s < bs)
                                bs = s;    
                        }
                    }
                }
                return bs;
            }
        } 
        else
        return (0);  
    }
   return (0); 
}

int bestMove(char board[][side], int moveIndex)
{
    int x = -1, y = -1;
    int score = 0, bestscore = -999;
    for (int i = 0; i < side; i++)
    {
        for (int j = 0; j < side; j++)
        {
            if (board[i][j] == '*')
            {
                board[i][j] = COMPUTERMOVE;
                score = minimax(board, moveIndex + 1, false); // x=10,o=-10,draw=0
                board[i][j] = '*';
                if (score > bestscore)
                {
                    bestscore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return (x * side + y);
}
// to play tic tac toe
void playTTT(int whoseTurn)
{
    char board[side][side];
    int moveIndex = 0, x = 0, y = 0;

    initialise(board);//yha
    showInstructions();
    while (gameOver(board) == false && moveIndex != side * side)
    {
        int n;
        if (whoseTurn == computer)
        {
            n = bestMove(board, moveIndex);
            x = n / side;
            y = n % side;
            board[x][y] = COMPUTERMOVE;
            printf("Computer has put a %c in cell %d\n\n", COMPUTERMOVE, n + 1);
            showBoard(board);
            moveIndex++;
            whoseTurn = human;
        }
        else if (whoseTurn == human)
        {
            printf("You can insert in the following positions: \n");
            for (int i = 0; i < side; i++)
            {
                for (int j = 0; j < side; j++)
                {
                    if (board[i][j] == '*')
                        printf("%d ", (i * 3 + j) + 1);
                }
            }
            printf("\nEnter a position : ");
            scanf("%d", &n);
            n--;
            x = n / side;
            y = n % side;
            if (board[x][y] == '*' && n < 9 && n >= 0)
            {
                board[x][y] = HUMANMOVE;
                printf("\nHUMAN has put %c in cell %d\n\n", HUMANMOVE, n + 1);
                showBoard(board);
                moveIndex++;
                whoseTurn = computer;
            }
            else if (board[x][y] != '*' && n < 9 && n >= 0)
            {
                printf("\nPosition occupied, enter a valid position.\n");
            }
            else if (n > 8 || n < 0)
            {
                printf("Invalid Position");
            }
        }
    }
    if (gameOver(board) == false && moveIndex == side * side)
        printf("It's a draw.\n");
    else if (gameOver(board) == true)
    {
        if (whoseTurn == computer)
            whoseTurn = human;
        else if (whoseTurn == human)
            whoseTurn = computer;

        declareWinner(whoseTurn);

    }
    return ;
}
int main()
{
    printf("\n---------------------------------------------------------------------\n\n");
    printf("\t\tLet's play Tic-Tac-Toe :) !\n");
    printf("\n---------------------------------------------------------------------\n\n");

    int c=1;
    while(c==1){
        char choice;
        printf("Do you want to start first? (y for yes/n for no) : ");
        cin>>choice;
        // cont=choice;
        if (choice == 'n')
            playTTT(computer);
        else if (choice == 'y')
            playTTT(human);
        else
          { printf("Invalid choice");}

        printf("Do you want to quit?(0 for yes/1 for no) :  ");
        scanf("%d", &c);

    }

    return (5);
}