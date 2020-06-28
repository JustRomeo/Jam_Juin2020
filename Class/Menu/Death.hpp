#ifndef __DEATHMENU__
#define __DEATHMENU__

#include "MusicSFML.hpp"
#include "ImageSFML.hpp"
#include "LibGraphics.hpp"

class DeathMenu {
    public:
        DeathMenu();
        ~DeathMenu();

        int Menu(sf::RenderWindow &window);

    private:
        MusicSFML *_music;
};

#endif