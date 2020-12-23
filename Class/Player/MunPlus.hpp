/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** MunPlus
*/

#ifndef MUNPLUS_HPP_
#define MUNPLUS_HPP_

#include "../include/LibGraphics.hpp"
#include "Exception.hpp"

class MunPlus {
    public:
        MunPlus(int type, int x, int y);
        ~MunPlus();

        int getType() const;
        sf::FloatRect getMunShape();
        void display(std::shared_ptr<sf::RenderWindow> window);

    protected:
    private:
        sf::RectangleShape munShape;
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;
        int mun;
        int type;
        int max_mun;
};

#endif /* !MUNPLUS_HPP_ */
