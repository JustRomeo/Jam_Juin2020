/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** Character
*/

#ifndef CHARACTER_HPP_
#define CHARACTER_HPP_

#include "../include/LibGraphics.hpp"
#include "Exception.hpp"
#include "time.h"

class Character {
    public:
        Character();
        ~Character();
        void display(std::shared_ptr<sf::RenderWindow> window);
        void moveLeft();
        void moveRigth();
        int getTimeDiff(float diff);
        void shoot();
        void restartPos();
        int isShooting();
        bool getMoving();
        void setMoving(bool status);

    protected:
    private:
        std::shared_ptr<sf::Texture> texture;
        std::shared_ptr<sf::Texture> textureFight;
        sf::Sprite sprite;
        sf::Vector2f move;
        sf::Clock move_clock;
        std::vector<sf::IntRect> shootRect;
        bool is_shooting;
        bool is_moving;
        int move_Y;
        int notMove_Y;
        int move_Xmax;
        int shootRectPos;
};

#endif /* !CHARACTER_HPP_ */
