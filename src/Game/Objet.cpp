#include "Objet.hpp"

Objet::Objet() {
    _speed = 0;
    _name = "";
}
Objet::~Objet() {
    _name.clear();
}

void Objet::setSpeed(int nbr) {_speed = nbr;}
int Objet::getSpeed(void) const {return _speed;}
void Objet::setName(string name) {_name = name;}
string Objet::getName(void) const {return _name;}
