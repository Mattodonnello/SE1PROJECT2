//
// Created by Lili on 26/03/2020.
//

//
// Created by Lili on 24/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include "gameinit.h"

/* Implement the data structure necessary to define the  players in game_init.h
 •Players should be characterized by: name, color, number of own pieces accumulated,
 number of adversary’s pieces capture */

void printList( PiecePtr currentPtr )
{
        printf("|");
        /* while not the end of the list */
        while ( currentPtr != NULL ) {
            if(currentPtr->p_color == RED) printf("R");
            if(currentPtr->p_color == GREEN) printf("G");
            printf( "%c-->", currentPtr->p_color );
            currentPtr = currentPtr->next;
        } /* end while */

        printf( "NULL\t\t\t\t\t\t\t" );
} /* end function printList */

void initialize_players(player players[PLAYERS_NUM]) {
    int i, color_choice;

    for (i = 0; i < PLAYERS_NUM; i++) {
            players[i].pieces_kept = 18;
            players[i].pieces_captured = 0;

            printf("Please enter Player %d name: ", i + 1);
            scanf("%s", players[i].players_name);
            printf("\nEnter 1 if %s wants to use RED pieces or 2 if %s wants to use GREEN pieces:",
                   players[i].players_name, players[i].players_name);
            scanf("%d", &color_choice);

            if (color_choice < 1 || color_choice > 2) {
                printf("ERROR PLEASE ENTER EITHER ONE OR TWO");
                exit(0);
            } else if (color_choice == 1) {
                players[i].player_color = RED;
            } else if (color_choice == 2) {
                players[i].player_color = GREEN;
            }

            if (players[i].player_color == RED) {
                printf("\n%s will use RED pieces and initially has %d of his/her own pieces and %d of his/her opponents pieces\n\n",
                       players[i].players_name, players[i].pieces_kept, players[i].pieces_captured);
            } else if (players[i].player_color == GREEN) {
                printf("\n%s will use GREEN pieces and initially has %d of his/her own pieces and %d of his/her opponents pieces\n\n",
                       players[i].players_name, players[i].pieces_kept, players[i].pieces_captured);
            }

        }

    if (players[0].player_color == players[1].player_color) {
        printf("ERROR, PLAYERS CANNOT USE THE SAME COLOUR PIECE");
        exit(0);
    }
    }

//Set Invalid Squares (where it is not possible to place stacks)
void set_invalid(square * s){
s->type = INVALID;
s->stack = NULL;
s->num_pieces = 0;
}

//Set Empty Squares (with no pieces/stacks)
void set_empty(square * s){
s->type = VALID;
s->stack = NULL;
s->num_pieces = 0;
}

//Set squares  with a GREEN piece
void set_green(square * s){
s->type = VALID;
s->stack = (piece *) malloc (sizeof(piece));
s->stack->p_color = GREEN;
s->stack->next = NULL;
s->num_pieces = 1;
}

//Set squares with a RED piece
void set_red(square * s){
s->type = VALID;
s->stack = (piece *) malloc (sizeof(piece));
s->stack->p_color = RED;
s->stack->next = NULL;
s->num_pieces = 1;
}

//initializes the board
void initialize_board(square board [BOARD_SIZE][BOARD_SIZE]){

    for(int i=0; i< BOARD_SIZE; i++){
        for(int j=0; j< BOARD_SIZE; j++){
            //invalid squares
            if((i==0 && (j==0 || j==1 || j==6 || j==7)) ||
               (i==1 && (j==0 || j==7)) ||
               (i==6 && (j==0 || j==7)) ||
               (i==7 && (j==0 || j==1 || j==6 || j==7)))
                set_invalid(&board[i][j]);

            else{
                //squares with no pieces
                if(i==0 || i ==7 || j==0 || j == 7)
                    set_empty(&board[i][j]);
                else{
                    //squares with red pieces
                    if((i%2 == 1 && (j < 3 || j> 4)) ||
                       (i%2 == 0 && (j == 3 || j==4)))
                        set_red(&board[i][j]);
                        //green squares
                    else set_green(&board[i][j]);
                }
            }
        }


    }


}

