#ifndef __ENNEMIS__
#define __ENNEMIS__

#include <iostream>
#include "Exception.hpp"
#include "LibGraphics.hpp"

using namespace std;
class Ennemi {
    public:
        Ennemi(int X = 0, int Y = 0);
        ~Ennemi();

        sf::Texture *getTexture(void);
        sf::Vector2f getPosition(void);
        void setTexture(string filepath);
        sf::Vector2f getSize(void) const;
        sf::Sprite getSprite(void) const;
        void setPosition(sf::Vector2f pos);

    private:
        size_t anim;
        bool moving;
        sf::Vector2f _pos;
        sf::Sprite _sprite;
        sf::Vector2f _size;
        sf::Clock move_clock;
        sf::Texture *_texture;
};

#endif