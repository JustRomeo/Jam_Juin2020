/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** MapCreator
*/

#include "Map.hpp"

MapCreator::MapCreator(size_t width, size_t heigh) {
    _width = width;
    _heigh = heigh;
    for (size_t i = 0; i < 3; i ++) {
        string line = "###";
        for (size_t i = 0; i < _width; i ++)
            line += "#";
        line += "###";
        _map.push_back(line);
    } for (size_t i = 0; i < _heigh; i ++) {
        string line = "###";
        for (size_t i = 0; i < _width; i ++)
            line += " ";
        line += "###";
        _map.push_back(line);
    } for (size_t i = 0; i < 3; i ++) {
        string line = "###";
        for (size_t i = 0; i < _width; i ++)
            line += "#";
        line += "###";
        _map.push_back(line);
    }
    // this->addChar('X', 10, 10);
    // for (size_t i = 0; i < _map.size(); i ++)
    //     cout << _map[i] << endl;
    // exit(0);
}

MapCreator::~MapCreator() {}

void MapCreator::addChar(char c, size_t x, size_t y) {_map[x + 3][y + 3] = c;}