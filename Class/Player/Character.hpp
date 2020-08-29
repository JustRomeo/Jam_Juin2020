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

using namespace std;
class Character {
    public:
        Character();
        ~Character();

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
        bool isHooking();
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
        void shootAnimation();
        sf::Sprite getSprite();
        void switchAnimation();
        void spriteAnimation();
        void collisionProblem();
        bool isActionPossible();
        void channelingAnimation();
        void setMoving(bool status);
        sf::Vector2f getSpriteMid(void);
        void setSpritePosition(int, int);
        void addValue(shared_ptr<Objet>);
        vector<shared_ptr<Objet>> getItems(void) const;
        int checkFall(vector<shared_ptr<Block>> mapSFML);
        int not_colision(vector<shared_ptr<Block>> mapSFML);
        int collisionFall(vector<shared_ptr<Block>> mapSFML);
        void unblockCharacter(vector<shared_ptr<Block>> mapSFML);
        void checkCollMunPlus(vector<shared_ptr<MunPlus>> &PlusList);
        void moveChar(std::shared_ptr<sf::RenderWindow> window, int orient);
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
        bool is_hooking;
        bool is_shooting;
        bool is_switching;
        bool is_sprinting;
        bool is_channeling;

        Time cac_clock;
        Time move_clock;
        Time anim_clock;
        Time switch_clock;
        Time sprint_clock;

        sf::Vector2f move;
        sf::Sprite sprite;
        sf::Vector2f oldPose;

        MusicSFML *jump_sound;
        MusicSFML *coli_sound;
        MusicSFML *shot_sound1;
        MusicSFML *shot_sound2;
        MusicSFML *shot_sound3;
        MusicSFML *shot_sound4;

        shared_ptr<HUD> hud;
        vector<float> channelingTime;
        vector<sf::IntRect> shootRect;
        shared_ptr<sf::Texture> texture;
        vector<sf::IntRect> cacAttackRect;
        vector<sf::IntRect> channelingRect;
        vector<shared_ptr<Objet>> _objects;
        shared_ptr<sf::Texture> textureFight;
        vector<sf::IntRect> jumpCacAttackRect;
};

#endif
