/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** BlueProjectile
*/

#ifndef BLUEPROJECTILE_HPP_
#define BLUEPROJECTILE_HPP_

#include "Projectile.hpp"

class BlueProjectile : virtual public Projectile {
    public:
        BlueProjectile(int _orient, sf::Vector2f pos, int desCap);
        ~BlueProjectile();

        void animation();
        void movement();
        void display(std::shared_ptr<sf::RenderWindow> window);
        int checkKill(std::shared_ptr<Ennemi> ennemi);
        int checkDestruction(std::shared_ptr<Block> block);

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

#endif /* !BLUEPROJECTILE_HPP_ */
