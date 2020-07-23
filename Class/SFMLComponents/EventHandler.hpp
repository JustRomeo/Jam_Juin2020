#ifndef __EVENTHANDLER__
#define __EVENTHANDLER__

#include <memory>
#include <iostream>

#include "LibGraphics.hpp"

using namespace std;
class EventHandler {
    public:
        EventHandler() {}
        ~EventHandler() {}

        bool isTabPressed(sf::Event event);
        void inputEvent(sf::Event event, string &input);
    private:
};

#endif