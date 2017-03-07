#ifndef BOARD_H
#define BOARD_H

#include <QList>
#include "space.h"

class Board{
public:
    // constructors
    Board();

    // getters/setters
    std::vector<Space*> getSpaces();

    // public methods
    void placeSpaces(int x, int y, int cols, int rows);

private:
    void createSpaceColumn(int x, int y, int numOfRows);
    std::vector<Space*> spaces;
};

#endif // BOARD_H
