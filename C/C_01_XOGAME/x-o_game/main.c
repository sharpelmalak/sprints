#include <stdio.h>
#include <string.h>

typedef unsigned char uint8_t;
#include "x_o.h" // include functions prototypes
#define boardSize 9


// Globals
uint8_t board[boardSize] = {'1','2','3','4','5','6','7','8','9'};
uint8_t symbols[2]={}; // [x,o]
uint8_t winner; // x or o
uint8_t *configArray=&symbols; // player(1) is the first index in symbols array | player(2) is the second index in symbols array
uint8_t *win=&winner; // pointer to the winner variable


int main() {

    /* gamestate initially = 2 ( 0 --> winning | 1 --> drawing | 2 --> continue the game )
    player = 1 will start the game
    i -- > counter */
   uint8_t gamestate=2,player=1,i;
   // *p -- > pointer to player variable
   uint8_t *p=&player;
   // set players config to choose symbols
   setPlayerConfig(configArray);

   //while gamestate is 2 we will play
   while(gamestate==2){

        if(*p==1){
           //load player and ask for the position then update board
            loadAndUpdate(*p);
           // check if the gamestate is it winning drawing continue the game
            getGameState(board,&gamestate);
           // update player
            *p++;
        }
        else if(*p==2){

            //load player and ask for the position then update board
            loadAndUpdate(*p);
           // check if the gamestate is it winning drawing continue the game
            getGameState(board,&gamestate);
           // update player
            *p--;
        }

    }


    // gamestate now is not equal 2 so while breaked
    printf("\n\t-------FINISHHHHH----------\n");
    // case Drawing gamestate = 1
    if(gamestate==1){
        //draw final board
        drawBoard(board);
        printf("\n\t-------Draw No Losers No Winners------\n");


    }
    // case winning gamestate = 0
    else{
        // the win symbol index is the win player
        for(i=0;i<2;i++){
            if(*win==symbols[i])printf("\n\t-------PLAYER %d WINS WITH %c SYMBOL------\n",i+1,symbols[i]);
        }
        //draw final board
        drawBoard(board);
    }

    // pause to any key hit
   system("pause");
   return 0;



}
