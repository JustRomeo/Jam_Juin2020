#ifndef __BLOCK__
#define __BLOCK__

#include "../include/LibGraphics.hpp"

class Block {
    public:
        Block();
        ~Block();

        sf::Texture *getTexture(void);
        sf::Vector2f getPosition(void);
        void setTexture(string filepath);
        sf::Sprite getSprite(void) const;
        void setPosition(sf::Vector2f pos);

    private:
        sf::Vector2f pos;
        sf::Sprite _sprite;
        sf::Texture *_texture;
};

#endif