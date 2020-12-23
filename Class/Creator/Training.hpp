/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** Training Class
*/

#ifndef __Training__
#define __Training__

#include <vector>
#include <memory>
#include <iostream>

#include "Button.hpp"

using namespace std;
class Training {
    public:
        Training();
        ~Training();

        void Menu(shared_ptr<sf::RenderWindow> window);

    private:
        shared_ptr<Button> create;
        shared_ptr<Button> load;
        shared_ptr<Button> quit;
        vector<string> _map;

    protected:
};

#endif
