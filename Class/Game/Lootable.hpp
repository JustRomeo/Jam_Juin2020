#ifndef __LOOTABLE__
#define __LOOTABLE__

#include <iostream>

#include "Objet.hpp"
#include "ImageSFML.hpp"
#include "LibGraphics.hpp"

using namespace std;
class Lootable {
    public:
        enum TYPE {Undefined, Object, Potion};
        Lootable(TYPE type, string name, size_t x, size_t y, string path = "resources/Images/Game/Object/bonus.png");
        ~Lootable();

        void setFilepath(string);
        string getFilepath(void) const;
        void setPosition(sf::Vector2f);
        void setPosition(float, float);
        sf::Vector2f getPosition(void) const;
        shared_ptr<Objet> getObject(void) const;
        shared_ptr<ImageSFML> getImage(void) const;

    private:
        TYPE _type;
        string _filepath;
        sf::Vector2f _pos;
        shared_ptr<Objet> _objet;
        shared_ptr<ImageSFML> _image;

    protected:
};

#endif