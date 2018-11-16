#include <vector>

#define ROW_ERROR "Invalid input! Please enter a row index between 0 and "
#define COL_ERROR "Invalid input! Please enter a column index between 0 and "
#define OCCUPIED_SPOT "Invalid spot! You can only play at empty spots in the grid."
#define PLAYER_ERROR "Invalid player number! Only players allowed are 1 and 2."

class Grid {
    std::vector<std::vector<char>> game_grid;
    int length;
    char p1 = 'X';
    char p2 = 'O';
    
    void build_grid();
    void check_victory_helper(char c);
    bool check_row(int r);
    bool check_column(int c);
    bool check_diagonal(int c);

public:
    Grid();
    Grid(int in_rows);
    void display_grid();
    bool play_spot(int row, int col, int player);
    bool check_victory();
};