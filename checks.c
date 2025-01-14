

#include "board.h"
#include "structs.h"
#include "player.h"
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include "checks.h"

void verify_moves_p(struct Game* game_now){
    set_player(game_now);
    for(int i=0;i<game_now->num_of_players;i++){
        any_move_possible(game_now);
        change_player(game_now);
    }   
};

int any_move_possible(struct Game* game_now){
    int i = 0;
    int check_col;
    int check_row;
    int num_rows = game_now->num_rows;
    int num_cols = game_now->num_cols;

    for (i = 0; i < 3; i++) {
        check_row = game_now->player_now->placed_penguin_coord[i].x;
        check_col = game_now->player_now->placed_penguin_coord[i].y;

        if (check_row + 1 < num_rows &&
            (game_now->board[check_row + 1][check_col] == 3 || game_now->board[check_row + 1][check_col] == 2 || game_now->board[check_row + 1][check_col] == 1)) {
            return 1;
        }

        if (check_row - 1 >= 0 &&
            (game_now->board[check_row - 1][check_col] == 3 || game_now->board[check_row - 1][check_col] == 2 || game_now->board[check_row - 1][check_col] == 1)) {
            return 1;
        }

        if (check_col + 1 < num_cols &&
            (game_now->board[check_row][check_col + 1] == 3 || game_now->board[check_row][check_col + 1] == 2 || game_now->board[check_row][check_col + 1] == 1)) {
            return 1;
        }

        if (check_col - 1 >= 0 &&
            (game_now->board[check_row][check_col - 1] == 3 || game_now->board[check_row][check_col - 1] == 2 || game_now->board[check_row][check_col - 1] == 1)) {
            return 1;
        }
    }

    game_now->player_now->no_moves_possible = 0;
    return 0;
};

int move_possible(int x,int y, struct Game* game_now){
    int i=0;
    int current_penguin_row= game_now->current_penguin_row;
    int current_penguin_col=game_now->current_penguin_col;
    if (x!=current_penguin_row && y!=current_penguin_col){
        return 0;
    }
    if (x==current_penguin_row){
        if (y>current_penguin_col){
            for(i=current_penguin_col+1;i<=y;i++){
                if (game_now->board[x][i]==0 ){
                    return 0;
                }
                for(int val=0;val<game_now->num_of_players;val++){
                    if(game_now->board[x][i]== game_now->players[val].penguin_value){
                        return 0;
                    }
                }
        
            }
        }
        if (y<current_penguin_col){
            for(i=current_penguin_col-1;y<=i;i--){
                if (game_now->board[x][i]==0 ){
                    return 0;
                }
                for(int val=0;val<game_now->num_of_players;val++){
                    if(game_now->board[x][i]== game_now->players[val].penguin_value){
                        return 0;
                    }
                }
            }
        }
    }
    if (y==current_penguin_col){
        if (x>current_penguin_row){
            for(i=current_penguin_row+1;i<=x;i++){
                if (game_now->board[i][y]==0 ){
                    return 0;
                }
                for(int val=0;val<game_now->num_of_players;val++){
                    if(game_now->board[i][y]== game_now->players[val].penguin_value){
                        return 0;
                    }
                }
            }
        }
        if (x<current_penguin_row){
            for(i=current_penguin_row-1;x<=i;i--){
                if (game_now->board[i][y]==0 ){
                    return 0;
                }
                for(int val=0;val<game_now->num_of_players;val++){
                    if(game_now->board[i][y]== game_now->players[val].penguin_value){
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
};
int check_if_coordinates_are_valid(int row_coord,int col_coord, struct Game* game_now) {
    if ((row_coord>=0 && row_coord<=game_now->num_rows)&& (col_coord>=0 && col_coord<=game_now->num_cols)){
        return 1; 
    } //only tells if the coordinates exist within the board not if the move itself is possible}
    return 0;
};


int game_not_over(struct Game* game_now){
   
    for(int i =0;i<game_now->num_of_players;i++){
        if (game_now->players[i].no_moves_possible!=0){
            return 1;
        }
    }
    return 0;
};

int penguin_cant_move(struct Game* game_now){
    int current_penguin_col = game_now->current_penguin_col;
    int current_penguin_row = game_now->current_penguin_row;


    if (current_penguin_row + 1 < game_now->num_rows &&
        (game_now->board[current_penguin_row + 1][current_penguin_col] == 1 ||
         game_now->board[current_penguin_row + 1][current_penguin_col] == 2 ||
         game_now->board[current_penguin_row + 1][current_penguin_col] == 3)) {
        return 1;
    }

    if (current_penguin_row - 1 >= 0 &&
        (game_now->board[current_penguin_row - 1][current_penguin_col] == 1 ||
         game_now->board[current_penguin_row - 1][current_penguin_col] == 2 ||
         game_now->board[current_penguin_row - 1][current_penguin_col] == 3)) {
        return 1;
    }

    if (current_penguin_col + 1 < game_now->num_cols &&
        (game_now->board[current_penguin_row][current_penguin_col + 1] == 1 ||
         game_now->board[current_penguin_row][current_penguin_col + 1] == 2 ||
         game_now->board[current_penguin_row][current_penguin_col + 1] == 3)) {
        return 1;
    }

    if (current_penguin_col - 1 >= 0 &&
        (game_now->board[current_penguin_row][current_penguin_col - 1] == 1 ||
         game_now->board[current_penguin_row][current_penguin_col - 1] == 2 ||
         game_now->board[current_penguin_row][current_penguin_col - 1] == 3)) {
        return 1;
    }

    printf("This penguin cannot move.\n");
    return 0;
};

int valid(int x, int y,struct Game* game_now){

        if (game_now->board[x][y]!=1 && game_now->board[x][y]!=2 && game_now->board[x][y]!=3){
            return 0;
        } 
        
        if(x>= game_now->num_rows|| y>=game_now->num_cols){
            return 0;
        }
    return 1;
    }
