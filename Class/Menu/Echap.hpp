/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** Echap Menu Class
*/

#ifndef __ECHAPMENU__
#define __ECHAPMENU__

#include "Button.hpp"
#include "TextSFML.hpp"
#include "ImageSFML.hpp"
#include "LibGraphics.hpp"
#include "InputControler.hpp"

using namespace std;
class EchapMenu {
    public:
        EchapMenu();
        ~EchapMenu();

        void createButton(void);
        void updateSong(sf::Event);
        size_t getSoundLvl(void) const;
        void updateControler(sf::Event);
        InputControler getInput(void) const;
        int Menu(shared_ptr<sf::RenderWindow>);
        void setControler(InputControler newone);
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
        shared_ptr<TextSfml> jumpText;
        shared_ptr<TextSfml> switchText;
        shared_ptr<TextSfml> sprintText;
        shared_ptr<ImageSFML> controler;
        shared_ptr<ImageSFML> rectImage;
        shared_ptr<ImageSFML> _background;
        shared_ptr<InputControler> _controler;
        shared_ptr<sf::RectangleShape> rectbase;
        shared_ptr<sf::RectangleShape> rectload;
        shared_ptr<sf::RectangleShape> rectcolo;

};

#endif