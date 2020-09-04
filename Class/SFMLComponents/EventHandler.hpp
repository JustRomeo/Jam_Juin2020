#ifndef __EventHandler__
#define __EventHandler__

#include <memory>
#include <iostream>

#include "LibGraphics.hpp"

using namespace std;
class EventHandler {
    public:
        EventHandler() {}
        ~EventHandler() {}

        bool isTabPressed(sf::Event);
        void inputEvent(sf::Event, string &);
        int EventType(shared_ptr<sf::RenderWindow>);

    private:
    protected:
};

#endif