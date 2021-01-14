#ifndef __InputControler__
#define __InputControler__

#include <vector>
#include <memory>

#include "ManetteSFML.hpp"
#include "LibGraphics.hpp"

using namespace std;
class InputControler {
    public:
        InputControler();
        ~InputControler();

        bool isLeft(void) const;
        bool isRight(void) const;
        bool isJumping(void) const;
        bool isShooting(void) const;
        bool isSwitching(void) const;
        bool isSprinting(void) const;

    private:
        bool _remote;
        shared_ptr<ManetteSFML> remote;

    protected:
};

#endif