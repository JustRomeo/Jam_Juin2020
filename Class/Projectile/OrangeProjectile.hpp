/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
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
        int checkKill(std::shared_ptr<Runner> ennemi);
        int checkDestruction(vector<shared_ptr<Block>> &mapSFML);

    protected:
    private:
        int orient;
        int posRect;
        sf::Sprite sprite;
        sf::Vector2f move;
        IProjectile::Type type;
        std::vector<float> shootTime;
        std::vector<sf::IntRect> shootRect;
        std::vector<sf::Vector2f> shootMove;
        std::shared_ptr<sf::Texture> texture;
};

#endif
