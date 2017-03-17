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
    text->setPos(15,55);
    text->setDefaultTextColor(Qt::black);

    setAcceptHoverEvents(true);
}

Qt::GlobalColor Space::getColor()
{
    return color;
}

void Space::setColor(Qt::GlobalColor color, QString imageRef)
{
    this->color = color;

    QGraphicsPixmapItem *pm = game->scene->addPixmap(QPixmap(imageRef).scaledToWidth(45));
    pm->setPos(xpos, ypos+10);

    if (color == Qt::black) { text->setDefaultTextColor(Qt::white); }

    if (imageRef == "") {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(color);
        setBrush(brush);
    }
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
        this->text->setPos(12,55);
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
}

void Space::highlightTarget(Space* space, QString direction) {
    //check if next is null
    Space* next = space->getAdjacentSpaces().find(direction)->second;
    int count = space->getAdjacentSpaces().count(direction);
    if ((count == 1) && (next->getColor() == Qt::green)) {
        highlightTarget(next, direction);
    } else {
        space->setColor(Qt::gray, "");
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

int Space::getYpos() const
{
    return ypos;
}

void Space::setYpos(int value)
{
    ypos = value;
}

int Space::getXpos() const
{
    return xpos;
}

void Space::setXpos(int value)
{
    xpos = value;
}
