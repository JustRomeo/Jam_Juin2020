#include "CompetenceTree.hpp"

CompetenceTree::CompetenceTree() {
    _speed = sf::Vector2f(0, 0);
    _lifeproj = sf::Vector2f(0, 0);
    _spdreload = sf::Vector2f(0, 0);
}
CompetenceTree::~CompetenceTree() {}

void CompetenceTree::upgradebyLevel(size_t lvl) {
    switch(lvl) {
        case 3:  _speed.x += 1; break;
        case 5:  _speed.x += 1; break;
        case 7:  _speed.x += 1; break;
        case 10: _speed.x += 1; break;
    }
}