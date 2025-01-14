
#include "phases.h"
#include "checks.h"
#include "player.h"
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include  "board.h"
#include "phases.h"

int main(){

    srand(time(NULL));

    struct Game game;
    struct Game* game_now = &game;

    set_player(game_now);
    generate_board(game_now);

    int rows,cols,num_players;
    do{
        printf("give number of rows for the board:\n");
        scanf("%d",&rows);
        if(rows<=0){
            printf("invalid value");
        }
    } while(rows<=0);
    do{
        printf("give number of columns for the board:\n");
        scanf("%d",&cols);
        if(cols<=0 || cols!=rows){
            printf("invalid value");
        }
    }while(cols<=0 || cols!=rows);
    do{
        printf("Give the number of players :\n");
        scanf("%d", &num_players);
        if(num_players<=0){
            printf("invalid value");
        }
    }while(num_players<=0);

    
    game_now->num_rows = rows;
    game_now->num_cols = cols;

    
    game_now->num_of_players = num_players;

    for (int i = 0; i < num_players; i++) {
        game_now->players[i].penguin_value = i + 5; 
        game_now->players[i].no_moves_possible = 1;
    }
    printf("PLACEMENT PHASE\n");
    placement_phase(game_now);
    
    printf("MOVEMENT PHASE\n");
    movement_phase(game_now);
    
    return 1;
}