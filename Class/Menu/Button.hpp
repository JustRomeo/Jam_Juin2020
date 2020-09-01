/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include "Exception.hpp"
#include "LibGraphics.hpp"
using namespace std;

class Button {
    public:
        Button(sf::Vector2f pos, sf::Vector2f size);
        ~Button();
        void setText(string fontPath, string Text, int size, const sf::Color textColor);
        void setColor(sf::Color buttonColor, sf::Color boundColor, float boundSize);
        void drawButton(shared_ptr<sf::RenderWindow> window);
        int isClicked(sf::Event);

    protected:
    private:
        sf::Font font;
        sf::Text text;
        int is_clicked;
        int is_hovered;
        sf::Vector2f pos;
        sf::Vector2f size;
        sf::Color buttonColor;
        sf::RectangleShape button;
};

#endif /* !BUTTON_HPP_ */
