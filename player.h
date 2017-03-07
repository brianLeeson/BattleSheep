/*
 *      Author: Brian Leeson
 */

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

class Player {
	public:
        Player();

        Qt::GlobalColor getColor();
		void setColor(Qt::GlobalColor color);
		
		bool getCanMove();
		void setCanMove(bool canMove);
		
		std::vector<Space*> getOccupiedSpaces();
		void setOccupiedSpaces(std::vector); //don't use this when a player moves

		void occupySpace(Space &space);

	protected:
		Qt::GlobalColor color = Qt::green;
		bool canMove = false;
		std::vector<Space*> occupiedSpaces;
		
};

#endif // PLAYER_H
