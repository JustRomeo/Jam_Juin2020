/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** Character
*/

#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include "time.h"
#include "HUD.hpp"
#include "Time.hpp"
#include "Block.hpp"
#include "Block.hpp"
#include "Objet.hpp"
#include "MunPlus.hpp"
#include "Exception.hpp"
#include "MusicSFML.hpp"
#include "LibGraphics.hpp"

class Character {
    public:
        Character();
        ~Character();

        void dash();
        void jump();
        void fall();
        bool isCac();
        void shoot();
        int getMun();
        void sprint();
        int getWeapon();
        void incWeapon();
        bool isJumping();
        bool getMoving();
        bool isFalling();
        int channelBat();
        void cacAttack();
        void stopSprint();
        bool isShooting();
        void channeling();
        void restartPos();
        bool isSwitching();
        bool isChanneling();
        bool isSprinting();
        int getMunBattery();
        void cacAnimation();
        void createAnimRec();
        void moveChar(std::shared_ptr<sf::RenderWindow> window, int orient);
        void shootAnimation();
        sf::Sprite getSprite();
        void switchAnimation();
        void spriteAnimation();
        void collisionProblem();
        bool isActionPossible();
        void channelingAnimation();
        void setMoving(bool status);
        sf::Vector2f getSpriteMid();
        void setSpritePosition(int, int);
        int checkFall(std::vector<std::shared_ptr<Block>> mapSFML);
        void checkCollMunPlus(vector<shared_ptr<MunPlus>> &PlusList);
        int not_colision(std::vector<std::shared_ptr<Block>> mapSFML);
        int collisionFall(std::vector<std::shared_ptr<Block>> mapSFML);
        void unblockCharacter(std::vector<std::shared_ptr<Block>> mapSFML);
        void display(std::shared_ptr<sf::RenderWindow> window, std::vector<std::shared_ptr<Block>> mapSFML);
        void moveLeft(std::shared_ptr<sf::RenderWindow> window, std::vector<std::shared_ptr<Block>> mapSFML);
        void moveRigth(std::shared_ptr<sf::RenderWindow> window, std::vector<std::shared_ptr<Block>> mapSFML);
        void jumpAnimation(std::shared_ptr<sf::RenderWindow> window, std::vector<std::shared_ptr<Block>> mapSFML);
        void fallingAnimation(std::shared_ptr<sf::RenderWindow> window, std::vector<std::shared_ptr<Block>> mapSFML);
        int _lifes;
        int invulnerability;
    protected:
    private:
        int move_Y;
        int move_Xmax;
        int notMove_Y;
        int weapon_type;
        int sprintBar;

        int cacRectPos;
        int shootRectPos;
        int channelRectPos;
        int jumpCacRectPos;

        bool is_cac;
        bool is_moving;
        bool is_jumping;
        bool is_falling;
        bool is_dashing;
        bool is_shooting;
        bool is_switching;
        bool is_sprinting;
        bool is_channeling;

        Time move_clock;
        Time anim_clock;
        Time cac_clock;
        Time sprint_clock;
        Time dash_clock;

        sf::Vector2f move;
        sf::Sprite sprite;
        Time switch_clock;
        sf::Vector2f oldPose;

        MusicSFML *jump_sound;
        MusicSFML *coli_sound;
        MusicSFML *shot_sound1;
        MusicSFML *shot_sound2;
        MusicSFML *shot_sound3;
        MusicSFML *shot_sound4;

        std::shared_ptr<HUD> hud;
        std::vector<float> channelingTime;
        std::vector<sf::IntRect> shootRect;
        std::shared_ptr<sf::Texture> texture;
        std::vector<sf::IntRect> cacAttackRect;
        std::vector<sf::IntRect> channelingRect;
        std::vector<shared_ptr<Objet>> _objects;
        std::shared_ptr<sf::Texture> textureFight;
        std::vector<sf::IntRect> jumpCacAttackRect;
};

#endif
