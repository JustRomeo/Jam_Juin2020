#include "MapUpdater.hpp"

MapUpdater::MapUpdater() {}
MapUpdater::~MapUpdater() {}

void MapUpdater::RunnerUpdate(sf::RenderWindow &window, vector<shared_ptr<Runner>> &Runnerlist, vector<shared_ptr<Block>> mapSFML, shared_ptr<Character> &perso) {
    for (size_t i = 0; i < Runnerlist.size(); i ++) {
        window.draw(Runnerlist[i]->getSprite());
        Runnerlist[i]->move(mapSFML, perso);
        if (perso->invulnerability < 1 && sf::IntRect(perso->getSprite().getGlobalBounds()).intersects(sf::IntRect(Runnerlist[i]->getSprite().getGlobalBounds()))) {
            perso->_lifes --;
            perso->invulnerability += 60;
        }
    }
}

void MapUpdater::EnnemiUpdate(sf::RenderWindow &window, vector<shared_ptr<Ennemi>> &Ennemilist, vector<shared_ptr<Block>> mapSFML, shared_ptr<Character> &perso) {
    for (size_t i = 0; i < Ennemilist.size(); i ++) {
        window.draw(Ennemilist[i]->getSprite());
        Ennemilist[i]->move(mapSFML);
        if (perso->invulnerability < 1 && sf::IntRect(perso->getSprite().getGlobalBounds()).intersects(sf::IntRect(Ennemilist[i]->getSprite().getGlobalBounds()))) {
            perso->_lifes --;
            perso->invulnerability += 60;
        }
    }
}

void MapUpdater::BlockUpdate(sf::RenderWindow &window, vector<shared_ptr<Block>> mapSFML) {
    for (size_t i = 0; i < mapSFML.size(); i++)
        window.draw(mapSFML[i]->getSprite());
}

void MapUpdater::setPlayerPosition(vector<string> map, shared_ptr<Character> perso) {
    for (size_t i = 0; i < map.size(); i ++)
        for (size_t j = 0; j < map[i].length(); j ++)
            if (map[i][j] == 'P')
                perso->setSpritePosition(j * 157, i * 157 + 60);
}

void MapUpdater::setSecondPlayerPosition(vector<string> map, shared_ptr<Character> perso2) {
    for (size_t i = 0; i < map.size(); i ++)
        for (size_t j = 0; j < map[i].length(); j ++)
            if (map[i][j] == 'S')
                perso2->setSpritePosition(j * 157, i * 157 + 60);
}

void MapUpdater::checkDestruction(vector<shared_ptr<Block>> &mapSFML, vector<shared_ptr<IProjectile>> &projectile) {
    int res = -1;

    for (size_t i = 0; i < projectile.size(); i ++) {
        res = -1;
        res = projectile[i]->checkDestruction(mapSFML);
        if (res == 0)
            projectile.erase(projectile.begin() + i);
    }
}