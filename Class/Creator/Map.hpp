/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** MapCreator Class
*/

#ifndef __MapCreator__
#define __MapCreator__

#include <vector>
#include <memory>
#include <iostream>

#include "ImageSFML.hpp"
#include "LibGraphics.hpp"

using namespace std;
class MapCreator {
    public:
        MapCreator(size_t width, size_t heigh);
        ~MapCreator();

        void makeMapBounds(void);
        vector<string> getMap(void) const;
        void addChar(char c, size_t x, size_t y);
        void creator(shared_ptr<sf::RenderWindow> window);
        void event_handling(shared_ptr<sf::RenderWindow> window);
        void drawWhichUnderMouse(shared_ptr<sf::RenderWindow> window);

    private:
        size_t _heigh;
        size_t _width;
        size_t block_row;
        vector<string> _map;
        vector<shared_ptr<ImageSFML>> _mapimg;

    protected:
};

#endif
