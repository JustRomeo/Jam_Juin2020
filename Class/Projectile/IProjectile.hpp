/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** IProjectile
*/

#ifndef IPROJECTILE_HPP_
#define IPROJECTILE_HPP_

#include "LibGraphics.hpp"
#include "Exception.hpp"
#include "Block.hpp"
#include "Ennemis.hpp"

class IProjectile {
    public:
        enum Type {YELLOW, BLUE, PURPLE, CHARGED};
        virtual ~IProjectile() = default;
        virtual void animation() = 0;
        virtual int getCurrentCapacity() = 0;
        virtual void display(std::shared_ptr<sf::RenderWindow> window) = 0;
        virtual int checkKill(std::shared_ptr<Ennemi> ennemi) = 0;
        virtual int checkDestruction(vector<shared_ptr<Block>> &mapSFML) = 0;

    protected:
    private:
};

#endif /* !IPROJECTILE_HPP_ */
