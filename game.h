
#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QString>
#include <map>
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
    std::vector<Player*> getPlayers();
    void setNumPlayers(int num);
    QString getState();
    int getWhoseTurn();
    void incrementTurn();

    // public attributes
    QGraphicsScene* scene;
    Board* board;
public slots:
    void start();
private:
    std::map<int, QString> states;
    int state = 0;
    int whoseTurn = 0;
    int numPlayers;
    std::vector<Player*> players = std::vector<Player*>();
};

#endif // GAME_H
