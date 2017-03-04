/*
 *      Author: Brian Leeson
 */


#ifndef SPACE_HPP_
#define SPACE_HPP_

#include <string>

class Space: {
	public:
        	Space();
        	virtual ~Space();
		std::string getColor();
		void setColor(std::string color);
		int getNumSheep();
		void setNumSheep(int numSheep);
		
		Space* getTopLeft();
		void setTopLeft(Space &space);
		Space* getTopRight();
		void setTopRight(Space &space);
		Space* getBotLeft();
		void setBotLeft(Space &space);
		Space* getBotRight();
		void setBotRight(Space &space);
		Space* getLeft();
		void setLeft(Space &space);
		Space* getRight();
		void setRight(Space &space);

	protected:
		std::string color = "Green";
		int numSheep = 0;
		Space* topLeft = NULL;
		Space* topRight = NULL;
		Space* botLeft = NULL;
		Space* botRight = NULL;
		Space* Left = NULL;
		Space* Right = NULL;
};

#endif
