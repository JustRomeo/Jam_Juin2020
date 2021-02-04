#ifndef __CompetenceTree__
#define __CompetenceTree__

#include <memory>
#include <iostream>

#include "ImageSFML.hpp"
#include "TextSFML.hpp"
#include "LibGraphics.hpp"

using namespace std;
class CompetenceTree {
    public:
        CompetenceTree();
        ~CompetenceTree();

        size_t getPoints(void);
        void setPoints(size_t);
        bool getGrapin(void) const;
        void upgradebyLevel(size_t);
        bool getDoubleJump(void) const;
        sf::Vector2f getSpeed(void) const;
        void competenceChoice(shared_ptr<ImageSFML> &, size_t &, bool &);
        void ChooseMenu(shared_ptr<sf::RenderWindow>, shared_ptr<sf::View>);

        float _spdshot;
        float _spdreload;
        sf::Vector2f _speed;
        sf::Vector2f _lifeproj;

    private:
        size_t pts;
        bool _db_jump;
        bool _grappin;

    protected:
};

#endif