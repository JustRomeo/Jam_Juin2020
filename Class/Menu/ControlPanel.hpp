#ifndef __ControlPanel__
#define __ControlPanel__

#include <vector>
#include <memory>

#include "TextSFML.hpp"
#include "ImageSFML.hpp"
#include "LibGraphics.hpp"
#include "EventHandler.hpp"

using namespace std;
class ControlPanel {
    public:
        ControlPanel();
        ~ControlPanel();

        void control_panel(shared_ptr<sf::RenderWindow>);

    private:
    protected:
};

#endif