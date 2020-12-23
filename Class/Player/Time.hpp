/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** Time
*/

#ifndef TIME_HPP_
#define TIME_HPP_

#include "LibGraphics.hpp"


class Time {
    public:
        Time();
        ~Time();

        int getTimeDiff(float timeDiff);
        void restartClock();

    protected:
    private:
        sf::Clock clock;
};

#endif

