/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** GameLoop
*/

#ifndef GAMELOOP_HPP_
#define GAMELOOP_HPP_

#include "LibGraphics.hpp"
#include "Exception.hpp"
#include "Window.hpp"
#include "Character.hpp"

class GameLoop {
    public:
        GameLoop();
        ~GameLoop();
        int gameLoop();
        int getEvent();
        void display();
        void clear();
        int checkOpen();
    protected:
    private:
        std::shared_ptr<sf::RenderWindow> window;
        std::shared_ptr<sf::View> view;
        std::shared_ptr<Sprite> background;
        std::shared_ptr<Character> perso;
};

#endif /* !GAMELOOP_HPP_ */
