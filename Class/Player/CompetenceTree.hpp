#ifndef __CompetenceTree__
#define __CompetenceTree__

class CompetenceTree {
    public:
        CompetenceTree();
        ~CompetenceTree();

        void upgradebyLevel(size_t lvl);
        sf::Vector2f getSpeed(void) const;

    private:
        sf::Vector2f _speed;
        sf::Vector2f _lifeproj;
        sf::Vector2f _spdreload;

    protected:
};

#endif