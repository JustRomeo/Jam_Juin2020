/*
** EPITECH PROJECT, 2020
** Jam
** File description:
** GameLoop
*/

#ifndef GAMELOOP_HPP_
#define GAMELOOP_HPP_

#include <memory>
#include <vector>

#include "Block.hpp"
#include "Window.hpp"
#include "Ennemis.hpp"
#include "Character.hpp"
#include "ImageSFML.hpp"
#include "Exception.hpp"
#include "LibGraphics.hpp"
#include "Projectile.hpp"
#include "MunPlus.hpp"

using namespace std;
class GameLoop {
    public:
        GameLoop();
        ~GameLoop();

        void clear(void);
        void display(void);
        int checkOpen(void);
        int fondue();
        shared_ptr<sf::RenderWindow> getWindow(void);
        int getEvent(vector<shared_ptr<Block>> mapSFML);
        void checkDestruction(vector<shared_ptr<Block>> &mapSFML);
        void checkDeathEnemy(vector<shared_ptr<Ennemi>> &Ennemilist);
        void drawHearts(sf::RenderWindow &window, shared_ptr<Character> &perso);
        int gameLoop(vector<shared_ptr<Block>> mapSFML, Door door,
            vector<shared_ptr<Ennemi>> Ennemilist, vector<shared_ptr<MunPlus>> PlusList);
        int endScreen();

        shared_ptr<sf::RenderWindow> window;
    protected:
    private:
        std::shared_ptr<sf::Music> _music;
        ImageSFML *heart1;
        ImageSFML *heart2;
        ImageSFML *heart3;

        MusicSFML *music_1;
        MusicSFML *music_2;
        MusicSFML *music_3;
        MusicSFML *death_ennemi;
        MusicSFML *death_perso;
        shared_ptr<sf::View> view;
        shared_ptr<Character> perso;
        shared_ptr<Sprite> background;
        vector<std::shared_ptr<Projectile>> projectile;
};

#endif /* !GAMELOOP_HPP_ */
