/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** IProjectile
*/

#ifndef IPROJECTILE_HPP_
#define IPROJECTILE_HPP_

#include "Block.hpp"
#include "Ennemis.hpp"
#include "Exception.hpp"
#include "LibGraphics.hpp"

class IProjectile {
    public:
        enum Type {Blue, Green, Orange, Purple};

        virtual ~IProjectile() = default;
        virtual void animation() = 0;
        virtual int getCurrentCapacity() = 0;
        virtual int checkKill(std::shared_ptr<Ennemi> ennemi) = 0;
        virtual void display(std::shared_ptr<sf::RenderWindow> window) = 0;
        virtual int checkDestruction(vector<shared_ptr<Block>> &mapSFML) = 0;

    protected:
    private:
};

#endif
