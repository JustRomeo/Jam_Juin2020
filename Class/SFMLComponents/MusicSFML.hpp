#ifndef __MUSICSFML__
#define __MUSICSFML__

#include <iostream>
#include "Exception.hpp"
#include "LibGraphics.hpp"

using namespace std;
class MusicSFML {
    public:
        MusicSFML();
        ~MusicSFML();

        void stop(void);
        void start(void);
        void pause(void);
        void jump(size_t sec);
        void setLoop(bool loop);
        bool isLoaded(void) const;
        void load(string filepath);
        bool isLooping(void) const;
        void setVolume(size_t volume);

    private:
        bool _loop;
        bool isLoad;
        size_t _volume;
        sf::Music *_music;
};

#endif