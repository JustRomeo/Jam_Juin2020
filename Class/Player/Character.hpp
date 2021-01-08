/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** Character
*/

#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include "time.h"
#include "HUD.hpp"
#include "Time.hpp"
#include "Block.hpp"
#include "Objet.hpp"
#include "MunPlus.hpp"
#include "Exception.hpp"
#include "MusicSFML.hpp"
#include "LibGraphics.hpp"
#include "CompetenceTree.hpp"

using namespace std;
class Character {
    public:
        Character(shared_ptr<sf::Texture> = nullptr);
        ~Character();

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
        bool isHooking(void);
        bool isFalling(void);
        int channelBat(void);
        void cacAttack(void);
        void setMoving(bool);
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
        void changeSprite(string);
        sf::Sprite getSprite(void);
        void switchAnimation(void);
        void spriteAnimation(void);
        void collisionProblem(void);
        bool isActionPossible(void);
        void channelingAnimation(void);
        sf::Vector2f getSpriteMid(void);
        void setSpritePosition(int, int);
        void addValue(shared_ptr<Objet>);
        void hook(shared_ptr<sf::RenderWindow>);
        int checkFall(vector<shared_ptr<Block>>);
        void hookShoot(vector<shared_ptr<Block>>);
        int not_colision(vector<shared_ptr<Block>>);
        int collisionFall(vector<shared_ptr<Block>>);
        vector<shared_ptr<Objet>> getItems(void) const;
        void unblockCharacter(vector<shared_ptr<Block>>);
        void moveChar(shared_ptr<sf::RenderWindow>, int);
        void checkCollMunPlus(vector<shared_ptr<MunPlus>> &);
        void display(shared_ptr<sf::RenderWindow>, vector<shared_ptr<Block>>);
        void moveLeft(shared_ptr<sf::RenderWindow>, vector<shared_ptr<Block>>);
        void moveRigth(shared_ptr<sf::RenderWindow>, vector<shared_ptr<Block>>);
        void hookAnimation(shared_ptr<sf::RenderWindow>, vector<shared_ptr<Block>>);
        void jumpAnimation(shared_ptr<sf::RenderWindow>, vector<shared_ptr<Block>>);
        void fallingAnimation(shared_ptr<sf::RenderWindow>, vector<shared_ptr<Block>>);

        size_t exp;
        size_t lvl;
        int _lifes;
        int invulnerability;
        shared_ptr<CompetenceTree> _comptree;

    private:
        int move_Y;
        int move_Xmax;
        int notMove_Y;
        int sprintBar;
        int weapon_type;

        int cacRectPos;
        int shootRectPos;
        int channelRectPos;
        int jumpCacRectPos;

        bool is_cac;
        bool is_hooked;
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

        sf::Sprite sprite;
        sf::Vector2f move;
        sf::Vector2f hookBeg;
        sf::Vector2f hookEnd;
        sf::Vector2f hookVec;
        sf::Vector2f oldPose;

        unique_ptr<MusicSFML> jump_sound;
        unique_ptr<MusicSFML> coli_sound;
        unique_ptr<MusicSFML> shot_sound1;
        unique_ptr<MusicSFML> shot_sound2;
        unique_ptr<MusicSFML> shot_sound3;
        unique_ptr<MusicSFML> shot_sound4;

        shared_ptr<HUD> hud;
        vector<float> channelingTime;
        vector<sf::IntRect> shootRect;
        shared_ptr<sf::Texture> texture;
        vector<sf::IntRect> cacAttackRect;
        vector<sf::IntRect> channelingRect;
        vector<shared_ptr<Objet>> _objects;
        shared_ptr<sf::Texture> textureFight;
        vector<sf::IntRect> jumpCacAttackRect;

    protected:
};

#endif
