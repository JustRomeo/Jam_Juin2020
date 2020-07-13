/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** Projectile
*/

#ifndef PROJECTILE_HPP_
#define PROJECTILE_HPP_

#include "LibGraphics.hpp"
#include "Exception.hpp"
#include "Ennemis.hpp"
#include "IProjectile.hpp"

class Projectile : public IProjectile{
    public:
        Projectile(int desCap);
        ~Projectile();
        int getTimeMov(float diff);
        int getTimeAnim(float diff);
        int getCurrentCapacity();

    protected:
        // std::shared_ptr<sf::Texture> texture;
        // sf::Sprite sprite;
        // sf::Vector2f move;
        sf::Clock move_clock;
        sf::Clock anim_clock;
        // IProjectile::Type type;
        // std::vector<sf::IntRect> shootRect1;
        // std::vector<float> shoot1Time;
        // std::vector<sf::Vector2f> shoot1Move;
        // int posRect;
        int destructionCapacity;
        // int orient;
    private:
};

#endif /* !PROJECTILE_HPP_ */
