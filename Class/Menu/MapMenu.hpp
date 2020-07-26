#ifndef __MapMenu__
#define __MapMenu__

#include <vector>
#include <memory>
#include <iostream>

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
        vector<shared_ptr<TextSfml>> loadTexts(vector<string>);
        vector<shared_ptr<ImageSFML>> loadImages(vector<string>);
    private:
    protected:
};

#endif