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

        void dash(void);
        void jump(void);
        void fall(void);
        bool isCac(void);
        void shoot(void);
        int getMun(void);
        void sprint(void);
        int getWeapon(void);
        void incWeapon(void);
        bool isJumping(void);
        bool getMoving(void);
        bool isFalling(void);
        int channelBat(void);
        void cacAttack(void);
        void stopSprint(void);
        bool isShooting(void);
        void channeling(void);
        void restartPos(void);
        bool isSwitching(void);
        bool isSprinting(void);
        bool isChanneling(void);
        int getMunBattery(void);
        void cacAnimation(void);
        void createAnimRec(void);
        void shootAnimation(void);
        sf::Sprite getSprite(void);
        void switchAnimation(void);
        void spriteAnimation(void);
        void collisionProblem(void);
        bool isActionPossible(void);
        void setMoving(bool status);
        void channelingAnimation(void);
        sf::Vector2f getSpriteMid(void);
        void setSpritePosition(int, int);
        void addValue(shared_ptr<Objet>);
        vector<shared_ptr<Objet>> getItems(void) const;
        int checkFall(vector<shared_ptr<Block>> mapSFML);
        void checkCollMunPlus(vector<shared_ptr<MunPlus>> &PlusList);
        int not_colision(vector<shared_ptr<Block>> mapSFML);
        int collisionFall(vector<shared_ptr<Block>> mapSFML);
        void unblockCharacter(vector<shared_ptr<Block>> mapSFML);
        void moveChar(shared_ptr<sf::RenderWindow> window, int orient);
        void display(shared_ptr<sf::RenderWindow> window, vector<shared_ptr<Block>> mapSFML);
        void moveLeft(shared_ptr<sf::RenderWindow> window, vector<shared_ptr<Block>> mapSFML);
        void moveRigth(shared_ptr<sf::RenderWindow> window, vector<shared_ptr<Block>> mapSFML);
        void jumpAnimation(shared_ptr<sf::RenderWindow> window, vector<shared_ptr<Block>> mapSFML);
        void fallingAnimation(shared_ptr<sf::RenderWindow> window, vector<shared_ptr<Block>> mapSFML);

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
