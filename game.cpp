#include "game.h"
#include "board.h"
#include "button.h"
#include "player.h"
#include <QGraphicsTextItem>

Game::Game(QWidget *parent){
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,768);
    setScene(scene);
}

void Game::start(){
    // clear the screen
    scene->clear();

    Qt::GlobalColor playerColors[4] = { Qt::red, Qt::blue, Qt::yellow, Qt::magenta };

    Player* newPlayer;
    Qt::GlobalColor playerColor;
    for (int i = 0; i < numPlayers; i++) {
        playerColor = playerColors[i];
        newPlayer = new Player(playerColor);
        players.push_back(newPlayer);
    }

    // test code TODO remove
    board = new Board();
    board->placeSpaces(100,100,5,5);
    std::vector<Space*> spaces = board->getSpaces();
    for(auto it = spaces.begin(); it != spaces.end(); ++it) {
        //connect(*it,SIGNAL(clicked()),this,SLOT(close()));
        players[3]->occupySpace(&(**it), 1);
    }
}

void Game::displayMainMenu(){
    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Battle Sheep"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the play button
    Button* playButton = new Button(QString("Play"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 275;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);

    // create the quit button
    Button* quitButton = new Button(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 350;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);

    setNumPlayers(4);
}

void Game::addPlayer(Player* player)
{
    players.push_back(player);
}

void Game::setNumPlayers(int num)
{
    this->numPlayers = num;
}
