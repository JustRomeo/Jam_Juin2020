#ifndef __PATH__
#define __PATH__

#include <vector>
#include <iostream>

using namespace std;
class Paths {
    public:
        Paths();
        ~Paths();

        string getPath(void);
        void fillPathList(vector<string> &list, string filepath);
    private:
    protected:
};

#endif