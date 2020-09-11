/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** Window
*/

#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "LibGraphics.hpp"
#include "Sprite.hpp"
#include "Exception.hpp"

class Window {
    public:
        Window();
        ~Window();
        void display();
        void clear();
        int checkOpen();
    protected:
    private:
        std::shared_ptr<sf::RenderWindow> window;
        std::shared_ptr<sf::View> view;
        std::shared_ptr<Sprite> background;
};

#endif /* !WINDOW_HPP_ */
