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
#include "System.hpp"
#include "GameLoop.hpp"
#include "Exception.hpp"
#include "MapUpdater.hpp"
#include "ErrorHandling.hpp"

using namespace std;
int main(int ac, char **av, char **env) {
    int replay = 1;
    shared_ptr<GameLoop> game;
    vector<string> map = System().openfile("maps/.map1");
    Door door(map);

    try {
        game = make_shared<GameLoop>();
    } catch (Exception &e) {
        cout << e.what() << endl;
        return 84;
    }
    while (replay == 1) {
        if (!ErrorHandling().isEnvDisplay(env))
            return 84;
        try {
            game->EnnemiGeneration(map);
            game->PlusGeneration(map);
            game->MapGeneration(map);
            MapUpdater().setPlayerPosition(map, game->getCharacter());
            game->ItemsGeneration(map);
            replay = game->gameLoop(door);
        } catch (Exception &e) {
            cout << e.what() << endl;
            return 84;
        }
    }
    return 0;
}
