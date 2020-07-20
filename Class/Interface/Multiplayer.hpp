#ifndef __MULTIPLAYER__
#define __MULTIPLAYER__

#include <memory>
#include <iostream>

#include "LibGraphics.hpp"

using namespace std;
class Multi_Screen {
    public:
        Multi_Screen(shared_ptr<sf::RenderWindow> window = 0);
        ~Multi_Screen();

        void display(void);

    private:
        bool _host;
        bool _connected;
        shared_ptr<sf::RenderWindow> _window;

    protected:
};

#endif