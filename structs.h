#pragma once

struct Penguins {
    int x;
    int y;
    
};

struct Player {
    int how_many_fish;
    int no_moves_possible;
    int penguin_value;
    struct Penguins placed_penguin_coord[3];
};

struct Game {
    int board[100][100];
    int num_rows;
    int num_cols;
    int penguins_placed;
    int num_of_players;
    struct Player players[10];
    struct Player* player_now;
    int current_player;
    int current_penguin_row;
    int current_penguin_col;
};
