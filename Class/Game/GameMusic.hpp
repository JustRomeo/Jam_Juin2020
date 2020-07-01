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

class GameMusic {
    public:
        GameMusic();
        ~GameMusic();
        void switch_music(int weapon);
        void pause_music(int weapon);
        void startDeathMusic();
        void endAllMusic();
        void startEndMusic();
        void endEndMusic();
        void playMainMusic();
        void stopMainMusic();

    protected:
    private:
        std::shared_ptr<sf::Music> music;
        std::shared_ptr<MusicSFML> music_1;
        std::shared_ptr<MusicSFML> music_2;
        std::shared_ptr<MusicSFML> music_3;
        std::shared_ptr<MusicSFML> death_ennemi;
        std::shared_ptr<MusicSFML> death_perso;
        std::shared_ptr<MusicSFML> end_music;
};

#endif /* !GAMEMUSIC_HPP_ */
