#include <stdio.h>
#include "triangle_routines.h"

#define NMOVES 36
#define PEG_SPACES 15
int moves[NMOVES][3] =
{
  {0, 1, 3},
  {3, 1, 0},
  {1, 3, 6},
  {6, 3, 1},
  {3, 6, 10},
  {10, 6, 3},
  {2, 4, 7}, 
  {7, 4, 2},
  {4, 7, 11},
  {11, 7, 4},
  {5, 8, 12},
  {12, 8, 5},
  {0, 2, 5}, 
  {5, 2, 0},
  {2, 5, 9},
  {9, 5, 2},
  {5, 9, 14},
  {14, 9, 5},
  {1, 4, 8},
  {8, 4, 1},
  {4, 8, 13}, 
  {13, 8, 4},
  {3, 7, 12},
  {12, 7, 3},
  {3, 4, 5}, 
  {5, 4, 3},
  {6, 7, 8}, 
  {8, 7, 6},
  {7, 8, 9}, 
  {9, 8, 7},
  {10, 11, 12},
  {12, 11, 10},
  {11, 12, 13}, 
  {13, 12, 11},
  {12, 13, 14},
  {14, 13, 12}
};

/* Return the number of pegs on the board. */
int npegs(int board[]);

/* Return 1 if the move is valid on this board, otherwise return 0. */
int valid_move(int board[], int move[]);

/* Make this move on this board. */
void make_move(int board[], int move[]);

/* Unmake this move on this board. */
void unmake_move(int board[], int move[]);

/* 
 * Solve the game starting from this board.  Return 1 if the game can
 * be solved; otherwise return 0.  Do not permanently alter the board passed
 * in. Once a solution is found, print the boards making up the solution in
 * reverse order. 
 */
int solve(int board[]);

int npegs(int board[]) {
    int numPegs = 0;
    int i;
    for (i = 0; i < PEG_SPACES; i++) {
        numPegs += board[i];
    }
    return numPegs;
}

int valid_move(int board[], int move[]) {
    if (board[move[0]] == 1 && board[move[1]] == 1 && board[move[2]] == 0) {
        return 1;
    }
    return 0;
}

void make_move(int board[], int move[]) {
    board[move[0]] = 0;
    board[move[1]] = 0;
    board[move[2]] = 1;
}

void unmake_move(int board[], int move[]) {
    board[move[0]] = 1;
    board[move[1]] = 1;
    board[move[2]] = 0;
}

int solve(int board[]) {
    int i;
    int sum = 0;
    if (npegs(board) == 1) {
        triangle_print(board);
        printf("\n");
        return 1;
    }
    for (i = 0; i < NMOVES; i++) {
        if (valid_move(board, moves[i])) {
            make_move(board, moves[i]);
            if (sum == 0) {
                sum = solve(board);
            }
            unmake_move(board, moves[i]);
        }
    }
    if (sum == 1) {
        triangle_print(board);
        printf("\n");
    }
    return sum;
}

int main(int argc, char* argv[]) {
    int board[15];
    triangle_input(board);

    printf("Here is the entered board: \n");
    triangle_print(board);

    printf("Here's the solution: \n");
    solve(board);
    return 0;
}
