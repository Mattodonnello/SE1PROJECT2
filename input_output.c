//
// Created by Lili on 26/03/2020.
//

//
// Created by Lili on 24/03/2020.
//

#include <stdio.h>
#include "input_output.h"

/* FUnction to print the board:
 * Invalid Squares are printed as | - |
 * Valid empty squares are printed as |   |
 * Valid squares with a GREEN piece are printed as | G |
 * Valid squares with a RED piece are printed as | R | */

void stacks(square board[BOARD_SIZE][BOARD_SIZE], int i, int j, int k, int l) {

    piece *top = board[i][j].stack;
    board[i][j].stack = NULL;
    board[i][j].num_pieces = 0;
    piece *curr = top;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = board[k][l].stack;
    board[k][l].stack = top;

}

void print_board(square board[BOARD_SIZE][BOARD_SIZE]){
    printf("****** The Board ******\n");
    for(int i = 0; i < BOARD_SIZE; i ++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j].type == VALID) {
                if(board[i][j].stack == NULL)
                    printf("|   ");
                else{
                    if (board[i][j].stack->p_color == GREEN)
                        printf("| G ");
                    else printf("| R ");
                }
            }
            else
                printf("| - ");
        }
        printf("|\n");
    }
}

    void over_five(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM], int k, int l) {
        int count = 1; // Initialise variable count
        piece *curr = board[k][l].stack;
        piece *last = NULL;
        int count_red=0, count_green=0;

        // Loop through stack and if we get to a 5th element we make that element equal to last
        while (curr != NULL) {
            if (count < 5) {
                curr = curr->next;
                count++;
            } else {
                last = curr;
            }

            /* We remove pieces from the bottom of the stack, one by one. While doing this we keep track of the
             * colours of the pieces we're removing and store these values */
            if (last != NULL) {
                curr = curr->next;
                while (curr != NULL) {
                    piece *toRemove = curr;
                    if(toRemove->p_color == RED){
                        count_red++;
                    }
                    else if(toRemove->p_color == GREEN){
                        count_green++;
                    }
                    curr = curr->next;
                    free(toRemove);
                }
                last->next = NULL;
            }
        }

        /* We store excess stack pieces that we removed in our pieces_kept and pieces_captured by each player
         * obviously making sure that the players are capturing opponents pieces and keeping their own */
        for(int x=0; x<PLAYERS_NUM; x++){
        if(board[k][l].stack->p_color == RED && players[x].player_color == RED){
            players[x].pieces_kept+=count_red;
            players[x].pieces_captured+=count_green;
        }

            if(board[k][l].stack->p_color == GREEN && players[x].player_color == GREEN){
                players[x].pieces_kept+=count_green;
                players[x].pieces_captured+=count_red;
            }
        }
    }

void make_move(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM]) {
    int i, j, k, l;
    int choice, validation;
    printf("\nWould you like to play the game (ENTER 1 FOR YES, ANY OTHER NUMBER FOR NO): ");
    scanf("%d", &validation);

    while (validation == 1) {
        for (int x = 0; x < PLAYERS_NUM; x++) {
            printf("\n%s, please enter the row of the piece you want to move: ", players[x].players_name);
            scanf("%d", &i);
            printf("\n%s, Please enter the column of the piece you want to move: ", players[x].players_name);
            scanf("%d", &j);
            printf("\n%s, Please enter whether you would like to move the stack/piece up, down, left or right.\nEnter 1 for up, 2 for down, 3 for left or 4 for right:",players[x].players_name);
            scanf("%d", &choice);

            if (choice == 1){
                k = i-1;
                l = j;
            }
            if (choice == 2){
                k = i+1;
                l = j;
            }
            if (choice == 3){
                k = i;
                l = j-1;
            }
            if (choice == 4){
                k = i;
                l = j+1;
            }

            if((k==0 && (l ==0 || l==1 || l==6 || l==7)) ||
               (k==1 && (l==0 || l==7)) ||
               (k==6 && (l==0 || l==7)) ||
               (k==7 && (l==0 || l==1 || l==6 || l==7)))
            {
                printf("ERROR, Move to invalid square");
                break;
            }

            if (board[i][j].stack->p_color != players[x].player_color) {
                printf("ERROR please enter a square where your color is actually present and is the top piece of the stack");
                break;
            }


            push(board[i][j].stack->p_color, &board[k][l].stack);
            pop(&board[i][j].stack);
            print_board(board);
        }
    }

    while (validation != 1){
        printf("PLAYERS HAVE CHOSEN NOT TO PLAY THE GAME");
        exit(0);
    }
}
