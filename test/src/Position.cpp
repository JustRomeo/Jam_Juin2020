/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Position
*/

#include "Position.hpp"

arcade::Position::Position()
{
    _x = 0;
    _y = 0;
}

arcade::Position::Position(int x, int y)
{
    _x = x;
    _y = y;
}

arcade::Position::~Position()
{
}

void arcade::Position::setPosition(int x, int y)
{
    _x = x;
    _y = y;
}

int arcade::Position::getPositionX() const
{
    return (_x);
}

int arcade::Position::getPositionY() const
{
    return (_y);
}

void arcade::Position::operator=(const Position &pos)
{
    setPosition(pos.getPositionX(), pos.getPositionY());
}

bool arcade::Position::operator==(const Position &pos)
{
    if (_x == pos.getPositionX() && _y == pos.getPositionY())
        return (true);
    return (false);
}