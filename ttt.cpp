#include <iostream>
#include "ttt.h"

// helper to be called within constructors to fill out the game grid
void Grid::build_grid() {
    std::vector<char> row(length, '.');
    for (int i=0; i<length; i++) game_grid.push_back(row);
}

Grid::Grid() : length(3) {
    build_grid();
}

Grid::Grid(int in_length) : length(in_length) {
    build_grid();
}

// displays the grid along with the row/column index
// TODO: pretty printing for grids with 2-digit side lengths
void Grid::display_grid() {
    std::cout << "CURRENT STATE OF THE GAME:\n";

    // display column indexes
    std::cout << "  ";
    for (int c=0; c<length; c++) {
        std::cout << c << " ";
    }
    std::cout << '\n';

    for (int r=0; r<length; r++) {
        std::cout << r << ' ';
        for (int c=0; c<length; c++) {
            std::cout << game_grid[r][c] << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

// given a row/column index
// handle input errors as well in here
// proper input will be 0-indexed
// returns true if there were no issues, false otherwise
bool Grid::play_spot(int row, int col, int player) {
    if (row < 0 || row >= length) {
        std::cout << "ERROR: " << ROW_ERROR << length-1 << '\n';
        return false;
    }

    if (col < 0 || col >= length) {
        std::cout << "ERROR: " << COL_ERROR << length-1 << '\n';
        return false;
    }

    if (player < 1 || player > 2) {
        std::cout << "ERROR: " << PLAYER_ERROR << '\n';
        return false;
    }

    if (game_grid.at(row).at(col) != '.') {
        std::cout << "ERROR: " << OCCUPIED_SPOT << '\n';
        return false;
    }

    if (player == 1) game_grid.at(row).at(col) = p1;
    else game_grid.at(row).at(col) = p2;

    return true;
}

void Grid::check_victory_helper(char c) {
    if (c == p1) std::cout << "Player 1 wins!\n";
    else std::cout << "Player 2 wins!\n";
}

bool Grid::check_row(int row) {
    for (int column = 1; (size_t) column < game_grid.size(); column++) {
        // break as soon as we see that the row contains two mismatched chars
        if (game_grid[row][0] != game_grid[row][column]) return false;
    }
    check_victory_helper(game_grid[row][0]);
    return true;
}

// basically the same as checking the row but for columns
bool Grid::check_column(int column) {
    for (int row=1; (size_t) row<game_grid.size(); row++) {
        // break as soon as we see that the row contains two mismatched chars
        if (game_grid[0][column] != game_grid[row][column]) return false;
    }
    check_victory_helper(game_grid[0][column]);
    return true;
}

// two cases: pass in column 0, so we go from [0,0] to [c, c]
// pass in column c, so we go from [0, c] to [c, 0]
bool Grid::check_diagonal(int column) {
    int index = 0;
    if (column == 0) {
        while (index < length) {
            if (game_grid[0][0] != game_grid[index][index]) return false;
            index++;
        }
        check_victory_helper(game_grid[0][0]);
    } else {
        int index2 = column;
        while (index < length) {
            if (game_grid[0][column] != game_grid[index][index2]) return false;
            index++;
            index2--;
        }
        check_victory_helper(game_grid[0][column]);
    }
    return true;
}

// checks for the victory of
bool Grid::check_victory() {
    // check each row and column
    // if the first column of a row is empty 
    // or the first row of a column is empty, 
    // it wouldnt be possible to detect victory anyway!
    bool victory = false;
    for (int r=0; (size_t) r<game_grid.size(); r++) {
        if (game_grid[r][0] != '.') victory = check_row(r);
        if (victory) return victory;
    }

    for (int c=0; (size_t) c<game_grid.size(); c++) {
        if (game_grid[0][c] != '.') victory = check_column(c);
        if (victory) return victory;
    }

    // check diagonals
    if (game_grid[0][0] != '.' && check_diagonal(0)) return true;
    if (game_grid[0][length-1] != '.' && check_diagonal(length-1)) return true;

    return victory;
}