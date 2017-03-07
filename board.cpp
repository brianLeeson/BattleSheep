#include "board.h"
#include "game.h"

extern Game* game;

Board::Board(){

}

std::vector<Space *> Board::getSpaces(){
    return spaces;
}

void Board::placeSpaces(int x, int y, int cols, int rows){
    int X_SHIFT = 82;
    int Y_SHIFT = 41;

    for (size_t i = 0, n = cols; i < n; i++){
        if (i % 2 == 0){ // even column
            Y_SHIFT = 0;
        }
        else{ // odd column
            Y_SHIFT = 41;
        }
        createSpaceColumn(x+X_SHIFT*i,y+Y_SHIFT,rows);
    }
}

void Board::createSpaceColumn(int x, int y, int numOfRows){
    // creates a column of Hexes at the specified location with the specified
    // number of rows
    for (size_t i = 0, n = numOfRows; i < n; i++){
        Space* space = new Space();
        space->setPos(x,y+82*i);
        spaces.push_back(space);
        game->scene->addItem(space);
    }
}
