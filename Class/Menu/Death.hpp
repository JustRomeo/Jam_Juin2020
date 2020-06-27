#ifndef __DEATHMENU__
#define __DEATHMENU__

#include "ImageSFML.hpp"
#include "LibGraphics.hpp"

class DeathMenu {
    public:
        DeathMenu();
        ~DeathMenu();

        int Menu(sf::RenderWindow &window);
    private:
};

#endif