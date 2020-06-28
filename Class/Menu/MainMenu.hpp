#ifndef __MAINMENU__
#define __MAINMENU__

#include "LibGraphics.hpp"

class MainMenu {
    public:
        MainMenu();
        ~MainMenu();

        bool Menu(sf::RenderWindow &window);
    private:
        sf::Music *_music;
};

#endif