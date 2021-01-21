/*
** EPITECH PROJECT, 2020
** Soundwaves
** File description:
** Saver
*/

#include "Saver.hpp"
#include "System.hpp"

Saver::Saver() {}
Saver::~Saver() {}

void Saver::save(string filepath, vector<string> _map) {
    System().createFile(filepath, _map);
}