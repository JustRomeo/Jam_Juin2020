#ifndef __MapMenu__
#define __MapMenu__

#include <vector>
#include <memory>
#include <iostream>

#include "Button.hpp"
#include "TextSFML.hpp"
#include "GameLoop.hpp"
#include "ImageSFML.hpp"
#include "LibGraphics.hpp"

using namespace std;
class MapMenu {
    public:
        MapMenu();
        ~MapMenu();

        size_t choice(GameLoop);
        vector<string> getOnlyMaps(vector<string>);
        void loadTexts(vector<string>);
        void loadImages(vector<string>);

    private:
        vector<shared_ptr<Button>> button;
        shared_ptr<Button> go_back_button;

    protected:
};

#endif