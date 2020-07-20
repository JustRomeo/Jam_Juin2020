#ifndef __MAINMENU__
#define __MAINMENU__

#include <memory>

#include "LibGraphics.hpp"

using namespace std;
class MainMenu {
    public:
        MainMenu();
        ~MainMenu();

        bool Menu(shared_ptr<sf::RenderWindow> window);
    private:
        sf::Music *_music;
};

#endif