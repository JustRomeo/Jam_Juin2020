#ifndef __ECHAPMENU__
#define __ECHAPMENU__

#include "Button.hpp"
#include "ImageSFML.hpp"
#include "LibGraphics.hpp"

class EchapMenu {
    public:
        EchapMenu(bool &sound_on);
        ~EchapMenu();

        int Menu(std::shared_ptr<sf::RenderWindow> window);
        void createButton();
    private:
        std::shared_ptr<Button> play;
        std::shared_ptr<Button> back;
        std::shared_ptr<Button> quit;
        std::shared_ptr<ImageSFML> cursor;
        std::shared_ptr<ImageSFML> background;
        std::shared_ptr<ImageSFML> sound;
        bool soundOn;

};

#endif