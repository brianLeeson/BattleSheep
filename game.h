#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
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
    void setNumPlayers(int num);
    int getNumPlayers();

    // public attributes
    QGraphicsScene* scene;
    Board* board;
    QString whoseTurn;
public slots:
    void start();
    void setNumFromSpin();
private:
    int numPlayers;
    QSpinBox *playerSpinBox;
    std::vector<Player*> players = std::vector<Player*>();
};

#endif // GAME_H
