/*
** Projet: SoundWaves
** Devs: Alexandre & Roméo
** File:
** Gameloop
*/

#ifndef GAMELOOP_HPP_
#define GAMELOOP_HPP_

#include <memory>
#include <vector>

#include "Door.hpp"
#include "Block.hpp"
#include "Echap.hpp"
#include "Window.hpp"
#include "Runner.hpp"
#include "Ennemis.hpp"
#include "MunPlus.hpp"
#include "Lootable.hpp"
#include "TextSFML.hpp"
#include "Character.hpp"
#include "ImageSFML.hpp"
#include "Exception.hpp"
#include "GameMusic.hpp"
#include "Projectile.hpp"
#include "LoadingBar.hpp"
#include "LibGraphics.hpp"
#include "IProjectile.hpp"
#include "ManetteSFML.hpp"
#include "ProjectileFactory.hpp"

using namespace std;
class GameLoop {
    public:
        enum Controler {RemoteXBOX, RemotePS, KeyBoard};
        GameLoop();
        ~GameLoop();

        int menu(void);
        void clear(void);
        int gameLoop(void);
        void display(void);
        int endScreen(void);
        int checkOpen(void);
        int shootEvent(void);
        void reset_map(void);
        void setPlayerNumber(int);
        void updateControler(void);
        int SecondshootEvent(void);
        int switchWeaponEvent(void);
        int movementEvent(sf::Event);
        int SecondmovementEvent(sf::Event);
        void MapGeneration(vector<string>);
        void PlusGeneration(vector<string>);
        void DoorGeneration(vector<string>);
        void ItemsGeneration(vector<string>);
        void EnnemiGeneration(vector<string>);
        int getEvent(vector<shared_ptr<Block>>);
        void reloadPerso(shared_ptr<sf::Texture>);
        void earnXp(shared_ptr<Character> &, size_t);
        shared_ptr<sf::RenderWindow> getWindow(void);
        shared_ptr<Character> getCharacter(void) const;
        void checkDestruction(vector<shared_ptr<Block>> &);
        void checkDeathEnemy(vector<shared_ptr<Ennemi>> &);
        void checkDeathRunner(vector<shared_ptr<Runner>> &);
        shared_ptr<Character> getSecondCharacter(void) const;

        shared_ptr<LoadingBar> Bar;
        shared_ptr<sf::RenderWindow> window;

    private:
        bool _sound;
        string _pseudo;
        size_t _players;
        Controler _remote;

        shared_ptr<Door> door;
        shared_ptr<sf::View> view;
        shared_ptr<ImageSFML> font;
        shared_ptr<Character> perso;
        shared_ptr<Character> perso2;
        shared_ptr<Sprite> background;
        ProjectileFactory projFactory;
        shared_ptr<EchapMenu> echapMenu;
        shared_ptr<GameMusic> gameMusic;
        vector<shared_ptr<Block>> mapSFML;
        shared_ptr<InputControler> inputctrl;
        vector<shared_ptr<MunPlus>> PlusList;
        vector<shared_ptr<Ennemi>> Ennemilist;
        vector<shared_ptr<Runner>> Runnerlist;
        vector<shared_ptr<Lootable>> Itemslist;
        shared_ptr<ManetteSFML> RemoteControler;
        vector<shared_ptr<IProjectile>> projectile;

    protected:
};

#endif
