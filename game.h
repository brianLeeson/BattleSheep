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

    Space* getCurSpace();
    void setCurSpace(Space *value);

    void runGame();
    void runRound0();
    void endGame();

    void disconnectSpaces();
    std::vector<QString> getLegalDirections(Space *origin);
    Space* highlightTarget(Space *space, QString direction);

    void migrate();

    // public attributes
    QGraphicsScene* scene;
    Board* board;

public slots:
    void start();
    void setNumFromSpin();
    void occupySpace();
    void beginMove();
    void endMove();

private:
    std::map<int, QString> states;
    int state = 0;
    int whoseTurn = 0;
    int round = 1;
    int numPlayers;
    QSpinBox *playerSpinBox;
    std::vector<Player*> players = std::vector<Player*>();
    Space* curSpace;
    Space* prevSpace;
    int sheepToLeave;
    int sheepToStay;
};

#endif // GAME_H
