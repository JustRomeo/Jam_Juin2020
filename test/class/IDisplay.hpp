/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** IDisplay
*/

#ifndef IDISPLAY_HPP_
#define IDISPLAY_HPP_

#include "CoreGame.hpp"
#include "Image.hpp"
#include "Position.hpp"

namespace arcade
{
    class IDisplay
    {
        public:
            virtual ~IDisplay() = default;
            virtual void Clear() = 0;
            virtual void Refresh() = 0;
            // virtual void dispMap(std::vector<std::string> &map, Element &map_element) = 0;
            // virtual void dispObject(std::vector<Element> &allElement) = 0;
            // virtual int menu(std::vector<std::string> gameLib_path) = 0;
            // virtual int getEvent() = 0;
            // virtual std::string getName() = 0;
            // virtual void setName(const std::string &name) = 0;
            // virtual int getTimeDiff() = 0;
            // virtual void dispName(std::string name) = 0;
            // virtual void dispScore(int score) = 0;
        protected:
        private:
    };

} // namespace arcade
#endif /* !IDISPLAY_HPP_ */
