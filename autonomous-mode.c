#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MY_PLAYER_VALUE 5
#define MY_PLAYER_ID "player_E"
struct Penguin {
    int x;
    int y;
    
};

struct PlayerInf {
    char id[10];
    int value;
    int score;
    struct Penguin penguins[10];
    int penguins_on_board;
};

struct GameInf {
    int rows;
    int cols;
    int board[100][100];
    struct PlayerInf players[10];
    int num_of_players;
};

void read_gamestate(char *file_name, struct GameInf *game){
    game->num_of_players=0;
    FILE *input_file = fopen(file_name, "r");
    if (input_file == NULL) {
        printf("input file can't be opened\n");
        exit(2);
    }
    
    fscanf(input_file, "%d %d", &game->rows, &game->cols);
    
    for (int i = 0; i < game->rows; i++) {
        for (int j = 0; j < game->cols; j++) {
            fscanf(input_file, "%d", &game->board[i][j]);
        }
    }

    while (fscanf(input_file, "%s %d %d", (game->players[game->num_of_players].id), &(game->players[game->num_of_players].value), &(game->players[game->num_of_players].score)) == 3) {
        game->num_of_players++;
    }
    
    fclose(input_file);
}
int find_my_index(struct GameInf *game){
    int my_index=-1;
    for(int i=0;i<game->num_of_players;i++){
        if (game->players[i].value==MY_PLAYER_VALUE){
            my_index=i;
            return my_index;
        }
    }
    if(my_index==-1){
        
        strcpy(game->players[game->num_of_players].id, MY_PLAYER_ID);
        game->players[game->num_of_players].value=MY_PLAYER_VALUE;
        game->players[game->num_of_players].score=0;
        game->num_of_players++;
        my_index=game->num_of_players-1;
    }
   
    return my_index;
}


void write_gamestate(char *output_file_name, struct GameInf *game){
    FILE *output_file = fopen(output_file_name, "w");
    if (output_file == NULL) {
        printf("output file can't be opened");
        exit(2);
    }
    
    fprintf(output_file, "%d %d\n", game->rows, game->cols);

    for (int i = 0; i < game->rows; i++) {
        for (int j = 0; j < game->cols; j++) {
            if (game->board[i][j]<10){
                fprintf(output_file, "0%d ", game->board[i][j]);
                continue;
            }
            fprintf(output_file, "%d ",game-> board[i][j]);
        }
        fprintf(output_file, "\n");
    }
    
    for (int i = 0; i <game-> num_of_players; i++) {
        fprintf(output_file, "%s %d %d\n", game->players[i].id, game->players[i].value, game->players[i].score);
    }
  
    fclose(output_file);
}





void add_points(int score,int my_index, struct GameInf *game){
    
    game->players[my_index].score+=score;
}


void my_penguins(struct GameInf *game,int my_index){
    
    int num_placed=0;
    
    for (int i = 0; i < game->rows; i++) {
        for (int j = 0; j < game->cols; j++) {
            if(game->board[i][j]==MY_PLAYER_VALUE || game->board[i][j]==(10+MY_PLAYER_VALUE) || game->board[i][j]==(20+MY_PLAYER_VALUE) || game->board[i][j]==(30+MY_PLAYER_VALUE)){
                
                game->players[my_index].penguins[num_placed].x=i;
                game->players[my_index].penguins[num_placed].y=j;
                num_placed+=1;
            }
        }

    }
    game->players[my_index].penguins_on_board=num_placed;
}
int placement(int num,char *file_name,char *output_file_name, struct GameInf *game){
    
   read_gamestate(file_name,game);

   int my_index;

   my_index=find_my_index(game);
  
   my_penguins(game,my_index);

   if (game->players[my_index].penguins_on_board==num){
    return 1;
   }


    //check how many penguins are placed
    
    int place_row;
    int place_col;
    int score=0;
   
   
    do{
    place_row=rand() % (game->rows + 1);
    place_col=rand() % (game->cols + 1);
    }while(!(game->board[place_row][place_col] == 10 || game->board[place_row][place_col] == 20 || game->board[place_row][place_col] == 30));
    score+=game->board[place_row][place_col]/10;
    game->board[place_row][place_col]=MY_PLAYER_VALUE;
    
    add_points(score,my_index,game);

    write_gamestate(output_file_name,game);

    return 0;   
}


void verify_placed_penguins(struct GameInf *game){
    for (int i = 0; i < game->num_of_players; i++) {
        game->players[i].penguins_on_board = 0; 

        for (int j=  0; j < game->rows; j++) {
            for (int k = 0; k < game->cols; k++) {
                int current_val = game->board[j][k];

                // Check if the tile contains a player's value or that value + 10, 20, or 30
                if (current_val == game->players[i].value ||
                    current_val == game->players[i].value + 10 ||
                    current_val == game->players[i].value + 20 ||
                    current_val == game->players[i].value + 30) {
                    game->players[i].penguins_on_board++;
                }
            }
        }
    }
    int check= game->players[0].penguins_on_board;
    for(int i=1;i<game->num_of_players;i++){
        if (game->players[i].penguins_on_board!=check){
            printf("wrong number of penguins on the board");
            exit(2);
        }
    }
}
int check_surroundings(int chosen_row,int chosen_col, struct GameInf *game){
    if (game->board[chosen_row+1][chosen_col]==10 || game->board[chosen_row+1][chosen_col]==20 
        || game->board[chosen_row+1][chosen_col]==30){
        return 1;
    }

    if (game->board[chosen_row-1][chosen_col]==10 || game->board[chosen_row-1][chosen_col]==20 
        || game->board[chosen_row-1][chosen_col]==30){
        return 1;
    }
    if (game->board[chosen_row][chosen_col+1]==10 || game->board[chosen_row][chosen_col+1]==20 
        || game->board[chosen_row][chosen_col+1]==30){
        return 1;
    }
     if (game->board[chosen_row][chosen_col-1]==10 || game->board[chosen_row][chosen_col-1]==20 
        || game->board[chosen_row][chosen_col-1]==30){
        return 1;
    }
    
    return 0;
}

void make_move(int penguin,int my_index,int chosen_row,int chosen_col, struct GameInf *game){
    if (game->board[chosen_row+1][chosen_col]==10 || game->board[chosen_row+1][chosen_col]==20 
        || game->board[chosen_row+1][chosen_col]==30){
            game->players[my_index].score+=game->board[chosen_row+1][chosen_col]/10;
            game->players[my_index].penguins[penguin].x=chosen_row+1;
            game->players[my_index].penguins[penguin].y=chosen_col;
            game->board[chosen_row][chosen_col]=0;
            game->board[chosen_row+1][chosen_col]=MY_PLAYER_VALUE;
    }
    else if (game->board[chosen_row-1][chosen_col]==10 || game->board[chosen_row-1][chosen_col]==20 
    || game->board[chosen_row-1][chosen_col]==30){
            game->players[my_index].score+=game->board[chosen_row-1][chosen_col]/10;
            game->players[my_index].penguins[penguin].x=chosen_row-1;
            game->players[my_index].penguins[penguin].y=chosen_col;
            game->board[chosen_row][chosen_col]=0;
            game->board[chosen_row-1][chosen_col]=MY_PLAYER_VALUE;
    }
    else if (game->board[chosen_row][chosen_col+1]==10 || game->board[chosen_row][chosen_col+1]==20 
        || game->board[chosen_row][chosen_col+1]==30){
            game->players[my_index].score+=game->board[chosen_row][chosen_col+1]/10;
            game->players[my_index].penguins[penguin].x=chosen_row;
            game->players[my_index].penguins[penguin].y=chosen_col+1;
            game->board[chosen_row][chosen_col]=0;
            game->board[chosen_row][chosen_col+1]=MY_PLAYER_VALUE;
    }
    else if (game->board[chosen_row][chosen_col-1]==10 || game->board[chosen_row][chosen_col-1]==20 
        || game->board[chosen_row][chosen_col-1]==30){
            game->players[my_index].score+=game->board[chosen_row][chosen_col-1]/10;
            game->players[my_index].penguins[penguin].x=chosen_row;
            game->players[my_index].penguins[penguin].y=chosen_col-1;
            game->board[chosen_row][chosen_col]=0;
            game->board[chosen_row][chosen_col-1]=MY_PLAYER_VALUE;
    }

}

int movement(char *input_file,char *output_file_name,struct GameInf* game){
    read_gamestate(input_file,game);
    
    int my_index=find_my_index(game);
    
    verify_placed_penguins(game);
    
    my_penguins(game,my_index);
    
    int i=0;
    int chosen_row;
    int chosen_col;
   
    do{
        chosen_row=game->players[my_index].penguins[i].x;
        chosen_col=game->players[my_index].penguins[i].y;
        i++;
        if(i>game->players[my_index].penguins_on_board){
            printf("cannot move\n");
            exit(1);
        }
    }while(!check_surroundings(chosen_row,chosen_col,game));
    i-=1;
    make_move(i,my_index,chosen_row,chosen_col,game);

    write_gamestate(output_file_name,game);

    return 0;

}

int main(int argc, char *argv[]) {
    if (argc<2){
        printf("not enough parameters\n");
        return 3;
    }
    struct GameInf game; 
    
    if (strcmp(argv[1], "name") == 0){
        printf("%s\n",MY_PLAYER_ID);
        return 0;
    } //phase=placement
   
    if (strcmp(argv[1], "phase=placement") == 0) {
        if (argc<5){
             printf("not enough parameters");

            return 3;
        }
        char a[2] = {argv[2][9], '\0'};
        int num_of_penguins=atoi(a);
        
        return (placement(num_of_penguins,argv[3],argv[4],&game));
        
    }
    else if (strcmp(argv[1], "phase=movement") == 0){
         if (argc<4){
             printf("not enough parameters\n");

            return 3;
        }
        return (movement(argv[2],argv[3],&game));
        
}
}

