#include "game.h"
#include "board.h"
#include "button.h"
#include "player.h"
#include <QGraphicsTextItem>
#include <QSpinBox>
#include <QtWidgets>
#include <iostream>

Game::Game(QWidget *parent){
    states[0] = (QString) "generating tiles";
    states[1] = (QString) "placing sheep";
    states[2] = (QString) "moving sheep";

    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,700);
    setNumPlayers(2);

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,700);
    setScene(scene);
}

void Game::start(){
    // clear the screen
    scene->clear();
    setFixedSize(200*getNumPlayers(),800);

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
    board->placeSpaces(50,10,2*getNumPlayers(),8);

    //std::vector<Space*> spaces = board->getSpaces();
    //for(auto it = spaces.begin(); it != spaces.end(); ++it) {
        //connect(*it,SIGNAL(clicked()),this,SLOT(close()));
        //players[3]->occupySpace(&(**it), 1);
    //}

    state = 1;
}

void Game::setNumFromSpin(){
    setNumPlayers(playerSpinBox->value());
}

void Game::displayMainMenu(){
    setWindowTitle(tr("Battle Sheep"));

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

    // create the spinbox
    playerSpinBox = new QSpinBox;
    playerSpinBox->setRange(2, 4);
    playerSpinBox->setSingleStep(1);
    playerSpinBox->setValue(2);
    playerSpinBox->setFixedHeight(50);
    playerSpinBox->setFixedWidth(200);
    playerSpinBox->setAlignment(Qt::AlignHCenter);
    connect(playerSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setNumFromSpin()));
    scene->addWidget(playerSpinBox);
}

void Game::addPlayer(Player* player)
{
    players.push_back(player);
}

std::vector<Player *> Game::getPlayers()
{
    return this->players;
}

void Game::setNumPlayers(int num)
{
    this->numPlayers = num;
}

int Game::getNumPlayers()
{
    return this->numPlayers;
}

QString Game::getState()
{
    return states[state];
}

int Game::getWhoseTurn()
{
    return whoseTurn % numPlayers;
}

void Game::incrementTurn()
{
    whoseTurn++;
    if (whoseTurn >= numPlayers) {
        state = 2;
    }
}
