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
#include "Exception.hpp"
#include "LibGraphics.hpp"
#include "Projectile.hpp"

using namespace std;
class GameLoop {
    public:
        GameLoop();
        ~GameLoop();

        void clear(void);
        void display(void);
        int checkOpen(void);
        void checkDestruction(vector<shared_ptr<Block>> &mapSFML);
        void checkDeathEnemy(vector<shared_ptr<Ennemi>> &Ennemilist);
        shared_ptr<sf::RenderWindow> getWindow(void);
        int getEvent(vector<shared_ptr<Block>> mapSFML);
        int gameLoop(vector<shared_ptr<Block>> mapSFML, Door door, vector<shared_ptr<Ennemi>> Ennemilist);

        shared_ptr<sf::RenderWindow> window;
    protected:
    private:
        shared_ptr<sf::View> view;
        shared_ptr<Character> perso;
        shared_ptr<Sprite> background;
        vector<std::shared_ptr<Projectile>> projectile;
};

#endif /* !GAMELOOP_HPP_ */
