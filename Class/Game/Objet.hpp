#ifndef __OBJECT__
#define __OBJECT__

#include <iostream>

using namespace std;
class Objet {
    public:
        Objet(string name, int speed);
        ~Objet();

        void setSpeed(int nbr);
        int getSpeed(void) const;
        void setName(string name);
        string getName(void) const;

    private:
        int _speed;
        string _name;

    protected:
};

#endif