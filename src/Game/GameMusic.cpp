/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** GameMusic
*/

#include "GameMusic.hpp"

GameMusic::GameMusic()
{
    try {
        music = std::make_shared<sf::Music>();
        music_1 = std::make_shared<MusicSFML>();
        music_2 = std::make_shared<MusicSFML>();
        music_3 = std::make_shared<MusicSFML>();
        death_perso = std::make_shared<MusicSFML>();
        death_ennemi = std::make_shared<MusicSFML>();
        end_music = std::make_shared<MusicSFML>();
        music->openFromFile("./resources/Sounds/music/Main.ogg");
        music_1->load("resources/Sounds/music/music_1.ogg");
        music_2->load("resources/Sounds/music/music_2.ogg");
        music_3->load("resources/Sounds/music/music_3.ogg");
        end_music->load("resources/Sounds/music/music_3.ogg");
        death_perso->load("resources/Sounds/Dead_sound.ogg");
        death_ennemi->load("resources/Sounds/death.ogg");
        end_music->load("resources/Sounds/music/end_music.ogg");
        music_1->setLoop(true);
        music_2->setLoop(true);
        music_3->setLoop(true);
    }
    catch (std::bad_alloc &e) {
        throw(Exception("can't initiate window and view\n"));
    }
}

GameMusic::~GameMusic()
{
}

void GameMusic::pause_music(int weapon)
{
    switch(weapon) {
        case 1: music_1->pause(); break;
        case 2: music_2->pause(); break;
        case 3: music_3->pause(); break;
    }
}

void GameMusic::switch_music(int weapon)
{
    switch(weapon) {
        case 1: music_1->start(); break;
        case 2: music_2->start(); break;
        case 3: music_3->start(); break;
    }
}

void GameMusic::startDeathMusic()
{
    death_perso->start();
}

void GameMusic::endAllMusic()
{
    music_1->stop();
    music_2->stop();
    music_3->stop();
}

void GameMusic::startEndMusic()
{
    end_music->start();
}

void GameMusic::endEndMusic()
{
    end_music->stop();
}

void GameMusic::playMainMusic()
{
    music->play();
}

void GameMusic::stopMainMusic()
{
    music->stop();
}