#include "Lootable.hpp"
#include "Exception.hpp"

Lootable::Lootable(TYPE type, string name) {
    _type = type;
    _objet = make_shared<Objet>();
}
Lootable::~Lootable() {}

shared_ptr<Objet> Lootable::getObject(void) const {
    if (_type != Object)
        throw Exception("Not the good lootable type.");
    return _objet;
}

void Lootable::setPosition(sf::Vector2f pos) {_pos = pos;}
void Lootable::setFilepath(string path) {_filepath = path;}
string Lootable::getFilepath(void) const {return _filepath;}
sf::Vector2f Lootable::getPosition(void) const {return _pos;}
void Lootable::setPosition(float x, float y) {_pos = sf::Vector2f(x, y);}