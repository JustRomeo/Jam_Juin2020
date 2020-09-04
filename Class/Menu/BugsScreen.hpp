#ifndef __BugsScreen__
#define __BugsScreen__

#include <vector>
#include <memory>

#include "TextSFML.hpp"
#include "ImageSFML.hpp"
#include "LibGraphics.hpp"
#include "EventHandler.hpp"

using namespace std;
class BugsScreen {
    public:
        BugsScreen();
        ~BugsScreen();

        void form_panel(shared_ptr<sf::RenderWindow>);

    private:
        vector<string> input;

    protected:
};

#endif