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
#include "Exception.hpp"
#include "LibGraphics.hpp"

using namespace std;
class GameLoop {
    public:
        GameLoop();
        ~GameLoop();

        void clear();
        int getEvent();
        void display();
        int checkOpen();
        int gameLoop(vector<shared_ptr<Block>> mapSFML);

    protected:
    private:
        std::shared_ptr<sf::View> view;
        std::shared_ptr<Sprite> background;
        std::shared_ptr<sf::RenderWindow> window;
};

#endif /* !GAMELOOP_HPP_ */
