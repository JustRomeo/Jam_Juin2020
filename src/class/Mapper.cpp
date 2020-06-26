#include "Mapper.hpp"
#include "System.hpp"
#include "Exception.hpp"

Mapper::Mapper() {}
Mapper::~Mapper() {}

bool Mapper::isReady(void) {
    if (_map.size() < 3)
        return false;
    for (size_t i = 0; i < _map.size(); i ++)
        if (_map[i].length() < 3)
            return false;
    return true;
}

void Mapper::setMap(string filepath) {
    try {
        _map = System().openfile(filepath);
    } catch (Exception &e) {
        throw e;
    }
}

vector<shared_ptr<Block>> Mapper::generate(void) {
    vector<shared_ptr<Block>> mapSFML;

    if (!isReady())
        throw (Exception("Ascii Map not set: Impossible to generate a graphics Map: Abort"))
    for (size_t i = 0; i < _map.size(); i ++)
        for (size_t j = 0; j < _map[j].length(); j ++)
            mapSFML.push_back(make_shared<Block>(Block()));
    return mapSFML;
}

void Mapper::setMap(vector<string> map) {_map = map;}
