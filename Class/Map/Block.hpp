#ifndef __BLOCK__
#define __BLOCK__

#include <iostream>
#include "LibGraphics.hpp"

using namespace std;
class Block {
    public:
        enum Type {UNBREAKABLE, YELLOW, BLUE, PURPLE};
        Block(int X = 0, int Y = 0, size_t size = 0, Type type = Type::UNBREAKABLE);
        ~Block();

        size_t getSize(void) const;
        //std::shared_ptr<sf::Texture> getTexture(void);
        sf::Vector2f getPosition(void);
        void setTexture(string filepath);
        sf::Sprite getSprite(void) const;
        void setPosition(sf::Vector2f pos);
        Type getType() const;

    private:
        Type _type;
        size_t _size;
        sf::Vector2f pos;
        sf::Sprite _sprite;
        std::shared_ptr<sf::Texture> _texture;
};

#endif
