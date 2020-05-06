#include <stdio.h>
#include <stdlib.h>
#include "input_output.h"

// Function to push one element to the top of a stack
void push(color p_color, PiecePtr *top){
    struct piece* curr = (PiecePtr)malloc(sizeof(struct piece));
    curr -> p_color = p_color;
    curr -> next = *top;
    (*top) = curr;
}

// Function to remove one element from the top of the stack
void pop(PiecePtr *top){
    if(*top != NULL){
        PiecePtr tempPtr = *top;
        *top = (*top) -> next;
        free(tempPtr);
    }
}

// Function to merge two stacks placing one on top of the other
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

/* Our function over_five makes sure our squares don't exceed 5 pieces. If our squares do exceed 5 pieces, the pieces
 * are removed from the bottom. We keep track of each piece removed storing it in pieces_kept/pieces_captured by
 * each opponent. */
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

/* FUnction to print the board:
 * Invalid Squares are printed as | - |
 * Valid empty squares are printed as |   |
 * Valid squares with a GREEN piece are printed as | G |
 * Valid squares with a RED piece are printed as | R | */
// I edited this slightly to allow for sizeable stacks, also adding function print_list to print more than one element
        void print_board(square board[BOARD_SIZE][BOARD_SIZE]){
    printf("****** The Board ******\n");
    for(int i = 0; i < BOARD_SIZE; i ++){
        for (int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j].type == VALID) {
                if(board[i][j].stack == NULL)
                    printf("|\t\t\t\t\t\t\t\t\t\t");
                else{
                    if (board[i][j].stack->p_color == GREEN && board[i][j].stack->next == NULL)
                        printf("| G\t\t\t\t\t\t\t\t\t\t");
                    if (board[i][j].stack->p_color == RED && board[i][j].stack->next == NULL)
                         printf("| R\t\t\t\t\t\t\t\t\t\t");
                    else if(board[i][j].stack->next != NULL){
                        printList(board[i][j].stack);
                }
            }
            }
            else
                printf("| -\t\t\t\t\t\t\t\t\t\t");
        }
        printf("|\n");
    }
}

/* Function size_stack keeps a track of the size of our stack. This will be useful when determining how many places
 * we can move the stack up, down, left or right in function make_move */
int size_stack(square board[BOARD_SIZE][BOARD_SIZE], int i, int j) {
    int count = 0;
    piece *curr = board[i][j].stack;
    while (curr != NULL) {
        if (count < 5) {
            curr = curr->next;
            count++;
        }
    }
        return count;
}


// Function make_move essentially runs our game prompting players to make moves on the board
void make_move(square board[BOARD_SIZE][BOARD_SIZE], player players[PLAYERS_NUM]) {
    int i, j, k = 0, l = 0;
    int sumk = 0, suml = 0;
    int choice, validation;
    int count = 0;
    int count2 = 0;
    int count3 = 0;
    int a, b, c, d;
    int p, q;
    // We prompt the players to answer whether or not they want to play our game
    printf("\nWould you like to play the game (ENTER 1 FOR YES, ANY OTHER NUMBER FOR NO): ");
    scanf("%d", &validation);

    while (validation == 1) {
        for (int x = 0; x < PLAYERS_NUM; x++) {

  /* The Following code I have commented is the code I was trying to use to allow players to put the pieces they'd kept
   * back into the game so they could keep playing. This code also would have determined who lost the game. Unfortunately
   * this code kept returning a segmentation fault and I couldn't figure out why. Therefore I commented it so that the
   * game still ran but a winner was not found*/

  /* for (p = 0; p < BOARD_SIZE; p++) {
               for (q = 0; q < BOARD_SIZE; q++) {

if (board[p][q].type == VALID && board[p][q].stack->p_color == RED) {
count2++;
}

if (board[p][q].type == VALID && board[p][q].stack->p_color == GREEN) {
count3++;
}
}
} */

/*
if (count2 == 0 && players[x].player_color == RED && players[x].pieces_kept != 0) {
printf("Please pick the row of a square on the board to reenter one of your kept pieces onto:");
scanf("%d", &a);
printf("Please pick the row of a square on the board to reenter one of your kept pieces onto:");
scanf("%d", &b);
push(players[x].player_color, &board[a][b].stack);
over_five(board, players, a, b);
print_board(board);
players[x].pieces_kept--;
}

if (count3 == 0 && players[x].player_color == GREEN && players[x].pieces_kept != 0) {
printf("Please pick the row of a square on the board to reenter one of your kept pieces onto:");
scanf("%d", &c);
printf("Please pick the row of a square on the board to reenter one of your kept pieces onto:");
scanf("%d", &d);
push(players[x].player_color, &board[c][d].stack);
over_five(board, players, c, d);
print_board(board);
players[x].pieces_kept--;
}

if (count2 == 0 && players[x].player_color == RED && players[x].pieces_kept == 0) {
printf("%s (Player %d), Has Lost the game", players[x].players_name, x + 1);
exit(0);
}

if (count3 == 0 && players[x].player_color == GREEN && players[x].pieces_kept == 0) {
printf("%s (Player %d), Has Lost the game", players[x].players_name, x + 1);
exit(0);
} */


            // Each Player is prompted to enter the column and row of the piece/stack they want to move
            printf("\n%s, please enter the row of the piece/stack you want to move: ", players[x].players_name);
            scanf("%d", &i);
            printf("\n%s, Please enter the column of the piece/stack you want to move: ", players[x].players_name);
            scanf("%d", &j);

            /* If either player tries to move their piece/stack to an invalid square an Error will occur and the program
             * will be terminated */
            if ((i == 0 && (j == 0 || j == 1 || j == 6 || j == 7)) ||
                (i == 1 && (j == 0 || j == 7)) ||
                (i == 6 && (j == 0 || j == 7)) ||
                (i == 7 && (j == 0 || j == 1 || j == 6 || j == 7))) {
                printf("ERROR, INVALID SQUARE WAS CHOSEN\n");
                exit(0);
            }

            /* If either player tries to move a piece/stack which doesn't contain their piece, as the top piece, an Error
             * will occur and the program will be terminated */
            if (board[i][j].stack->p_color != players[x].player_color) {
                printf("ERROR, YOUR SQUARE COLOUR IS NOT PRESENT OR IS NOT THE TOP OF THE STACK\n");
                exit(0);
            }

            // We keep track of the size of each stack
            count = size_stack(board, i, j);

            /* We get the user to enter the number of moves they wish to make. This corresponds to the size of the stack
             * they're moving */
            for (int z = 0; z < count; z++) {

                printf("\n%s, Please enter whether you would like to move the stack/piece up, down, left or right.\nEnter 1 for up, 2 for down, 3 for left or 4 for right:",
                       players[x].players_name);
                scanf("%d", &choice);

                if (choice == 1) {
                    k = i - 1;
                    l = j;
                }
                if (choice == 2) {
                    k = i + 1;
                    l = j;
                }
                if (choice == 3) {
                    k = i;
                    l = j - 1;
                }
                if (choice == 4) {
                    k = i;
                    l = j + 1;
                } else if (choice < 1 || choice > 4) {
                    printf("ERROR, Choice not appropriate");
                    exit(0);
                }

                if ((k == 0 && (l == 0 || l == 1 || l == 6 || l == 7)) ||
                    (k == 1 && (l == 0 || l == 7)) ||
                    (k == 6 && (l == 0 || l == 7)) ||
                    (k == 7 && (l == 0 || l == 1 || l == 6 || l == 7))) {
                    printf("ERROR, Move to invalid square");
                    exit(0);
                }

                sumk += k;
                suml += l;
            }
            stacks(board, i, j, sumk - ((count - 1) * i), suml - ((count - 1) * j));
            over_five(board, players, sumk - ((count - 1) * i), suml - ((count - 1) * j));
            print_board(board);
            sumk = 0;
            suml = 0;
        }
    }

    while (validation != 1) {
        printf("PLAYERS HAVE CHOSEN NOT TO PLAY THE GAME");
        exit(0);
    }
}
