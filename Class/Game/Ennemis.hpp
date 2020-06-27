#ifndef __ENNEMIS__
#define __ENNEMIS__

#include <iostream>
#include "Block.hpp"
#include "Exception.hpp"
#include "LibGraphics.hpp"

using namespace std;
class Ennemi {
    public:
        Ennemi(int X = 0, int Y = 0);
        ~Ennemi();

        void goLeft(void);
        void goRight(void);
        int getTimeDiff(float diff);
        sf::Texture *getTexture(void);
        void setPosition(int x, int y);
        sf::Vector2f getPosition(void);
        void movePosition(int x, int y);
        void setTexture(string filepath);
        sf::Vector2f getSize(void) const;
        sf::Sprite getSprite(void) const;
        void setPosition(sf::Vector2f pos);
        void movePosition(sf::Vector2f pos);
        void move(vector<shared_ptr<Block>> mapSFML);
        bool checkFall(vector<shared_ptr<Block>> mapSFML);
        bool isColisionned(vector<shared_ptr<Block>> mapSFML);
        bool isFalllingStop(std::vector<std::shared_ptr<Block>> mapSFML);

        bool left;
    private:
        size_t _anim;
        bool is_falling;
        sf::Vector2f _pos;
        sf::Sprite _sprite;
        sf::Vector2f _size;
        sf::Clock move_clock;
        sf::Vector2f gravity;
        sf::Texture *_texture;
};

#endif