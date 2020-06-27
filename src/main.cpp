/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** main
*/

#include <vector>
#include <memory>
#include <ostream>
#include <iostream>

#include "Door.hpp"
#include "Block.hpp"
#include "System.hpp"
#include "Mapper.hpp"
#include "GameLoop.hpp"
#include "Exception.hpp"

using namespace std;
static bool isEnvDisplay(char **env) {
    if (!env || !env[0])
        return false;
    for (size_t i = 0; env[i]; i ++) {
        if (string(env[i]).find("DISPLAY=:") != string::npos)
            return true;
    }
    return false;
}

#include "Ennemis.hpp"

int main(int ac, char **av, char **env) {
    Mapper mapper;
    std::shared_ptr<GameLoop> game;
    vector<shared_ptr<Block>> mapSFML;
    vector<shared_ptr<Ennemi>> Ennemilist;
    vector<string> map = System().openfile("maps/.map2");
    Door door(map);

    Ennemilist.push_back(make_shared<Ennemi>(Ennemi(500, 500)));
    if (!isEnvDisplay(env))
        return 84;
    try {
        mapper.setMap(map);
        mapSFML = mapper.generate();
    } catch (Exception &e) {
        cout << e.what() << endl;
        return 84;
    }
    game = std::make_shared<GameLoop>();
    game->gameLoop(mapSFML, door, Ennemilist);
    return 0;
}
