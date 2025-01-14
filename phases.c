

#include "checks.h"
#include "player.h"
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include  "board.h"
#include "phases.h"
void movement_phase(struct Game* game_now) {
    verify_moves_p(game_now);
    set_player(game_now);
    while (game_not_over(game_now)) {
        if (!any_move_possible(game_now)) {
            printf("no moves possible for player %d\n",game_now->current_player);
            change_player(game_now);
            continue;
        }
         printf("Player %d moves\n",game_now->current_player);
        
        print_board(game_now);
        do{
            if(!any_move_possible(game_now)){
                break;}
            choose_penguin(game_now);} while(!penguin_cant_move(game_now));
        if(!any_move_possible(game_now)){
                continue;}
        printf("chosen penguin coordinates (%d,%d)\n",game_now->current_penguin_row,game_now->current_penguin_col);
        int x, y;
        printf("give  your move coordinates\n");
        while (any_move_possible(game_now)){
            
            x = get_row();
            y = get_col();
            
            if (!check_if_coordinates_are_valid(x, y,game_now)) {
                printf("wrong coordinates\n");
                continue;
            }
            
            if (move_possible(x, y,game_now)) {
                printf("making a move\n");
                move(x, y,game_now);
                
                any_move_possible(game_now);
                break;  // Exit the loop if a valid move is made
            } else {
                printf("Invalid move. Choose a different move.\n");
                
            }
        }     
        change_player(game_now);
    }
    
    the_end(game_now);
}

void placement_phase(struct Game* game_now){

    for (int i=0;i<game_now->num_of_players;i++){
        game_now->players[i].how_many_fish=0;
    }
    int i=0;
    game_now->penguins_placed=3*game_now->num_of_players;
    generate_board(game_now);
    set_player( game_now);
    
    while(game_now->penguins_placed>0){
        
        int row;
        int col;
        print_board(game_now);

        do{
            row=get_row();
            col=get_col();
        
            if (!valid(row,col,game_now)){
                printf("wrong coordinates\n");
            }
        }while (!valid(row,col,game_now));
        game_now->player_now->placed_penguin_coord[i].x=row;
        game_now->player_now->placed_penguin_coord[i].y=col;
        game_now->player_now->how_many_fish+=game_now->board[row][col];
        game_now->board[row][col]=game_now->player_now->penguin_value;
        change_player(game_now);
        game_now->penguins_placed-=1;
        if (game_now->current_player==0){
            i++;
        }
    }
    
    print_board(game_now);

};