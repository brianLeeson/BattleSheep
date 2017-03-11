/*
 *      Author: Brian Leeson
 */

#ifndef SPACE_H
#define SPACE_H

#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>

class Space:public QObject, public QGraphicsPolygonItem {
    Q_OBJECT
	public:
        Space(QGraphicsItem* parent=NULL);

		Qt::GlobalColor getColor();
        void setColor(Qt::GlobalColor color);

		int getNumSheep();
		void setNumSheep(int numSheep);
		
		Space* getTopLeft();
        void setTopLeft(Space *space);
		Space* getTopRight();
        void setTopRight(Space *space);
		Space* getBotLeft();
        void setBotLeft(Space *space);
		Space* getBotRight();
        void setBotRight(Space *space);
		Space* getLeft();
        void setLeft(Space *space);
		Space* getRight();
        void setRight(Space *space);

        // (events)
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    signals:
         void clicked();
	private:
		Qt::GlobalColor color = Qt::green;
        int numSheep = 16;
		Space* topLeft = NULL;
		Space* topRight = NULL;
		Space* botLeft = NULL;
		Space* botRight = NULL;
		Space* Left = NULL;
		Space* Right = NULL;
};

#endif // SPACE_H
