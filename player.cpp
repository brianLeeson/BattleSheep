/*
 *      Author: Brian Leeson
 */

#include "player.h"
#include "space.h"
#include <vector>


Player::Player(Qt::GlobalColor color, QString imageRef) {
    this->color = color;
    this->imageRef = imageRef;
}

Qt::GlobalColor Player::getColor()
{
    return color;
}

bool Player::getCanMove()
{
    return canMove;
}

void Player::setCanMove(bool canMove)
{
    this->canMove = canMove;
}

std::vector<Space*> Player::getOccupiedSpaces()
{
    return occupiedSpaces;
}

void Player::occupySpace(Space *space, int sheep)
{
    space->setNumSheep(sheep);
    space->setColor(color, imageRef);
    this->occupiedSpaces.push_back(space);
}
