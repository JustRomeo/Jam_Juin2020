/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** Projectile
*/

#include "Projectile.hpp"

Projectile::Projectile(int desCap)
{
    move_clock.restart();
    anim_clock.restart();
    destructionCapacity = desCap;
}

Projectile::~Projectile()
{
}

int Projectile::getTimeAnim(float diff)
{
    sf::Time time;
    float seconds = 0;

    time = anim_clock.getElapsedTime();
    seconds = time.asMicroseconds() / 1000000.0;
    if (seconds > diff) {
        anim_clock.restart();
        return (1);
    }
    return (0);
}

int Projectile::getTimeMov(float diff)
{
    sf::Time time;
    float seconds = 0;

    time = move_clock.getElapsedTime();
    seconds = time.asMicroseconds() / 1000000.0;
    if (seconds > diff) {
        move_clock.restart();
        return (1);
    }
    return (0);
}

int Projectile::getCurrentCapacity()
{
    return (destructionCapacity);
}
