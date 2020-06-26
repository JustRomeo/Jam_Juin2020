#ifndef __BLOCK__
#define __BLOCK__

#include <iostream>
#include "../include/LibGraphics.hpp"

using namespace std;
class Block {
    public:
        Block(int X = 0, int Y = 0, int heigh = 0, int width = 0);
        ~Block();

        sf::Texture *getTexture(void);
        sf::Vector2f getPosition(void);
        void setTexture(string filepath);
        sf::Sprite getSprite(void) const;
        void setPosition(sf::Vector2f pos);

    private:
        sf::Vector2f pos;
        sf::Vector2f size;
        sf::Sprite _sprite;
        sf::Texture *_texture;
};

#endif
