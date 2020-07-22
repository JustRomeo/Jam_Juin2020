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
#include "Lootable.hpp"

using namespace std;
class GameLoop {
    public:
        GameLoop();
        ~GameLoop();

        int fondue(void);
        void clear(void);
        int gameLoop(Door);
        void display(void);
        int endScreen(void);
        int checkOpen(void);
        int shootEvent(void);
        int switchWeaponEvent(void);
        int movementEvent(sf::Event);
        void MapGeneration(vector<string>);
        void PlusGeneration(vector<string>);
        void DoorGeneration(vector<string>);
        void ItemsGeneration(vector<string>);
        void EnnemiGeneration(vector<string>);
        void setPlayerPosition(vector<string>);
        int getEvent(vector<shared_ptr<Block>>);
        shared_ptr<sf::RenderWindow> getWindow(void);
        void checkDestruction(vector<shared_ptr<Block>> &);
        void checkDeathEnemy(vector<shared_ptr<Ennemi>> &);

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
        vector<shared_ptr<MunPlus>> PlusList;
        std::shared_ptr<GameMusic> gameMusic;
        vector<shared_ptr<Ennemi>> Ennemilist;
        vector<shared_ptr<Lootable>> Itemslist;
        vector<std::shared_ptr<IProjectile>> projectile;
};

#endif
