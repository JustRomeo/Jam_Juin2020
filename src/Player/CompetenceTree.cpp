#include "CompetenceTree.hpp"

CompetenceTree::CompetenceTree() {
    _spdshot = 0.06;
    _spdreload = 0.2;
    _speed = sf::Vector2f(0, 0);
    _lifeproj = sf::Vector2f(0, 0);
}
CompetenceTree::~CompetenceTree() {}

void CompetenceTree::upgradebyLevel(size_t lvl) {
    switch(lvl) {
        case 3: _speed.x += 3; _speed.y += 1; _spdshot = 0.04; _spdreload = 0.150; break;
        case 5: _speed.x += 3; _spdreload = 0.125; break;
        case 7: _speed.x += 3; _speed.y += 1; _spdshot = 0.02; _spdreload = 0.100; break;
        case 10: _speed.x += 3; _spdreload = 0.75; break;
        case 12: _speed.x += 3; _speed.y += 1; _spdshot = 0.01; _spdreload = 0.50; break;
        default: break;
    }
}
