/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
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

        void setLvl(size_t);
        void pause_music(int);
        void switch_music(int);
        void endAllMusic(void);
        void endEndMusic(void);
        void startEndMusic(void);
        void playMainMusic(void);
        void stopMainMusic(void);
        void startDeathMusic(void);

    private:
        size_t soundlvl;
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
