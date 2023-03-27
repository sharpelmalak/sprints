#ifndef X_O_H_INCLUDED
#define X_O_H_INCLUDED

void drawBoard(uint8_t*board);
void updateBoard (uint8_t *board, uint8_t position, uint8_t value);
void setPlayerConfig(uint8_t *configArray);
uint8_t getPlayerSymbol(uint8_t playerNumber, uint8_t * symbol);
void loadAndUpdate(uint8_t playerNumber);
void getGameState(uint8_t *board, uint8_t *gameState);

#endif // X_O_H_INCLUDED
