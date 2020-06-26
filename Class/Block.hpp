#ifndef __BLOCK__
#define __BLOCK__

#include <iostream>
#include "../include/LibGraphics.hpp"

using namespace std;
class Block {
    public:
        Block(int X = 0, int Y = 0, size_t size = 0);
        ~Block();

        size_t getSize(void) const;
        sf::Texture *getTexture(void);
        sf::Vector2f getPosition(void);
        void setTexture(string filepath);
        sf::Sprite getSprite(void) const;
        void setPosition(sf::Vector2f pos);

    private:
        size_t _size;
        sf::Vector2f pos;
        sf::Sprite _sprite;
        sf::Texture *_texture;
};

#endif
