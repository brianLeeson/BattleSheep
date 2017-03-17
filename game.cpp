#include "game.h"
#include "board.h"
#include "button.h"
#include "player.h"
//#include "spinbox.h"
#include <QGraphicsTextItem>
#include <QSpinBox>
#include <QtWidgets>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <iostream>
#include <QLabel>
#include <QPushButton>

Game::Game(QWidget *parent){
    states[0] = (QString) "generating tiles";
    states[1] = (QString) "placing sheep";
    states[2] = (QString) "moving sheep";
    states[3] = (QString) "ending game";

    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,700);

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,700);
    setScene(scene);

    setNumPlayers(2);

    colorMap[Qt::red] = "Red";
    colorMap[Qt::blue] = "Blue";
    colorMap[Qt::black] = "Black";
    colorMap[Qt::white] = "White";
}

void Game::start(){
    // clear the screen
    scene->clear();
    setFixedSize(1024,1000);
    delete playerLabel;
    delete playerSpinBox;
    delete this->layout();

    delete layout();

    Qt::GlobalColor playerColors[4] = { Qt::red, Qt::blue, Qt::black, Qt::white };
    QString playerImages[4] = { ":/assets/red.png", ":/assets/blue.png", ":/assets/black.png", ":/assets/white.png" };

    Player* newPlayer;
    Qt::GlobalColor playerColor;
    QString playerImage;
    for (int i = 0; i < numPlayers; i++) {
        playerColor = playerColors[i];
        playerImage = playerImages[i];
        newPlayer = new Player(playerColor, playerImage);
        players.push_back(newPlayer);
    }

    // Generate a board
    board = new Board();
    board->placeSpaces(512-70*getNumPlayers(),0,2*getNumPlayers(),8);
    state = 1;

    //current player label
    turnLabel = new QLabel(QString("Turn: Red"));
    turnLabel->setFixedHeight(20);
    turnLabel->setFixedWidth(200);

    //winner label
    winnerLabel = new QLabel(QString("Winner: no one"));
    winnerLabel->setFixedHeight(20);
    winnerLabel->setFixedWidth(200);

    QHBoxLayout *layout = new QHBoxLayout;
    QGroupBox *displayGroup = new QGroupBox(tr(""));
    QHBoxLayout *displayLayout = new QHBoxLayout;
    displayLayout->addWidget(turnLabel);
    //displayLayout->addWidget(winnerLabel);
    displayGroup->setLayout(displayLayout);
    layout->addWidget(displayGroup);
    layout->setAlignment(Qt::AlignTop);
    setLayout(layout);

    runRound0();
}

void Game::runRound0() {
    disconnectSpaces();

    std::vector<Space*> spaces = board->getSpaces();
    for(auto it = spaces.begin(); it != spaces.end(); ++it) {
        if ((*it)->getColor() == Qt::green) {
            connect(*it,SIGNAL(clicked()),this,SLOT(occupySpace()));
        }
    }
}

void Game::runGame() {
    std::cout << "It is Round " << round << "." << std::endl;
    std::cout << "It is " << players[whoseTurn]->getColor() << "'s turn." << std::endl;

    Player* curPlayer = players[whoseTurn];


    std::vector<Space*> legalStarts;
    std::vector<Space*> occupiedSpaces = curPlayer->getOccupiedSpaces();

    for (auto it = occupiedSpaces.begin(); it != occupiedSpaces.end(); it++) {
        Space* space = *it;
        std::vector<QString> legalDirections = getLegalDirections(space);
        if ((space->getNumSheep() > 1) && (!legalDirections.empty())) {
            legalStarts.push_back(space);
        }
    }

    if (legalStarts.size() == 0) {
        std::cout << players[whoseTurn]->getColor() << " cannot move." << std::endl;
        incrementTurn();
    } else {
        std::cout << "Now to connect legal starts." << std::endl;

        disconnectSpaces();
        for (auto it = legalStarts.begin(); it != legalStarts.end(); it++) {
            connect(*it,SIGNAL(clicked()),this,SLOT(beginMove()));
        }
    }
}

void Game::beginMove() {
    std::cout << "Entering beginMove." << std::endl;

    disconnectSpaces();

    prevSpace = curSpace;
    std::vector<QString> legalDirections = getLegalDirections(curSpace);
    Space* nextSpace;
    QString direction;
    for (auto it = legalDirections.begin(); it != legalDirections.end(); it++) {
        nextSpace = curSpace->getAdjacentSpaces()[*it];
        direction = *it;
        nextSpace = highlightTarget(nextSpace, direction);
        connect(nextSpace,SIGNAL(clicked()),this,SLOT(endMove()));
    }
    //prompt user for values for migration
    movePrompt();
}

void Game::endMove() {
    std::cout << "Entering endMove." << std::endl;

    migrate();

    std::vector<Space*> spaces = board->getSpaces();
    for (auto it = spaces.begin(); it != spaces.end(); it++) {
        Space* space = *it;
        if (space->getColor() == Qt::gray) {
            space->setColor(Qt::green, "");
        }
    }

    incrementTurn();
}

void Game::endGame() {
    std::cout << "The game is now over." << std::endl;
    disconnectSpaces();

    std::map<Qt::GlobalColor, int> scores;
    std::vector<Space*> spaces = board->getSpaces();
    for (auto it = spaces.begin(); it != spaces.end(); it++) {
         if ((*it)->getColor() != Qt::green) {
             scores[(*it)->getColor()] += 1;
         }
    }

    int max = 0;
    bool hasTie;
    Qt::GlobalColor winner;
    for (auto it = scores.begin(); it != scores.end(); it++) {
        if ((*it).second > max) {
            hasTie = false;
            max = (*it).second;
            winner = (*it).first;
        } else if ((*it).second == max) {
            hasTie = true;
        }
    }

    int curTieBreakerMax = 0;
    int bfsResult = 0;
    int curTieWinner;
    Player* curPlayer;
    std::vector<Space*> occSpaces;
    for (int i = 0; i < numPlayers; i++) {
        curPlayer = players[i];
        occSpaces = curPlayer->getOccupiedSpaces();
        for (auto it = occSpaces.begin(); it != occSpaces.end(); it++) {
	    BFS((*it), &bfsResult);            
            if (bfsResult > curTieBreakerMax) {
                curTieBreakerMax = bfsResult;
                curTieWinner = i;
            }
            bfsResult = 0;
        }
    }

    char* colors[4] = { "Red", "Blue", "Black", "White" };
    QString winnerColor;
    if (winner == Qt::red) {
        winnerColor = "Red";
    }
    if (winner == Qt::blue) {
        winnerColor = "Blue";
    }
    if (winner == Qt::black) {
        winnerColor = "Black";
    }
    if (winner == Qt::white) {
        winnerColor = "White";
    }

    QString winText = "Winner: ";
    if (hasTie) {
        winnerColor = colors[curTieWinner];
    } 

    turnLabel->setText(winText + winnerColor);
}

void Game::BFS(Space* start, int* sum) {
    start->visited = true;
    (*sum) += 1;

    std::map<QString, Space*> adjacentSpaces = start->getAdjacentSpaces();
    for (auto it = adjacentSpaces.begin(); it != adjacentSpaces.end(); it++) {
        if (((*it).second->getColor() == start->getColor()) && !((*it).second->visited)) {
            Game::BFS((*it).second, sum);
        }
    }
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

    // create label
    playerLabel = new QLabel(QString("Number Of Players:"));
    playerLabel->setFixedHeight(50);
    playerLabel->setFixedWidth(200);
    playerLabel->setAlignment(Qt::AlignHCenter);

    // create the spinbox
    playerSpinBox = new QSpinBox;
    playerSpinBox->setRange(2, 4);
    playerSpinBox->setSingleStep(1);
    playerSpinBox->setValue(2);
    playerSpinBox->setFixedHeight(50);
    playerSpinBox->setFixedWidth(200);
    playerSpinBox->setAlignment(Qt::AlignHCenter);
    connect(playerSpinBox, SIGNAL(valueChanged(int)), this, SLOT(setNumFromSpin()));

    //label and spinbox layout
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(playerLabel);
    layout->addWidget(playerSpinBox);
    layout->setAlignment(Qt::AlignHCenter);
    setLayout(layout);
    this->layout()->setAlignment(Qt::AlignBottom);
}

// Helper Functions

void Game::occupySpace() {
    players[whoseTurn]->occupySpace(curSpace, 16);
    incrementTurn();
}

Space* Game::highlightTarget(Space* space, QString direction) {
    //check if next is null
    Space* next = space->getAdjacentSpaces().find(direction)->second;
    int count = space->getAdjacentSpaces().count(direction);
    if ((count == 1) && (next->getColor() == Qt::green)) {
        return highlightTarget(next, direction);
    } else {
        space->setColor(Qt::gray, "");
        return space;
    }
}

void Game::movePrompt(){
    //set default values in case prompt ignored.
    this->sheepToStay = 1;
    this->sheepToLeave = prevSpace->getNumSheep() - 1;

    //prompt user in popup
    popup = new QWidget();

    // layout and groups
    QHBoxLayout *layout = new QHBoxLayout;
    QGroupBox *migrateGroup = new QGroupBox(tr("Migrate"));
    QVBoxLayout *migrateLayout = new QVBoxLayout;

    // create label
    QLabel* migrateLabel = new QLabel(QString("Sheep to Migrate:"));
    migrateLabel->setFixedHeight(50);
    migrateLabel->setFixedWidth(200);
    migrateLabel->setAlignment(Qt::AlignHCenter);

    // create spinbox
    migrateSpinbox = new QSpinBox;
    migrateSpinbox->setRange(1, prevSpace->getNumSheep()-1);
    migrateSpinbox->setSingleStep(1);
    migrateSpinbox->setValue(prevSpace->getNumSheep()-1);
    migrateSpinbox->setFixedHeight(50);
    migrateSpinbox->setFixedWidth(200);
    migrateSpinbox->setAlignment(Qt::AlignHCenter);
    connect(migrateSpinbox, SIGNAL(valueChanged(int)), this, SLOT(setMigrateNums()));

    migrateClose = new QPushButton("Close Window");
    connect(migrateClose, SIGNAL(clicked()), popup, SLOT(close()));

    migrateLayout->addWidget(migrateLabel);
    migrateLayout->addWidget(migrateSpinbox);
    migrateLayout->addWidget(migrateClose);

    //set layout
    migrateGroup->setLayout(migrateLayout);
    layout->addWidget(migrateGroup);

    popup->setLayout(layout);
    popup->show();
}

void Game::migrate(){
    //keep and move sheep
    popup->close();
    prevSpace->setNumSheep(sheepToStay);
    players[whoseTurn]->occupySpace(curSpace, sheepToLeave);
}

std::vector<QString> Game::getLegalDirections(Space* origin) {
    std::vector<QString> legalDirections;
    std::map<QString, Space*> adjacentSpaces = origin->getAdjacentSpaces();
    for (auto it = adjacentSpaces.begin(); it != adjacentSpaces.end(); it++) {
        if (it->second->getColor() == Qt::green) {
            legalDirections.push_back(it->first);
        }
    }
    return legalDirections;
}

void Game::disconnectSpaces() {
    std::vector<Space*> spaces = board->getSpaces();
    for(auto it = spaces.begin(); it != spaces.end(); ++it) {
        disconnect(*it, 0, 0, 0);
    }
}

void Game::incrementTurn(){
    whoseTurn = (whoseTurn + 1) % numPlayers;

    QString turn = "Turn: ";
    char* player = (*colorMap.find(players[whoseTurn]->getColor())).second;
    turnLabel->setText(turn + player);

    if (state == 1) {
        if (whoseTurn == 0) {
            state++;
            runGame();
        } else {
            runRound0();
        }
    } else if (state == 2) {
        if (whoseTurn == 0) {
            round++;
        }
        if (round < 16) {
            runGame();
        } else {
            endGame();
        }
    }
}

// Getter and Setter Functions

void Game::addPlayer(Player* player)
{
    players.push_back(player);
}

std::vector<Player *> Game::getPlayers()
{
    return this->players;
}

void Game::setNumFromSpin(){
    setNumPlayers(playerSpinBox->value());
}

void Game::setMigrateNums(){
    int migrating = migrateSpinbox->value();
    sheepToLeave = migrating;
    sheepToStay = prevSpace->getNumSheep() - migrating;
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

Space *Game::getCurSpace()
{
    return curSpace;
}

void Game::setCurSpace(Space *value)
{
    curSpace = value;
}

int Game::getWhoseTurn()
{
    return whoseTurn % numPlayers;
}


