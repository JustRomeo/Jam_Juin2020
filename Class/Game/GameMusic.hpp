/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** GameMusic
*/

#ifndef GAMEMUSIC_HPP_
#define GAMEMUSIC_HPP_

#include "MusicSFML.hpp"
#include "Exception.hpp"

using namespace std;
class GameMusic {
    public:
        GameMusic();
        ~GameMusic();

        void endAllMusic(void);
        void endEndMusic(void);
        void startEndMusic(void);
        void playMainMusic(void);
        void stopMainMusic(void);
        void startDeathMusic(void);
        void pause_music(int weapon);
        void switch_music(int weapon);

    private:
        shared_ptr<sf::Music> music;
        shared_ptr<MusicSFML> music_1;
        shared_ptr<MusicSFML> music_2;
        shared_ptr<MusicSFML> music_3;
        shared_ptr<MusicSFML> end_music;
        shared_ptr<MusicSFML> death_perso;
        shared_ptr<MusicSFML> death_ennemi;

    protected:
};

#endif
