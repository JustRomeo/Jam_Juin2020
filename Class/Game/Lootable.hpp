#ifndef __LOOTABLE__
#define __LOOTABLE__

#include <vector>
#include <memory>
#include <iostream>


#include "Objet.hpp"
#include "ImageSFML.hpp"
#include "LibGraphics.hpp"

using namespace std;
class Lootable {
    public:
        enum TYPE {Undefined, Object, Potion};
        Lootable(shared_ptr<Lootable> &);
        Lootable(TYPE type, string name, size_t x, size_t y, string path = "resources/Images/Game/Object/bonus.png");
        ~Lootable();
        Lootable &operator=(Lootable &loot);

        void setLife(size_t);
        void setName(string);
        void setSpeed(size_t);
        void setMaxlife(size_t);
        void setFilepath(string);
        TYPE getType(void) const;
        void setType(TYPE newone);
        size_t getLife(void) const;
        string getName(void) const;
        size_t getSpeed(void) const;
        size_t getMaxlife(void) const;
        string getFilepath(void) const;
        void setPosition(sf::Vector2f);
        void setPosition(float, float);
        void setObjet(shared_ptr<Objet>);
        sf::Vector2f getPosition(void) const;
        shared_ptr<Objet> getObjet(void) const;
        shared_ptr<Objet> getObject(void) const;
        shared_ptr<ImageSFML> getImage(void) const;

    private:
        TYPE _type;
        size_t life;
        size_t speed;
        string _name;
        string _filepath;
        sf::Vector2f _pos;
        shared_ptr<Objet> _objet;
        shared_ptr<ImageSFML> _image;

    protected:
};

#endif