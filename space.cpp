#include "space.h"
#include "game.h"
#include <QPointF>
#include <QPolygonF>
#include <QVector>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QString>
#include <iostream>
#include <map>

extern Game* game;

Space::Space(QGraphicsItem *parent) {
    QVector<QPointF> hexPoints;
    hexPoints << QPointF(0,0) << QPointF(1,0) << QPointF(1.5,.87) << QPointF(1, 1.72)
              << QPointF(0,1.72) << QPointF(-.5,.87);

    // scale the points
    int SCALE_BY = 45;
    for (size_t i = 0, n = hexPoints.size(); i < n; ++i){
        hexPoints[i] = hexPoints[i] * SCALE_BY;
    }

    // create a polygon with the scaled points
    QPolygonF hexagon(hexPoints);

    // draw the poly
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    setBrush(brush);
    setPolygon(hexagon);

    //draw the text
    text = new QGraphicsTextItem("",this);
    text->setPos(15,30);

    setAcceptHoverEvents(true);
}

Qt::GlobalColor Space::getColor()
{
    return color;
}

void Space::setColor(Qt::GlobalColor color)
{
    this->color = color;

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    setBrush(brush);
}

int Space::getNumSheep()
{
    return numSheep;
}

void Space::setNumSheep(int numSheep)
{
    this->numSheep = numSheep;
    this->text->setPlainText(QString::number(numSheep));
    if (numSheep > 9) {
        this->text->setPos(12,30);
    }
}

Space* Space::getAdjacent(QString direction) {
    return adjacentSpaces[direction];
}

void Space::setAdjacent(QString direction, Space* space) {
    adjacentSpaces[direction] = space;
}

void Space::mousePressEvent(QGraphicsSceneMouseEvent *event){
    game->setCurSpace(this);
    std::cout << "button was clicked" << std::endl;
    emit clicked();





//    QString gameState = game->getState();
//    Player* currentPlayer = game->getPlayers()[game->getWhoseTurn()];
//    if (gameState == "placing sheep" && this->numSheep == 0) {
//        currentPlayer->occupySpace(this, 16);
//        game->incrementTurn();
//    } else if ((gameState == "moving sheep") && (this->numSheep > 1) && (currentPlayer->getColor() == this->getColor())) {
//        QString directions[6] = { "u", "d", "ul", "ur", "dl", "dr" };
//        Space* cur = this;
//        Space* next;
//        for (int i = 0; i < 6; i++) {
//            next = cur->adjacentSpaces[directions[i]];
//            while (next->getColor() == Qt::green) {
//                cur = next;
//                next = cur->adjacentSpaces[directions[i]];
//            }
//            cur->setColor(Qt::gray);
//        }

//        std::vector<QString> legalDirections;
//        for (auto it = adjacentSpaces.begin(); it != adjacentSpaces.end(); it++) {
//            if (it->second->getColor() == Qt::green) {
//                legalDirections.push_back(it->first);
//            }
//        }

//        Space* nextSpace;
//        QString direction;
//        for (auto it = legalDirections.begin(); it != legalDirections.end(); it++) {
//            nextSpace = this->adjacentSpaces[*it];
//            direction = *it;
//            highlightTarget(nextSpace, direction);
//        }

        //get the target tile
        //ask how many to move
        //move them
        //increment the turn only if we moved them
//    }
}

void Space::highlightTarget(Space* space, QString direction) {
    //check if next is null
    Space* next = space->getAdjacentSpaces().find(direction)->second;
    int count = space->getAdjacentSpaces().count(direction);
    if ((count == 1) && (next->getColor() == Qt::green)) {
        highlightTarget(next, direction);
    } else {
        space->setColor(Qt::gray);
    }
}

void Space::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    // change color to cyan
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);
}

void Space::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    // change color back to the space's color
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    setBrush(brush);
}

std::map<QString, Space*> Space::getAdjacentSpaces()
{
    return adjacentSpaces;
}
