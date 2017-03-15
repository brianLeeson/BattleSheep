#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QString>
#include <map>
#include "board.h"
#include "player.h"
#include <QSpinBox>

class QGroupBox;

class Game: public QGraphicsView{
    Q_OBJECT
public:
    // constructors
    Game(QWidget* parent=NULL);

    // public methods
    void displayMainMenu();
    void addPlayer(Player* player);
    std::vector<Player*> getPlayers();

    QString getState();

    int getWhoseTurn();
    void incrementTurn();

    void setNumPlayers(int num);
    int getNumPlayers();

    // public attributes
    QGraphicsScene* scene;
    Board* board;
public slots:
    void start();
    void setNumFromSpin();
private:
    std::map<int, QString> states;
    int state = 0;
    int whoseTurn = 0;
    int numPlayers;
    QSpinBox *playerSpinBox;
    std::vector<Player*> players = std::vector<Player*>();
};

#endif // GAME_H
