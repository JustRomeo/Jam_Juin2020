#ifndef __MAINMENU__
#define __MAINMENU__

#include <memory>

#include "Button.hpp"
#include "TextSFML.hpp"
#include "ImageSFML.hpp"
#include "Exception.hpp"
#include "Multiplayer.hpp"
#include "EventHandler.hpp"
#include "LibGraphics.hpp"

using namespace std;
class MainMenu {
    public:
        MainMenu();
        ~MainMenu();

        bool Menu(shared_ptr<sf::RenderWindow> window);
    private:
        sf::Music *_music;
        std::shared_ptr<Button> play;
        std::shared_ptr<Button> quit;
        std::shared_ptr<Button> bugs;
        std::shared_ptr<Button> ctrl;
        std::shared_ptr<Button> multi;
        std::shared_ptr<ImageSFML> cursor;
        std::shared_ptr<ImageSFML> background;
};

#endif