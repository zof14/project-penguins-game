
#include "structs.h"
#include "board.h"

#include<stdio.h>
#include <stdlib.h>
#include <time.h>


void the_end(struct Game* game_now){
    printf("THE END\n");
    int max=game_now->players[0].how_many_fish;
    int winner = 0;
    for(int i=0;i<game_now->num_of_players;i++){
        printf("Player %d collected %d fish\n",i,game_now->players[i].how_many_fish);
        if (game_now->players[i].how_many_fish > max) {
            max = game_now->players[i].how_many_fish;
            winner = i;
        }
    }
    printf("Player %d wins!\n", winner);

};


int getRandomNumber() {
    return rand() % 3 + 1;
}

void generate_board(struct Game* game_now) {
    // Function to generate a board with random numbers from 1 to 3
    for (int i = 0; i < game_now->num_rows; i++) {
        for (int j = 0; j <game_now->num_cols; j++) {
            game_now->board[i][j] = getRandomNumber();
        }
    }
}

void print_board(struct Game* game_now) {
    printf("   BOARD\n");
    // Function to print the board
    printf("   ");
    for (int i=0;i<game_now->num_rows;i++){
        printf("%d  ",i);
    }
    printf("\n");
    for (int i = 0; i < game_now->num_rows; i++) {
        printf("%d  ",i);
        for (int j = 0; j < game_now->num_cols; j++) {
		int temp_value=game_now->board[i][j];
        
            if (game_now->board[i][j]!=1 && game_now->board[i][j]!=2 && game_now->board[i][j]!=3 && game_now->board[i][j]!=0){
                int player_index = 0;
                while (game_now->players[player_index].penguin_value != temp_value) {
                    player_index++;}
                char penguin_letter = 'A' + player_index; 
                int penguin_num = 1;
                
                for (int k = 0; k < 3; k++) {
                    if (game_now->players[player_index].placed_penguin_coord[k].x == i &&
                        game_now->players[player_index].placed_penguin_coord[k].y == j) {
                        penguin_num = k + 1;
                        break;
                    }
                }
            printf("%c%d ", penguin_letter, penguin_num);
            }
            
            else{
            printf("%d  ", game_now->board[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}
