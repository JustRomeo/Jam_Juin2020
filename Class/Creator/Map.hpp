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

using namespace std;
class MapCreator {
    public:
        MapCreator(size_t width, size_t heigh);
        ~MapCreator();

        vector<string> getMap(void) const;
        void addChar(char c, size_t x, size_t y);

    private:
        size_t _heigh;
        size_t _width;
        vector<string> _map;

    protected:
};

#endif
