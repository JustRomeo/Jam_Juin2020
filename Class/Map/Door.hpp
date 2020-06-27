#ifndef __DOOR__
#define __DOOR__

#include <iostream>
#include "Exception.hpp"
#include "LibGraphics.hpp"

using namespace std;
class Door {
    public:
        Door(vector<string> map);
        Door(int X = 0, int Y = 0);
        ~Door();

        void doorOpen(void);
        void setOpening(bool);
        size_t getSize(void) const;
        int getTimeDiff(float diff);
        sf::Texture *getTexture(void);
        sf::Vector2f getPosition(void);
        void setTexture(string filepath);
        sf::Sprite getSprite(void) const;
        void setPosition(sf::Vector2f pos);
        void setPosition(vector<string> map);

    private:
        size_t _anim;
        size_t _size;
        bool _opening;
        sf::Vector2f pos;
        sf::Sprite _sprite;
        sf::Clock move_clock;
        sf::Texture *_texture;
};

#endif