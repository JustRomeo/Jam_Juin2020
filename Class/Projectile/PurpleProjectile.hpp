/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** PurpleProjectile
*/

#ifndef PURPLEPROJECTILE_HPP_
#define PURPLEPROJECTILE_HPP_

#include "Projectile.hpp"

class PurpleProjectile : virtual public Projectile {
    public:
        PurpleProjectile(int _orient, sf::Vector2f pos, int desCap);
        ~PurpleProjectile();

        void animation();
        void movement();
        void display(std::shared_ptr<sf::RenderWindow> window);
        int checkKill(std::shared_ptr<Ennemi> ennemi);
        int checkKill(std::shared_ptr<Runner> ennemi);
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

#endif /* !PURPLEPROJECTILE_HPP_ */
