/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** ProjectileFactory
*/

#ifndef PROJECTILEFACTORY_HPP_
#define PROJECTILEFACTORY_HPP_

#include "PurpleProjectile.hpp"
#include "BlueProjectile.hpp"
#include "OrangeProjectile.hpp"
#include "GreenProjectile.hpp"

class ProjectileFactory {
    public:
        ProjectileFactory();
        ~ProjectileFactory();
        std::shared_ptr<IProjectile> createComponent(int _type, int _orient, sf::Vector2f pos, int desCap);
    protected:
    private:
};

#endif /* !PROJECTILEFACTORY_HPP_ */
