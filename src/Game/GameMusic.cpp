/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** GameMusic
*/

#include "GameMusic.hpp"

GameMusic::GameMusic() {
    try {
        soundlvl = 50;
        music = make_shared<sf::Music>();
        music_1 = make_shared<MusicSFML>();
        music_2 = make_shared<MusicSFML>();
        music_3 = make_shared<MusicSFML>();
        death_perso = make_shared<MusicSFML>();
        death_ennemi = make_shared<MusicSFML>();
        end_music = make_shared<MusicSFML>();
        if (!music->openFromFile("./resources/Sounds/music/Main.ogg"))
            throw(Exception("Can't initiate \"./resources/Sounds/music/Main.ogg\"\n"));
        music_1->load("./resources/Sounds/music/music_1.ogg");
        music_2->load("./resources/Sounds/music/music_2.ogg");
        music_3->load("./resources/Sounds/music/music_3.ogg");
        end_music->load("resources/Sounds/music/music_3.ogg");
        death_perso->load("resources/Sounds/Dead_sound.ogg");
        death_ennemi->load("resources/Sounds/death.ogg");
        end_music->load("resources/Sounds/music/end_music.ogg");
        music_1->setLoop(true);
        music_2->setLoop(true);
        music_3->setLoop(true);
    } catch (bad_alloc &e) {
        throw(Exception("Can't initiate one (or more) Music\n"));
    }
}

GameMusic::~GameMusic() {}

void GameMusic::pause_music(int weapon) {
    switch(weapon) {
        case 1: music_1->pause(); break;
        case 2: music_2->pause(); break;
        case 3: music_3->pause(); break;
    }
}

void GameMusic::switch_music(int weapon) {
    switch(weapon) {
        case 1: music_1->start(); break;
        case 2: music_2->start(); break;
        case 3: music_3->start(); break;
    }
}

void GameMusic::endAllMusic() {
    music_1->stop();
    music_2->stop();
    music_3->stop();
    end_music->stop();
    death_perso->stop();
    death_ennemi->stop();
}

void GameMusic::setLvl(size_t lvl) {
    soundlvl = lvl;
    music_1->setVolume(soundlvl);
    music_2->setVolume(soundlvl);
    music_3->setVolume(soundlvl);
    end_music->setVolume(soundlvl);
    death_perso->setVolume(soundlvl);
    death_ennemi->setVolume(soundlvl);
}

void GameMusic::stopMainMusic() {music->stop();}
void GameMusic::playMainMusic() {music->play();}
void GameMusic::endEndMusic() {end_music->stop();}
void GameMusic::startEndMusic() {end_music->start();}
void GameMusic::startDeathMusic() {death_perso->start();}