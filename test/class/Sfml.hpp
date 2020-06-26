/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Sfml
*/

#ifndef SFML_HPP_
#define SFML_HPP_

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "IDisplay.hpp"
#include "CoreGame.hpp"
#include "Sprite.hpp"

namespace arcade {
    class Text;
    class Button;
    class Sprite;
}

class Sfml : public arcade::IDisplay {
    public:
        Sfml();
        ~Sfml();
        void Clear();
        void Refresh();
        int menu(std::vector<std::string> gameLib_path);
        int analyseKeyReleased(sf::Event event);

    protected:
    private:
        int manageEventMenu();
        void drawAndDisplayWindow();

        sf::RenderWindow *_window;
        sf::View *view;
        arcade::Sprite _background;
};

#endif /* !SFML_HPP_ */
