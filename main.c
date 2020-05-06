#include <stdio.h>
#include "input_output.h"

// Function main begins execution
int main() {

    // declaration of the players and the board
    player players[PLAYERS_NUM];
    square board[BOARD_SIZE][BOARD_SIZE];

    // Function to initialise our players
    initialize_players(players);

    // Function to initialise our players
    initialize_board(board);

    // Function to print our original board
    print_board(board);

    // Function to allow players to play the game until a winner is found
    make_move(board, players);

    return 0;
}
// Function main finishes execution
