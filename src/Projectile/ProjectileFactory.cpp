/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** ProjectileFactory
*/

#include "ProjectileFactory.hpp"

ProjectileFactory::ProjectileFactory() {}

ProjectileFactory::~ProjectileFactory() {}

std::shared_ptr<IProjectile> ProjectileFactory::createComponent(int _type, int _orient, sf::Vector2f pos, int desCap) {
    switch (_type) {
        case 1: return (std::make_shared<OrangeProjectile>(_orient, pos, desCap));
        case 2: return (std::make_shared<BlueProjectile>(_orient, pos, desCap));
        case 3: return (std::make_shared<PurpleProjectile>(_orient, pos, desCap));
        case 4: return (std::make_shared<GreenProjectile>(_orient, pos, desCap));
        default: break;
    }
    return NULL;
}
