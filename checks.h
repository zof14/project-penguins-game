#pragma once
int valid(int x, int y,struct Game* game_now);
int penguin_cant_move(struct Game* game_now);
int game_not_over(struct Game* game_now);
int check_if_coordinates_are_valid(int row_coord,int col_coord, struct Game* game_now);
int move_possible(int x,int y, struct Game* game_now);
int any_move_possible(struct Game* game_now);
void verify_moves_p(struct Game* game_now);