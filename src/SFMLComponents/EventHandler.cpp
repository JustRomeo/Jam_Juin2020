#include "EventHandler.hpp"

using namespace std;
void EventHandler::inputEvent(sf::Event event, string &input) {
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == 59 && input.length() > 0)
            input.substr(0, input.length() - 1);
        else if (event.key.code < 26 && event.key.shift)
            input + (char)(event.key.code + 65);
        else if (event.key.code < 26)
            input + (char)(event.key.code + 97);
        else if (event.key.code == 57)
            input + " ";
        else if (event.key.code == 58); //Entrée
        else if (event.key.code == 52 && event.key.shift)
            input + "/";
        // else
        //     cout << "KeyUnknownEvent: " << event.key.code << endl;
    }
}

bool EventHandler::isTabPressed(sf::Event event) {
    if (event.type == sf::Event::KeyReleased)
        if (event.key.code == 60)
            return true;
    return false;
}