/*
** EPITECH PROJECT, 2020
** Soundwaves
** File description:
** Saver Class
*/

#ifndef __Saver__
#define __Saver__

#include <memory>
#include <vector>

using namespace std;
class Saver {
    public:
        Saver();
        ~Saver();

        void save(vector<string>);

    private:
        string _name;

    protected:
};

#endif