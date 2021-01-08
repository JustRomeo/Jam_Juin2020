#ifndef __CompetenceTree__
#define __CompetenceTree__

#include <memory>
#include <iostream>

#include "LibGraphics.hpp"

using namespace std;
class CompetenceTree {
    public:
        CompetenceTree();
        ~CompetenceTree();

        void upgradebyLevel(size_t lvl);
        sf::Vector2f getSpeed(void) const;

        float _spdshot;
        float _spdreload;
        sf::Vector2f _speed;
        sf::Vector2f _lifeproj;
    private:

    protected:
};

#endif