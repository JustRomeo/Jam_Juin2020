/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** Position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

namespace arcade
{
    class Position {
        public:
            Position();
            Position(int x, int y);
            ~Position();
            void setPosition(int x, int y);
            int getPositionX() const;
            int getPositionY() const;
            void operator=(const Position &pos);
            bool operator==(const Position &pos);

        protected:
        private:
            int _x;
            int _y;
    };
}

#endif