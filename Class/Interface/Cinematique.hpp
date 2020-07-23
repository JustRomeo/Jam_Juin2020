#ifndef __Cinematique__
#define __Cinematique__

#include <memory>
#include <iostream>

#include "Character.hpp"
#include "LibGraphics.hpp"

using namespace std;
class Cinematique {
    public:
        Cinematique();
        ~Cinematique();

        int Intro(shared_ptr<sf::RenderWindow>, shared_ptr<Character> &);
    private:
    protected:
};

#endif