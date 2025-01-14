#pragma once



void set_player(struct Game* game_now);
void change_player(struct Game* game_now);
int get_row();
int get_col();
void choose_penguin(struct Game* game_now);
void move(int x,int y,struct Game* game_now);