/*
** EPITECH PROJECT, 2020
** Soundwaves
** File description:
** Input Controler Class
*/

#ifndef __InputControler__
#define __InputControler__

#include <vector>
#include <memory>

#include "ManetteSFML.hpp"
#include "LibGraphics.hpp"

using namespace std;
class InputControler {
    public:
        InputControler();
        ~InputControler();

        void setJumpKey(int);
        void setSprintKey(int);
        void setSwitchKey(int);
        int getJumpKey(void) const;
        int getSprintKey(void) const;
        int getSwitchKey(void) const;
        bool isLeft(sf::Event) const;
        bool isRight(sf::Event) const;
        bool isJumping(sf::Event) const;
        bool isShooting(sf::Event) const;
        bool isSwitching(sf::Event) const;
        bool isSprinting(sf::Event) const;

    private:
        int KeyJump;
        int KeyLeft;
        int KeyRight;
        int KeyShoot;
        bool _remote;
        int KeySprint;
        int KeySwitching;
        shared_ptr<ManetteSFML> remote;

    protected:
};

#endif