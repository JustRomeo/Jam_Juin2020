/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Element
*/

#ifndef ELEMENT_HPP_
#define ELEMENT_HPP_

#include <iostream>
#include <vector>
#include <ncurses.h>
#include <unordered_map>
#include <string>
#include <fstream>
#include "Position.hpp"
#include "Image.hpp"

enum Color {
    WHITE = 1,
    RED = 2,
    BLUE = 3,
    GREEN = 4,
    BLACK = 5,
};

namespace arcade
{
    class Element {
        public:
            Element(Position pos, std::string elem, Color color, Image image);
            Element();
            ~Element();
            Position getPosition() const;
            std::string getElement() const;
            Color getColor() const;
            Image getImage() const;
            void setPosition(Position position);
            void setElement(std::string &element);
            void setColor(Color &color);
            void setImage(Image &image);

        protected:
        private:
            Color _color;
            Image _image;
            std::string _element;
            Position _position;
    };
} // namespace arcade

#endif /* !ELEMENT_HPP_ */
