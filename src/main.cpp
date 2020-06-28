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
#include "MunPlus.hpp"
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

static void PlusGeneration(vector<string> map, vector<shared_ptr<MunPlus>> &PlusList)
{
    for (size_t i = 0; i < map.size(); i ++) {
        for (size_t j = 0; j < map[i].length(); j ++) {
            if (map[i][j] == '1')
                PlusList.push_back(make_shared<MunPlus>(1, j * 157 + 50, i * 157 + 60));
            if (map[i][j] == '2')
                PlusList.push_back(make_shared<MunPlus>(2, j * 157 + 50, i * 157 + 60));
            if (map[i][j] == '3')
                PlusList.push_back(make_shared<MunPlus>(3, j * 157 + 50, i * 157 + 60));
        }
    }
}

int main(int ac, char **av, char **env) {
    int replay = 1;
    Mapper mapper;
    std::shared_ptr<GameLoop> game;
    vector<shared_ptr<Block>> mapSFML;
    vector<shared_ptr<Ennemi>> Ennemilist;
    vector<shared_ptr<MunPlus>> PlusList;
    vector<string> map = System().openfile("maps/.map1");
    Door door(map);

    while (replay == 1) {
        mapSFML.clear();
        Ennemilist.clear();
        EnnemiGeneration(map, Ennemilist);
        PlusGeneration(map, PlusList);
        if (!isEnvDisplay(env))
            return 84;
        try {
            mapper.setMap(map);
            mapSFML = mapper.generate();
            game = std::make_shared<GameLoop>();
            game->setPlayerPosition(map);
            replay = game->gameLoop(mapSFML, door, Ennemilist, PlusList);
        } catch (Exception &e) {
            cout << e.what() << endl;
            return 84;
        }
    }
    return 0;
}
