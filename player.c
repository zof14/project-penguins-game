

#include "phases.h"
#include "checks.h"

#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include  "board.h"
#include "player.h"

void move(int x,int y,struct Game* game_now){
    int i=0;
    

    (game_now->player_now->how_many_fish)+=game_now->board[x][y];
    game_now->board[game_now->current_penguin_row][game_now->current_penguin_col]=0;

    for(i=0;i<3;i++){
        if(game_now->player_now->placed_penguin_coord[i].x==game_now->current_penguin_row && 
        game_now->player_now->placed_penguin_coord[i].y==game_now->current_penguin_col){
            game_now->player_now->placed_penguin_coord[i].x=x;
            game_now->player_now->placed_penguin_coord[i].y=y;
        }
    }
    game_now->board[x][y]=game_now->player_now->penguin_value;
    printf("move successful\n");
}
;
void choose_penguin(struct Game* game_now){
    int num;
    
    do{
        printf("choose a penguin (1-3)\n");
        scanf("%d",&num);
        if (num!=1 && num !=2 && num!=3){
            printf("such penguin doesn't exist\n");
        }
    }while(num!=1 && num !=2 && num!=3);
    game_now->current_penguin_row= game_now->player_now->placed_penguin_coord[num-1].x;
    game_now->current_penguin_col= game_now->player_now->placed_penguin_coord[num-1].y;
};

int get_row(){
    int row_coord;
    printf("give the row coordinate\n");
    scanf("%d",&row_coord);
    return row_coord;
};

int get_col(){
    int col_coord;
    printf("give the column coordinate\n");
    scanf("%d",&col_coord);
    return col_coord;
};
void set_player(struct Game* game_now){
    game_now->current_player=0;
    game_now->player_now = &game_now->players[0];
}

void change_player(struct Game* game_now) {
    if (game_now->current_player == game_now->num_of_players - 1) {
        game_now->current_player = 0;
        game_now->player_now = &game_now->players[game_now->current_player];
    } 
    else {
        for (int i = 0; i < game_now->num_of_players - 1; i++) {
            if (game_now->current_player == i) {
                game_now->current_player = i + 1;
                game_now->player_now = &game_now->players[game_now->current_player];
                break;
            }
        }
    }
}