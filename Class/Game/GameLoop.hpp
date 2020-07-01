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

using namespace std;
class GameLoop {
    public:
        GameLoop();
        ~GameLoop();

        void MapGeneration(vector<string> map);
        void EnnemiGeneration(vector<string> map);
        void PlusGeneration(vector<string> map);
        int fondue(void);
        void clear(void);
        void display(Door door_s);
        int checkOpen(void);
        void setPlayerPosition(vector<string> map);
        shared_ptr<sf::RenderWindow> getWindow(void);
        int getEvent(vector<shared_ptr<Block>> mapSFML);
        void checkDestruction(vector<shared_ptr<Block>> &mapSFML);
        void checkDeathEnemy(vector<shared_ptr<Ennemi>> &Ennemilist);
        int gameLoop(Door door);
        int endScreen();

        shared_ptr<sf::RenderWindow> window;
    protected:
    private:
        ImageSFML font;
        std::shared_ptr<GameMusic> gameMusic;
        shared_ptr<sf::View> view;
        shared_ptr<Character> perso;
        shared_ptr<Sprite> background;
        vector<std::shared_ptr<Projectile>> projectile;
        vector<shared_ptr<Block>> mapSFML;
        vector<shared_ptr<Ennemi>> Ennemilist;
        vector<shared_ptr<MunPlus>> PlusList;
};

#endif /* !GAMELOOP_HPP_ */
