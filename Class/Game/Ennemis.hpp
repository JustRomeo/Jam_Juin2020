/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** Runner Class
*/

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

        enum Type {Blue, Green, Orange, Purple};

        void goLeft(void);
        void goRight(void);
        int getType(void) const;
        void setType(Type newtype);
        int getTimeDiff(float diff);
        void setPosition(int x, int y);
        void movePosition(int x, int y);
        void setTexture(string filepath);
        sf::Vector2f getSize(void) const;
        sf::Sprite getSprite(void) const;
        sf::Texture getTexture(void) const;
        void setPosition(sf::Vector2f pos);
        void movePosition(sf::Vector2f pos);
        sf::Vector2f getPosition(void) const;
        void move(vector<shared_ptr<Block>> mapSFML);
        bool checkFall(vector<shared_ptr<Block>> mapSFML);
        bool isColisionned(vector<shared_ptr<Block>> mapSFML);
        bool isFalllingStop(std::vector<std::shared_ptr<Block>> mapSFML);

        bool left;

    private:
        Type _type;
        size_t _anim;
        bool is_falling;
        sf::Vector2f _pos;
        sf::Vector2f _size;
        sf::Clock move_clock;
        sf::Vector2f gravity;
        shared_ptr<sf::Sprite> _sprite;
        shared_ptr<sf::Texture> _texture;
};

#endif