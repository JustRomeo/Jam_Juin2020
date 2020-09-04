#ifndef __Map_Updater__
#define __Map_Updater__

#include <memory>
#include <vector>

#include "Block.hpp"
#include "Ennemis.hpp"
#include "Character.hpp"
#include "IProjectile.hpp"
#include "LibGraphics.hpp"

using namespace std;
class MapUpdater {
    public:
        MapUpdater();
        ~MapUpdater();

        void setPlayerPosition(vector<string>, shared_ptr<Character>);
        void BlockUpdate(sf::RenderWindow &, vector<shared_ptr<Block>>);
        void setSecondPlayerPosition(vector<string>, shared_ptr<Character>);
        void checkDestruction(vector<shared_ptr<Block>> &, vector<shared_ptr<IProjectile>> &);
        void EnnemiUpdate(sf::RenderWindow &, vector<shared_ptr<Ennemi>> &, vector<shared_ptr<Block>>, shared_ptr<Character> &);
    private:
    protected:
};

#endif