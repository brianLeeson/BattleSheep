/*
 *      Author: Brian Leeson
 */

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <string>
#include <vector>

class Space: {
	public:
        	Space();
        	virtual ~Space();
		
		std::string getColor();
		void setColor(std::string color);
		
		bool getCanMove();
		void setCanMove(bool numSheep);
		
		std::vector<Space*> getoccupiedSpaces();
		void setOccupiedSpaces(std::vector); //don't use this when a player moves

		void occupySpace(Space &space);

	protected:
		std::string color = "Green";
		bool canMove = false;
		std::vector<Space*> occupiedSpaces;
		
		
};

#endif
