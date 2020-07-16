/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** OrangeProjectile
*/

#ifndef ORANGEPROJECTILE_HPP_
#define ORANGEPROJECTILE_HPP_

#include "Projectile.hpp"

class OrangeProjectile : virtual public Projectile {
    public:
        OrangeProjectile(int _orient, sf::Vector2f pos, int desCap);
        ~OrangeProjectile();

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

#endif /* !ORANGEPROJECTILE_HPP_ */
