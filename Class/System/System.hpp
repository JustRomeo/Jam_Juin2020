#ifndef __SYSTEM__
#define __SYSTEM__

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Exception.hpp"

using namespace std;
class System {
    public:
        System();
        ~System();

        int setPath(string filepath);
        int createFolder(string name);
        void savefile(string filepath);
        bool execution(string filepath);
        vector<string> openfile(string filepath);
        void createFile(string name, vector<string> file);
        vector<string> strtowordarray(string str, string delimiter);

    private:
};

#endif
