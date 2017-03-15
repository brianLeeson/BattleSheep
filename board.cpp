#include "board.h"
#include "game.h"
#include <iostream>

extern Game* game;

Board::Board(){

}

std::vector<Space*> Board::getSpaces(){
    return spaces;
}

void Board::placeSpaces(int x, int y, int cols, int rows){
    int X_SHIFT = 70;
    int Y_SHIFT = 41;

    for (size_t i = 0, n = cols; i < n; i++){
        if (i % 2 == 0) { // even column
            Y_SHIFT = 0;
        } else { // odd column
            Y_SHIFT = 41;
        }
        createSpaceColumn(x+X_SHIFT*i,y+Y_SHIFT,rows);

        // connect spaces diagonally
        if (i != 0) {
            if (i%2 == 0) { // even column
                for (size_t j = 0; j < rows; j++) {
                    spaces[(rows*i)+j]->setAdjacent("dl", spaces[(rows*(i-1))+j]);
                    spaces[(rows*(i-1))+j]->setAdjacent("ur", spaces[(rows*i)+j]);
                    if (j != 0) {
                        spaces[(rows*i)+j]->setAdjacent("ul", spaces[(rows*(i-1))+j-1]);
                        spaces[(rows*(i-1))+j-1]->setAdjacent("dr", spaces[(rows*i)+j]);
                    }
                }
            } else { // odd column
                for (size_t j = 0, k = rows; j < k; j++) {
                    spaces[(rows*i)+j]->setAdjacent("ul", spaces[(rows*(i-1))+j]);
                    spaces[(rows*(i-1))+j]->setAdjacent("dr", spaces[(rows*i)+j]);
                    if (j != (rows-1)) {
                        spaces[(rows*i)+j]->setAdjacent("dl", spaces[(rows*(i-1))+j+1]);
                        spaces[(rows*(i-1))+j+1]->setAdjacent("ur", spaces[(rows*i)+j]);
                    }
                }
            }
        }
    }
}

std::vector<Space*> Board::createSpaceColumn(int x, int y, int numOfRows){
    std::vector<Space*> column;
    Space* space;
    // creates a column of Hexes at the specified location with the specified
    // number of rows
    for (size_t i = 0, n = numOfRows; i < n; i++){
        space = new Space();
        space->setPos(x,y+82*i);
        column.push_back(space);
        spaces.push_back(space);
        game->scene->addItem(space);

        // connect Spaces top to bottom
        if (i != 0 ) {
            column[i-1]->setAdjacent("d", column[i]);
            column[i]->setAdjacent("u", column[i-1]);
        }
    }

    return column;
}
