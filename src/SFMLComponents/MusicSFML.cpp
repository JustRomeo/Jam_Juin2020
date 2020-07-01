#include "MusicSFML.hpp"

MusicSFML::MusicSFML() {
    _volume = 20;
    _loop = false;
    isLoad = false;
    _music = new sf::Music;
    _music->setVolume((float)_volume);
}

MusicSFML::~MusicSFML() {
    _music->stop();
    delete(_music);
}

void MusicSFML::load(string filepath) {
    if (!_music->openFromFile(filepath))
        throw Exception("Resources load failed (type: Music)");
    _music->setLoop(_loop);
    isLoad = true;
}

void MusicSFML::setVolume(size_t volume) {
    _volume = volume;
    _music->setVolume(_volume);
}

void MusicSFML::stop(void) {_music->stop();}
void MusicSFML::start(void) {_music->play();}
void MusicSFML::pause(void) {_music->pause();}
void MusicSFML::setLoop(bool loop) {_loop = loop;}
bool MusicSFML::isLoaded(void) const {return isLoad;}
bool MusicSFML::isLooping(void) const {return _loop;}
void MusicSFML::jump(size_t sec) {_music->setPlayingOffset(sf::seconds((float)sec));}
