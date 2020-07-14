/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** Weapon
*/

#ifndef WEAPON_HPP_
#define WEAPON_HPP_

#include "LibGraphics.hpp"
#include "MusicSFML.hpp"

class Weapon {
    public:
        enum WeaponType{YELLOW, BLUE, PURPLE};
        Weapon();
        ~Weapon();

    protected:
    private:
        MusicSFML *shot_sound1;
        MusicSFML *shot_sound2;
        MusicSFML *shot_sound3;
        MusicSFML *shot_sound4;
        int weapon_type;
        WeaponType weaponType;
};

#endif /* !WEAPON_HPP_ */
