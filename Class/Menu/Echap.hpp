#ifndef __ECHAPMENU__
#define __ECHAPMENU__

#include "ImageSFML.hpp"
#include "LibGraphics.hpp"

class EchapMenu {
    public:
        EchapMenu();
        ~EchapMenu();

        int Menu(sf::RenderWindow &, bool &);
    private:
};

#endif