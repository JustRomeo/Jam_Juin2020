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

using namespace std;
class GameLoop {
    public:
        GameLoop();
        ~GameLoop();

        void clear();
        int getEvent(vector<shared_ptr<Block>> mapSFML);
        void display();
        int checkOpen();
        int gameLoop(vector<shared_ptr<Block>> mapSFML, Door door, vector<shared_ptr<Ennemi>> Ennemilist);

    protected:
    private:
        shared_ptr<sf::View> view;
        shared_ptr<Sprite> background;
        shared_ptr<Character> perso;
        shared_ptr<sf::RenderWindow> window;
};

#endif /* !GAMELOOP_HPP_ */
