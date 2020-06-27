#ifndef __SYSTEM__
#define __SYSTEM__

#include <vector>
#include <iostream>

using namespace std;
class System {
    public:
        System();
        ~System();

        void savefile(string filepath);
        vector<string> openfile(string filepath);

    private:
};

#endif