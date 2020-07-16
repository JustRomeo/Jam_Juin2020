/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** GreenProjectile
*/

#ifndef GREENPROJECTILE_HPP_
#define GREENPROJECTILE_HPP_

#include "Projectile.hpp"

class GreenProjectile : virtual public Projectile {
    public:
        GreenProjectile(int _orient, sf::Vector2f pos, int desCap);
        ~GreenProjectile();

    void animation();
        void movement();
        void display(std::shared_ptr<sf::RenderWindow> window);
        int checkKill(std::shared_ptr<Ennemi> ennemi);
        int checkDestruction(vector<shared_ptr<Block>> &mapSFML);

    protected:
    private:
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;
        sf::Vector2f move;
        IProjectile::Type type;
        std::vector<sf::IntRect> shootRect;
        std::vector<float> shootTime;
        std::vector<sf::Vector2f> shootMove;
        int posRect;
        int orient;
};

#endif /* !GREENPROJECTILE_HPP_ */
