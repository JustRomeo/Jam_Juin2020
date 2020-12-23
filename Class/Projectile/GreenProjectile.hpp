/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** GreenProjectile
*/

#ifndef GREENPROJECTILE_HPP_
#define GREENPROJECTILE_HPP_

#include "Projectile.hpp"

class GreenProjectile : virtual public Projectile {
    public:
        GreenProjectile(int _orient, sf::Vector2f pos, int desCap);
        ~GreenProjectile();

        void movement(void);
        void animation(void);
        int checkKill(std::shared_ptr<Ennemi> ennemi);
        void display(std::shared_ptr<sf::RenderWindow> window);
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
