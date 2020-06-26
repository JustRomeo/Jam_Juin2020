/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Image
*/

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <iostream>
#include "Position.hpp"

namespace arcade
{
    class Image {
        public:
            Image();
            Image(std::string filename, arcade::Position beg, arcade::Position end);
            ~Image();
            std::string getFilename() const;
            arcade::Position getPositionBeg() const;
            arcade::Position getPositionEnd() const;
            void setFilename(std::string &filename);
            void setPositionBeg(arcade::Position &beg);
            void setPositionEnd(arcade::Position &end);

        private:
            std::string _filename;
            arcade::Position _beg;
            arcade::Position _end;
    };
} // namespace arcade

#endif /* !IMAGE_HPP_ */
