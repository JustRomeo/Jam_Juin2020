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
#include "Block.hpp"
#include "Exception.hpp"
#include "MusicSFML.hpp"
#include "LibGraphics.hpp"
#include "MunPlus.hpp"
#include "HUD.hpp"

class Character {
    public:
        Character();
        ~Character();
        void createAnimRec();
        sf::Sprite getSprite();
        void display(std::shared_ptr<sf::RenderWindow> window,
            std::vector<std::shared_ptr<Block>> mapSFML);
        void moveLeft(std::shared_ptr<sf::RenderWindow> window, std::vector<std::shared_ptr<Block>> mapSFML);
        void moveRigth(std::shared_ptr<sf::RenderWindow> window, std::vector<std::shared_ptr<Block>> mapSFML);
        int getTimeDiff(float diff);
        int getTimeSwitch(float diff);
        int getTimeMove(float diff);
        void shoot();
        void channelingAnimation();
        void switchAnimation();
        void channeling();
        void restartPos();
        int getWeapon();
        void incWeapon();
        bool isChanneling();
        bool isJumping();
        bool getMoving();
        bool isFalling();
        bool isShooting();
        bool isSwitching();
        bool isActionPossible();
        void setMoving(bool status);
        void jump();
        void fall();
        int getMunBattery();
        int getMun();
        int channelBat();
        sf::Vector2f getSpriteMid();
        void checkCollMunPlus(vector<shared_ptr<MunPlus>> &PlusList);
        void jumpAnimation(std::shared_ptr<sf::RenderWindow> window,
            std::vector<std::shared_ptr<Block>> mapSFML);
        void shootAnimation();
        void fallingAnimation(std::shared_ptr<sf::RenderWindow> window,
            std::vector<std::shared_ptr<Block>> mapSFML);
        int not_colision(std::vector<std::shared_ptr<Block>> mapSFML);
        int collisionFall(std::vector<std::shared_ptr<Block>> mapSFML);
        int checkFall(std::vector<std::shared_ptr<Block>> mapSFML);
        void setSpritePosition(int, int);
        int _lifes;
        int invulnerability;
    protected:
    private:
        bool is_switching;
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
        sf::Clock switch_clock;
        sf::Vector2f oldPose;
        sf::Clock anim_clock;
        MusicSFML *jump_sound;
        MusicSFML *coli_sound;
        MusicSFML *shot_sound;
        std::vector<float> channelingTime;
        std::vector<sf::IntRect> shootRect;
        std::shared_ptr<sf::Texture> texture;
        std::vector<sf::IntRect> channelingRect;
        std::shared_ptr<sf::Texture> textureFight;
        std::shared_ptr<HUD> hud;
};

#endif /* !CHARACTER_HPP_ */
