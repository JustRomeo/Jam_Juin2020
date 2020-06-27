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
        int getWeapon();
        void incWeapon();
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

        int _lifes;
    protected:
    private:
        int move_Y;
        int notMove_Y;
        int move_Xmax;
        bool is_moving;
        bool is_jumping;
        int weapon_type;
        bool is_falling;
        int shootRectPos;
        bool is_shooting;
        sf::Vector2f move;
        sf::Sprite sprite;
        int channelRectPos;
        bool is_channeling;
        sf::Clock move_clock;
        sf::Vector2f oldPose;
        sf::Clock anim_clock;
        std::vector<float> channelingTime;
        std::vector<sf::IntRect> shootRect;
        std::shared_ptr<sf::Texture> texture;
        std::vector<sf::IntRect> channelingRect;
        std::shared_ptr<sf::Texture> textureFight;
};

#endif /* !CHARACTER_HPP_ */
