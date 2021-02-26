/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** Door Class
*/

#ifndef __DOOR__
#define __DOOR__

#include <iostream>
#include "Exception.hpp"
#include "MusicSFML.hpp"
#include "LibGraphics.hpp"

using namespace std;
class Door {
    public:
        Door(vector<string> map);
        Door(int X = 0, int Y = 0);
        ~Door();

        int getAnim();
        bool getOpen();
        void setOpening(bool);
        int getTimeDiff(float);
        void setTexture(string);
        bool isEnded(void) const;
        void doorOpen(sf::Sprite);
        size_t getSize(void) const;
        sf::Vector2f getPosition(void);
        void setPosition(sf::Vector2f);
        sf::Sprite getSprite(void) const;
        void setPosition(vector<string>);
        shared_ptr<sf::Texture> getTexture(void);

        bool alreadyopen;

    private:
        bool _end;
        size_t _anim;
        size_t _size;
        bool _opening;
        sf::Vector2f pos;
        sf::Sprite _sprite;
        sf::Clock move_clock;
        shared_ptr<MusicSFML> openUp;
        shared_ptr<sf::Texture> _texture;
};

#endif