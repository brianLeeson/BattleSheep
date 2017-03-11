
#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "board.h"
#include "player.h"

class Game: public QGraphicsView{
    Q_OBJECT
public:
    // constructors
    Game(QWidget* parent=NULL);

    // public methods
    void displayMainMenu();
    void addPlayer(Player* player);
    void setNumPlayers(int num);

    // public attributes
    QGraphicsScene* scene;
    Board* board;
    QString whoseTurn;
public slots:
    void start();
private:
    int numPlayers;
    std::vector<Player*> players = std::vector<Player*>();
};

#endif // GAME_H
