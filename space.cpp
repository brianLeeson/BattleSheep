#include "space.h"
#include <QPointF>
#include <QPolygonF>
#include <QVector>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QString>
#include <iostream>


Space::Space(QGraphicsItem *parent) {
    // points needed to draw hexagon: (1,0), (2.5,0), (3,1), (2.5,2), (1,2), (0,1)
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
    //setPolygon(hexagon);

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

void Space::mousePressEvent(QGraphicsSceneMouseEvent *event){
    setNumSheep(numSheep+1);
    emit clicked();
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
