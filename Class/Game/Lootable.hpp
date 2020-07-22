#ifndef __LOOTABLE__
#define __LOOTABLE__

#include <iostream>

#include "Objet.hpp"
#include "LibGraphics.hpp"

using namespace std;
enum TYPE {Undefined, Object, Potion};

class Lootable {
    public:
        Lootable(TYPE type, string name);
        ~Lootable();

        void setFilepath(string);
        string getFilepath(void) const;
        void setPosition(sf::Vector2f);
        void setPosition(float, float);
        sf::Vector2f getPosition(void) const;
        shared_ptr<Objet> getObject(void) const;

    private:
        TYPE _type;
        string _filepath;
        sf::Vector2f _pos;
        shared_ptr<Objet> _objet;

    protected:
};

#endif