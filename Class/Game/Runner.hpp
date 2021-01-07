/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** Runner Class
*/

#ifndef __Runner__
#define __Runner__

#include <memory>
#include <vector>
#include <iostream>

#include "Block.hpp"
#include "Exception.hpp"
#include "Character.hpp"
#include "LibGraphics.hpp"

using namespace std;
class Runner {
    public:
        Runner(int X, int Y);
        ~Runner();

        void goLeft(void);
        void goRight(void);
        int getTimeDiff(float diff);
        void setPosition(int x, int y);
        void movePosition(int x, int y);
        sf::Vector2f getSize(void) const;
        void setTexture(string filepath);
        sf::Sprite getSprite(void) const;
        void setPosition(sf::Vector2f pos);
        sf::Texture getTexture(void) const;
        void movePosition(sf::Vector2f pos);
        sf::Vector2f getPosition(void) const;
        bool checkFall(vector<shared_ptr<Block>>);
        bool isColisionned(vector<shared_ptr<Block>>);
        bool isFalllingStop(vector<shared_ptr<Block>>);
        void move(vector<shared_ptr<Block>>, shared_ptr<Character>);

    private:
        bool left;
        size_t _anim;
        bool is_falling;
        sf::Vector2f _pos;
        sf::Vector2f _size;
        sf::Clock move_clock;
        sf::Vector2f gravity;
        shared_ptr<sf::Sprite> _sprite;
        shared_ptr<sf::Texture> _texture;

    protected:
};

#endif