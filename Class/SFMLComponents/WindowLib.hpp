#ifndef __WindowLibSfml__
#define __WindowLibSfml__

#include <vector>
#include <memory>
#include <iostream>

#include "ImageSFML.hpp"
#include "LibGraphics.hpp"

using namespace std;
class WindowLib {
    public:
        WindowLib();
        ~WindowLib();

        void drawSprites(shared_ptr<sf::RenderWindow>, vector<shared_ptr<ImageSFML>>);

    private:
    protected:
};

#endif