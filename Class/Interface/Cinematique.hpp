#ifndef __Cinematique__
#define __Cinematique__

#include <memory>
#include <iostream>

#include "Character.hpp"
#include "GameMusic.hpp"
#include "LibGraphics.hpp"

using namespace std;
class Cinematique {
    public:
        Cinematique();
        ~Cinematique();

        int Intro(shared_ptr<sf::RenderWindow>, shared_ptr<Character> &);
        int End(shared_ptr<sf::RenderWindow>, std::shared_ptr<GameMusic> &);
    private:
    protected:
};

#endif