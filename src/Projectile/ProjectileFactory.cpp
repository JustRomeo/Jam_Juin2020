/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** ProjectileFactory
*/

#include "ProjectileFactory.hpp"

ProjectileFactory::ProjectileFactory()
{
}

ProjectileFactory::~ProjectileFactory()
{
}

std::shared_ptr<IProjectile> ProjectileFactory::createComponent(int _type, int _orient, sf::Vector2f pos, int desCap)
{
    if (_type == 1) {
        return (std::make_shared<OrangeProjectile>(_orient, pos, desCap));
    }
    if (_type == 2) {
        return (std::make_shared<BlueProjectile>(_orient, pos, desCap));
    }
    if (_type == 3) {
        return (std::make_shared<PurpleProjectile>(_orient, pos, desCap));
    }
    if (_type == 4) {
        return (std::make_shared<GreenProjectile>(_orient, pos, desCap));
    }
    return (NULL);
}
