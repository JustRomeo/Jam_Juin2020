/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** Echap Menu Class
*/

#ifndef __ECHAPMENU__
#define __ECHAPMENU__

#include "Button.hpp"
#include "ImageSFML.hpp"
#include "LibGraphics.hpp"

using namespace std;
class EchapMenu {
    public:
        EchapMenu();
        ~EchapMenu();

        void createButton(void);
        size_t getSoundLvl(void) const;
        void updateSong(sf::Event event);
        int Menu(shared_ptr<sf::RenderWindow>);
        void dispEchapMenu(shared_ptr<sf::RenderWindow>);

    private:
        size_t soundlvl;

        shared_ptr<Button> play;
        shared_ptr<Button> back;
        shared_ptr<Button> quit;
        shared_ptr<ImageSFML> sound;
        shared_ptr<ImageSFML> cursor;
        shared_ptr<ImageSFML> larrow;
        shared_ptr<ImageSFML> rarrow;
        shared_ptr<ImageSFML> controler;
        shared_ptr<ImageSFML> background;
        shared_ptr<sf::RectangleShape> rectbase;
        shared_ptr<sf::RectangleShape> rectload;
        shared_ptr<sf::RectangleShape> rectcolo;

};

#endif