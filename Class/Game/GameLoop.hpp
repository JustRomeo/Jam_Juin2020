/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** GameLoop
*/

#ifndef GAMELOOP_HPP_
#define GAMELOOP_HPP_

#include <memory>
#include <vector>

#include "Block.hpp"
#include "Window.hpp"
#include "Ennemis.hpp"
#include "Character.hpp"
#include "ImageSFML.hpp"
#include "Exception.hpp"
#include "LibGraphics.hpp"
#include "Projectile.hpp"
#include "MunPlus.hpp"
#include "GameMusic.hpp"
#include "ProjectileFactory.hpp"
#include "IProjectile.hpp"

using namespace std;
class GameLoop {
    public:
        GameLoop();
        ~GameLoop();

        void display();
        int endScreen();
        int fondue(void);
        void clear(void);
        int shootEvent();
        int checkOpen(void);
        int switchWeaponEvent();
        int gameLoop(Door door);
        int movementEvent(sf::Event event);
        void MapGeneration(vector<string> map);
        void PlusGeneration(vector<string> map);
        void DoorGeneration(vector<string> map);
        void EnnemiGeneration(vector<string> map);
        void setPlayerPosition(vector<string> map);
        shared_ptr<sf::RenderWindow> getWindow(void);
        int getEvent(vector<shared_ptr<Block>> mapSFML);
        void checkDestruction(vector<shared_ptr<Block>> &mapSFML);
        void checkDeathEnemy(vector<shared_ptr<Ennemi>> &Ennemilist);
        shared_ptr<sf::RenderWindow> window;
    protected:
    private:
        shared_ptr<Door> door;
        shared_ptr<sf::View> view;
        shared_ptr<Character> perso;
        shared_ptr<Sprite> background;
        ProjectileFactory projFactory;
        std::shared_ptr<ImageSFML> font;
        vector<shared_ptr<Block>> mapSFML;
        vector<shared_ptr<Ennemi>> Ennemilist;
        vector<shared_ptr<MunPlus>> PlusList;
        std::shared_ptr<GameMusic> gameMusic;
        vector<std::shared_ptr<IProjectile>> projectile;
};

#endif /* !GAMELOOP_HPP_ */
