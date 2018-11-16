#include <iostream>
#include <string>
#include <exception>
#include "ttt.h"

// runs one turn of the game
void game_tick(Grid &board, int player) {
    std::string row, col;
    int r, c;

    // continually ask for input until the player makes a valid move
    do {
        std::cin >> row;
        std::cin >> col;
        r = c = -1;
        // sanitize input to ints
        try {
            r = stoi(row);
            c = stoi(col);
        } catch (std::exception& e) {
            std::cout << "ERROR: Integer input only!" << std::endl;
        }
        
    } while (!board.play_spot(r, c, player));

    board.display_grid();
}

// main driver
int main() {
    std::string length;
    int l;
    std::cout << "Welcome to Tic-Tac-Toe! How long is your square game board? ";
    
    // sanitize the input
    do {
        std::cin >> length;
        l = -1;
        try {
            l = stoi(length);
        } catch (std::exception& e) {
            std::cout << "ERROR: Integer input only!" << std::endl;
        }
    } while (l == -1);
    
    // construct our grid with the length input
    Grid board(l);
    board.display_grid();

    // main game loop section
    int current_player = 1;
    int turns = 1;
    int turn_limit = l*l;
    bool victory = false;
    while (!victory && turns <= turn_limit) {
        std::cout << "PLAYER " << current_player << "'S TURN\n";
        game_tick(board, current_player);

        if (current_player == 1) current_player = 2;
        else current_player = 1;
        turns++;
        victory = board.check_victory();
    }
    if (turns > turn_limit && !victory) std::cout << "Draw!\n";
    return 0;
}