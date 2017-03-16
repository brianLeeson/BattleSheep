/*
 *      Author: Brian Leeson
 */

#ifndef SPACE_H
#define SPACE_H

#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>
#include <map>

class Space:public QObject, public QGraphicsPolygonItem {
    Q_OBJECT
	public:
        Space(QGraphicsItem* parent=NULL);

		Qt::GlobalColor getColor();
        void setColor(Qt::GlobalColor color, QString imageRef);

		int getNumSheep();
		void setNumSheep(int numSheep);
		
        Space* getAdjacent(QString direction);
        void setAdjacent(QString direction, Space* space);

        void highlightTarget(Space* space, QString direction);

        // (events)
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
        std::map<QString, Space*> getAdjacentSpaces();

        int getYpos() const;
        void setYpos(int value);

        int getXpos() const;
        void setXpos(int value);

signals:
        void clicked();
private:
        int xpos;
        int ypos;
        QGraphicsTextItem* text;
        QGraphicsPixmapItem* image;
		Qt::GlobalColor color = Qt::green;
        int numSheep = 0;
        std::map<QString, Space*> adjacentSpaces;
};

#endif // SPACE_H
