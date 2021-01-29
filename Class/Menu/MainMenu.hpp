/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** Main Menu Class
*/

#ifndef __MAINMENU__
#define __MAINMENU__

#include <memory>

#include "Button.hpp"
#include "GameLoop.hpp"
#include "TextSFML.hpp"
#include "ImageSFML.hpp"
#include "Exception.hpp"
#include "Multiplayer.hpp"
#include "LibGraphics.hpp"
#include "ManetteSFML.hpp"
#include "EventHandler.hpp"

using namespace std;
class MainMenu {
    public:
        MainMenu();
        ~MainMenu();

        string getPseudo(void) const;
        void remoteChoice(shared_ptr<sf::RenderWindow> window);
        bool Menu(shared_ptr<sf::RenderWindow> window, GameLoop &game);
        void changeCustomPlayer(shared_ptr<sf::Texture> new_texture, GameLoop &game);
        bool buttonsChoice(shared_ptr<sf::RenderWindow> window, sf::Event event, GameLoop &game);

    private:
        string _mypseudo;
        bool isRemoteUsed;
        sf::Music *_music;
        size_t _remote_row;

        shared_ptr<Button> play;
        shared_ptr<Button> quit;
        shared_ptr<Button> ctrl;
        shared_ptr<Button> multi;
        shared_ptr<Button> local;
        shared_ptr<ImageSFML> tuto;
        shared_ptr<ImageSFML> bugs;
        shared_ptr<ImageSFML> cursor;
        shared_ptr<ImageSFML> change;
        shared_ptr<ManetteSFML> remote;
        shared_ptr<TextSfml> pseudotxt;
        shared_ptr<ImageSFML> background;
        shared_ptr<sf::Texture> texture_1;
        shared_ptr<sf::Texture> texture_2;
        shared_ptr<sf::Sprite> perso_sprite;
        shared_ptr<ImageSFML> manette_cursor;
        shared_ptr<sf::RectangleShape> rectbase;
        shared_ptr<sf::RectangleShape> rectload;
};

#endif