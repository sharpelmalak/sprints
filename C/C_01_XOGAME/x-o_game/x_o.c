typedef unsigned char uint8_t;
extern uint8_t board[];
extern uint8_t symbols[];
extern uint8_t *configArray;
extern uint8_t *win;
#define boardSize 9

// This function takes a board as an input and prints it on the console
void drawBoard(uint8_t* board) {
	uint8_t i;
	printf("\n");
	for (i = 0; i < boardSize; i++) {
		printf("\t%c\t", board[i]);
		if (i == 2 || i == 5 || i==8)printf("\n\n"); // to draw in rows
	}

	return;

}

//This function takes the (board, position to update ,value to set in this position)
void updateBoard (uint8_t *board, uint8_t position, uint8_t value){
board[position-1]=value;
}

// This function takes the player's number and asks the player to choose between X and O (case insensitive)
uint8_t getPlayerSymbol(uint8_t playerNumber, uint8_t * symbol){

 // take user input and check if it ( x,X,o,O, or any other characters)
 unsigned char symbolIn;
 scanf(" %c",&symbolIn);
 switch(symbolIn){

    case 'x':
     // check that symbols array did not hold x
     if(symbol[0]!='x' && symbol[1]!='x')
        {
            symbol[playerNumber-1]='x';
            return 0 ; //symbol is not wrong and/or was not chosen before
        }
     // x is already in symbols array
     else return 1; // return 1 means x was chosen before

    case 'X' :
    // check that symbols array did not hold x
     if(symbol[0]!='x' && symbol[1]!='x')
        {
            symbol[playerNumber-1]='x';
            return 0 ; //symbol is not wrong and/or was not chosen before
        }
     // x is already in symbols array
     else return 1; // return 1 means x was chosen before


    case 'o' :
     if(symbol[0]!='o' && symbol[1]!='o')
        {
            symbol[playerNumber-1]='o';
            return 0 ;
        }
     else return 1;

    case 'O' :
     if(symbol[0]!='o' && symbol[1]!='o')
        {
            symbol[playerNumber-1]='o';
            return 0 ;
        }
     else return 1;
    // default the user types any character except (x,o,X,O)
    default: return 1; //symbol is wrong
 }
}

//This function prompt and asks each user about their preferred symbols and saves it in the configArray/symbols[]
void setPlayerConfig(uint8_t *configArray){

  uint8_t i,status;
  for(i=0;i<2;i++){
     printf("\n\n\t\t\tWelcome To X-O Game");
    printf("\n\n\tPLEASE PLAYER %d CHOOSE BETWEEN 'X' OR 'O' SYMBOLS : ",i+1);
    // check on symbol
    status = getPlayerSymbol(i+1,configArray);
    if(status){
        printf("\n\n\tERROR Wrong character or you choose same symbol\n");
        i--; // decrement loop by one and ask again for the right symbol
    }

  }
  for(i=0;i<2;i++){
    printf("\n\tPlayer %d Choses %c Symbol\n",i+1,configArray[i]);
  }

 printf("\n\n\tLet's Begin\n");

}

//This function takes player's number then load his config/symbol, asks him for the position then updates the board
void loadAndUpdate(uint8_t playerNumber){

int pos;
drawBoard(board);
printf("\n\tPlayer %d Enter The Position:  ",playerNumber);
scanf(" %d",&pos);
// check if user choose reserved position or wrong position
while(board[pos-1] == 'x' || board[pos-1] == 'o' || pos<1 || pos>9){
    printf("\n\tYou select a reserved or wrong position \n");
    printf("\n\tPlayer %d Enter The Position:  ",playerNumber);
    scanf(" %d",&pos);
}
// update board with player symbol
updateBoard(board,pos,configArray[playerNumber-1]);
}

//This function checks after each move if there is a win, draw or continue playing.
void getGameState(uint8_t *board, uint8_t *gameState){
    uint8_t i;
    // check on all winning cases manullay
    //Returns 0 in *gamestate for winning
    if(board[0]==board[1]&& board[0]==board[2])      {*gameState=0;*win=board[0];return; }
    else if(board[3]==board[4]&& board[3]==board[5]) {*gameState=0;*win=board[3];return; }
    else if(board[6]==board[7]&& board[6]==board[8]) {*gameState=0;*win=board[6] ;return; }
    else if(board[0]==board[3]&& board[0]==board[6]) {*gameState=0;*win=board[0] ;return; }
    else if(board[1]==board[4]&& board[1]==board[7]) {*gameState=0;*win=board[1] ;return; }
    else if(board[2]==board[5]&& board[2]==board[8]) {*gameState=0;*win=board[2] ;return; }
    else if(board[0]==board[4]&& board[0]==board[8]) {*gameState=0;*win=board[0] ;return; }
    else if(board[2]==board[4]&& board[2]==board[6]) {*gameState=0;*win=board[2] ;return; }

    // check if it draw or continue playing
    else {

        // loop over all board positions to see if there's empty position
        for(i=0;i<boardSize;i++)
        {
            if(board[i]!='x' && board[i]!='o')
             {
                 //Returns 2 to continue
                 *gameState=2 ;
                  return;
             }

        }

        //Returns 1 for a draw
        *gameState=1 ;return;

        }

}


