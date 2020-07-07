/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** Time
*/

#include "Time.hpp"

Time::Time()
{
    clock.restart();
}

Time::~Time()
{
}

int Time::getTimeDiff(float timeDiff)
{
    sf::Time time;
    float seconds = 0;

    time = clock.getElapsedTime();
    seconds = time.asMicroseconds() / 1000000.0;
    if (seconds > timeDiff) {
        clock.restart();
        return (1);
    }
    return (0);
}

void Time::restartClock()
{
    clock.restart();
}