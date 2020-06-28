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
#include "Ennemis.hpp"
#include "GameLoop.hpp"
#include "MainMenu.hpp"
#include "Exception.hpp"

using namespace std;
static bool isEnvDisplay(char **env) {
    if (!env || !env[0])
        return false;
    for (size_t i = 0; env[i]; i ++)
        if (string(env[i]).find("DISPLAY=:") != string::npos)
            return true;
    return false;
}

static void EnnemiGeneration(vector<string> map, vector<shared_ptr<Ennemi>> &Ennemilist) {
    for (size_t i = 0; i < map.size(); i ++)
        for (size_t j = 0; j < map[i].length(); j ++)
            if (map[i][j] == 'E')
                Ennemilist.push_back(make_shared<Ennemi>(Ennemi(j * 157, i * 157)));
}

int main(int ac, char **av, char **env) {
    int replay = 1;
    Mapper mapper;
    std::shared_ptr<GameLoop> game;
    vector<shared_ptr<Block>> mapSFML;
    vector<shared_ptr<Ennemi>> Ennemilist;
    vector<string> map = System().openfile("maps/.map1");
    Door door(map);

    while (replay == 1) {
        mapSFML.clear();
        Ennemilist.clear();
        EnnemiGeneration(map, Ennemilist);
        if (!isEnvDisplay(env))
            return 84;
        try {
            mapper.setMap(map);
            mapSFML = mapper.generate();
            game = std::make_shared<GameLoop>();
            game->setPlayerPosition(map);
            replay = game->gameLoop(mapSFML, door, Ennemilist);
        } catch (Exception &e) {
            cout << e.what() << endl;
            return 84;
        }
    }
    return 0;
}
