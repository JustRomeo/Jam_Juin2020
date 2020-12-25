/*
** EPITECH PROJECT, 2020
** SFML
** File description:
** Manette SFML Hpp
*/

#ifndef __Manette__
#define __Manette__

#include "LibGraphics.hpp"

class ManetteSFML {
    public:
        ManetteSFML();
        ~ManetteSFML();

        enum Button {Croix, Rond, Carre, Triangle, Nada};
        enum Direction {Droite, DroiteHaut, Haut, GaucheHaut, Gauche, GaucheBas, Bas, DroiteBas, Nothing};

        bool isConnected(void);
        bool isClicked(Button);
        sf::Vector2f getAxis(void);
        void setSensibility(size_t);
        size_t howManyConnected(void);
        Button getButtonsClicked(void);
        Direction getJoysDirection(void);
        size_t getSensibility(void) const;

    private:
        bool _isCo;
        sf::Joystick _joys;
        size_t _sensybility;

    protected:
};

#endif