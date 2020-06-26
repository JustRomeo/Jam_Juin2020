/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** main
*/

#include <ostream>
#include <iostream>
#include "GameLoop.hpp"

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

int main(int ac, char **av, char **env) {
    std::shared_ptr<GameLoop> game;

    if (!isEnvDisplay(env))
        return 84;
    game = std::make_shared<GameLoop>();
    game->gameLoop();
    return 0;
}