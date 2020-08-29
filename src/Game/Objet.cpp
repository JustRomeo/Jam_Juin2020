#include "Objet.hpp"

Objet::Objet(string name, int speed) {
    _name = name;
    _speed = speed;
}
Objet::~Objet() {
    _name.clear();
}

void Objet::setSpeed(int nbr) {_speed = nbr;}
int Objet::getSpeed(void) const {return _speed;}
void Objet::setName(string name) {_name = name;}
string Objet::getName(void) const {return _name;}
