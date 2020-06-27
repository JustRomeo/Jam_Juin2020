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
#include "Block.hpp"
#include "time.h"

class Character {
    public:
        Character();
        ~Character();
        sf::Sprite getSprite();
        void display(std::shared_ptr<sf::RenderWindow> window,
            std::vector<std::shared_ptr<Block>> mapSFML);
        void moveLeft(std::shared_ptr<sf::RenderWindow> window, std::vector<std::shared_ptr<Block>> mapSFML);
        void moveRigth(std::shared_ptr<sf::RenderWindow> window, std::vector<std::shared_ptr<Block>> mapSFML);
        int getTimeDiff(float diff);
        void shoot();
        void channelingAnimation();
        void channeling();
        void restartPos();
        int isShooting();
        bool isChanneling();
        bool isJumping();
        bool getMoving();
        bool isFalling();
        void setMoving(bool status);
        void jump();
        void fall();
        sf::Vector2f getSpriteMid();
        void jumpAnimation(std::shared_ptr<sf::RenderWindow> window,
            std::vector<std::shared_ptr<Block>> mapSFML);
        void shootAnimation();
        void fallingAnimation(std::shared_ptr<sf::RenderWindow> window,
            std::vector<std::shared_ptr<Block>> mapSFML);
        int not_colision(std::vector<std::shared_ptr<Block>> mapSFML);
        int collisionFall(std::vector<std::shared_ptr<Block>> mapSFML);
        int checkFall(std::vector<std::shared_ptr<Block>> mapSFML);

    protected:
    private:
        std::shared_ptr<sf::Texture> texture;
        std::shared_ptr<sf::Texture> textureFight;
        sf::Sprite sprite;
        sf::Vector2f move;
        sf::Vector2f oldPose;
        sf::Clock move_clock;
        sf::Clock anim_clock;
        std::vector<sf::IntRect> shootRect;
        std::vector<sf::IntRect> channelingRect;
        std::vector<float> channelingTime;
        bool is_shooting;
        bool is_moving;
        bool is_jumping;
        bool is_falling;
        bool is_channeling;
        int move_Y;
        int notMove_Y;
        int move_Xmax;
        int shootRectPos;
        int channelRectPos;
};

#endif /* !CHARACTER_HPP_ */
