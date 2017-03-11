#include "space.h"
#include <QPointF>
#include <QPolygonF>
#include <QVector>
#include <QGraphicsTextItem>
#include <QBrush>
#include <iostream>


Space::Space(QGraphicsItem *parent){
    // points needed to draw hexagon: (1,0), (2,0), (3,1), (2,2), (1,2), (0,1)
    QVector<QPointF> hexPoints;
    hexPoints << QPointF(1,0) << QPointF(2,0) << QPointF(3,1) << QPointF(2,2)
              << QPointF(1,2) << QPointF(0,1);

    // scale the points
    int SCALE_BY = 40;
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
}

void Space::mousePressEvent(QGraphicsSceneMouseEvent *event){
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
