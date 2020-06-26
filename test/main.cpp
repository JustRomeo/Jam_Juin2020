/*
** EPITECH PROJECT, 2020
** OOP_arcade_2019
** File description:
** main
*/

#include "Sfml.hpp"

int main(int argc, char **argv)
{
    Sfml *lib = new Sfml();
    int ret = 0;
    char key = 0;
    std::vector<std::string> vec;

    vec.push_back("pacman");
    vec.push_back("nibbler");
    ret = lib->menu(vec);
    delete(lib);
    return (0);
}