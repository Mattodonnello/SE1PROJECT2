#ifndef FOCUS_INPUT_OUTPUT_H
#define FOCUS_INPUT_OUTPUT_H

#endif //FOCUS_INPUT_OUTPUT_H

#include "gameinit.h"

//Function to print the board
void print_board(square board[BOARD_SIZE][BOARD_SIZE]); // Function prototype for print_board function
void make_move(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM]); // Function prototype for make_move function
void push(color p_color, PiecePtr *top); // Function prototype for push function
void pop(PiecePtr *top); // Function prototype for pull function
void stacks(square board[BOARD_SIZE][BOARD_SIZE], int i, int j, int k, int l); // Function prototype for stacks function
void over_five(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM], int k, int l); // Function prototype for over_five function
int size_stack(square board[BOARD_SIZE][BOARD_SIZE], int i, int j); // Function prototype for size_stack function

