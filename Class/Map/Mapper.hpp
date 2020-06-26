#ifndef __MAPPER__
#define __MAPPER__

#include <vector>
#include <memory>
#include <iostream>
#include "Block.hpp"

using namespace std;
class Mapper {
    public:
        Mapper();
        ~Mapper();

        bool isReady(void);
        void setMap(string filepath);
        void setMap(vector<string> map);
        vector<shared_ptr<Block>> generate(void);

    private:
        vector<string> _map;
};

#endif