/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** CoreGame
*/

#ifndef COREGAME_HPP_
#define COREGAME_HPP_

#include "Element.hpp"

typedef struct CoreGame_s {
    std::vector<std::string> map;
    arcade::Element map_style;
    std::vector<arcade::Element> allElements;
    bool end;
    bool pause;
    bool restart;
    int score;
} CoreGame_t;

namespace arcade
{
    enum Input
    {
        NOTHING = -2,
        QUIT = -1,
        PAUSE = 0,
        RESTART = 1,
        NEXT_LIB = 2,
        PREV_LIB = 3,
        NEXT_GAME = 4,
        PREV_GAME = 5,
        UP = 6,
        DOWN = 7,
        LEFT = 8,
        RIGHT = 9,
        MENU = 10,
    };
}

#endif /* !COREGAME_HPP_ */