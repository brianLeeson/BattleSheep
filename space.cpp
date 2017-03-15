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

void Space::setColor(Qt::GlobalColor color)
{
    this->color = color;

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    setBrush(brush);
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
    QString gameState = game->getState();
    Player* currentPlayer = game->getPlayers()[game->getWhoseTurn()];
    if (gameState == "placing sheep" && this->numSheep == 0) {
        currentPlayer->occupySpace(this, 16);

        std::map<QString, Space*>::iterator it;

        // When Round 0 happens, all adjacent Spaces are painted with original color.
        for(it = adjacentSpaces.begin(); it != adjacentSpaces.end(); it++) {
            it->second->setColor(currentPlayer->getColor());
        }

        game->incrementTurn();
    }
    //setNumSheep(numSheep+1);
    //getAdjacent("u")->setNumSheep(10);
    //emit clicked();
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
