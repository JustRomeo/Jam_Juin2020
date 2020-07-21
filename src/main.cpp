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
#include "Multiplayer.hpp"

using namespace std;
static bool isEnvDisplay(char **env) {
    if (!env || !env[0])
        return false;
    for (size_t i = 0; env[i]; i ++)
        if (string(env[i]).find("DISPLAY=:") != string::npos)
            return true;
    return false;
}

int main(int ac, char **av, char **env) {
    Mapper mapper;
    int replay = 1;
    std::shared_ptr<GameLoop> game;
    vector<string> map = System().openfile("maps/.map1");
    Door door(map);

    while (replay == 1) {
        if (!isEnvDisplay(env))
            return 84;
        try {
            game = std::make_shared<GameLoop>();
            game->EnnemiGeneration(map);
            game->PlusGeneration(map);
            game->MapGeneration(map);
            game->setPlayerPosition(map);
            replay = game->gameLoop(door);
        } catch (Exception &e) {
            cout << e.what() << endl;
            return 84;
        }
    }
    return 0;
}
