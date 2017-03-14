#include "game.h"
#include "board.h"
#include "button.h"
#include "player.h"
#include <QGraphicsTextItem>
#include <QSpinBox>
#include <QtWidgets>
#include <iostream>

Game::Game(QWidget *parent){
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,500);
    setNumPlayers(2);

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,500);
    setScene(scene);

    //QHBoxLayout *layout = new QHBoxLayout;

}

void Game::start(){
    // clear the screen
    scene->clear();

    //set numPlayer

    //initializing player
    Player *redPlayer = new Player(Qt::red);
    addPlayer(redPlayer);

    // test code TODO remove
    board = new Board();
    board->placeSpaces(100,100,5,5);
    std::vector<Space*> spaces = board->getSpaces();
    for(auto it = spaces.begin(); it != spaces.end(); ++it) {
        connect(*it,SIGNAL(clicked()),this,SLOT(close()));
        redPlayer->occupySpace(&(**it), 16);
    }
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

    /* create the spinbox */
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

void Game::setNumPlayers(int num)
{
    this->numPlayers = num;
}

int Game::getNumPlayers()
{
    return this->numPlayers;
}
