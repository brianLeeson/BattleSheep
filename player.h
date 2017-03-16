/*
 *      Author: Brian Leeson
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "space.h"
#include <vector>
#include <QObject>

class Player:public QObject {
    Q_OBJECT
	public:
        Player(Qt::GlobalColor color, QString imageRef);

        Qt::GlobalColor getColor();
		void setColor(Qt::GlobalColor color);
		
		bool getCanMove();
		void setCanMove(bool canMove);
		
        std::vector<Space*> getOccupiedSpaces();

        void occupySpace(Space *space, int sheep);

	protected:
        Qt::GlobalColor color;
        QString imageRef;
        bool canMove = true;
        std::vector<Space*> occupiedSpaces;
};

#endif // PLAYER_H
