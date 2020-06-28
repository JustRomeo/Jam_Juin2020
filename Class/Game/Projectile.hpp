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
#include "Block.hpp"

class Projectile {
    public:
        enum Type {UNBREAKABLE, YELLOW, BLUE, PURPLE};
        Projectile(int type, int orient, sf::Vector2f pos);
        ~Projectile();
        void animation();
        void movement();
        int getCurrentCapacity();
        void display(std::shared_ptr<sf::RenderWindow> window);
        int checkDestruction(std::shared_ptr<Block> block);
        int getTimeMov(float diff);
        int getTimeAnim(float diff);

    protected:
    private:
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;
        sf::Vector2f move;
        sf::Clock move_clock;
        sf::Clock anim_clock;
        Type type;
        std::vector<sf::IntRect> shootRect1;
        std::vector<float> shoot1Time;
        std::vector<sf::Vector2f> shoot1Move;
        std::vector<sf::IntRect> shootRect2;
         std::vector<float> shoot2Time;
        std::vector<sf::Vector2f> shoot2Move;
        std::vector<sf::IntRect> shootRect3;
        std::vector<float> shoot3Time;
        std::vector<sf::Vector2f> shoot3Move;
        int posRect;
        int destructionCapacity;
};

#endif /* !PROJECTILE_HPP_ */
