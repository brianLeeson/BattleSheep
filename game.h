
#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "board.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    // constructors
    Game(QWidget* parent=NULL);

    // public methods
    void displayMainMenu();

    // public attributes
    QGraphicsScene* scene;
    Board* board;
    QString whoseTurn;
public slots:
    void start();
};

#endif // GAME_H
