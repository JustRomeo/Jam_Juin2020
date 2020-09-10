#ifndef __LoadingBar__
#define __LoadingBar__

#include <memory>
#include <vector>

#include "TextSFML.hpp"
#include "LibGraphics.hpp"

using namespace std;
class LoadingBar {
    public:
        LoadingBar();
        LoadingBar(size_t total_width = 0, size_t heigh = 0, size_t max = 0);
        ~LoadingBar();

        void isText(bool);
        void setRow(size_t);
        void setMax(size_t);
        bool isText(void) const;
        size_t getRow(void) const;
        size_t getMax(void) const;
        void setTotalWidth(size_t);
        size_t getTotalWidth(void) const;
        shared_ptr<TextSfml> getText(void) const;
        void setRectangle(shared_ptr<sf::RectangleShape>);
        shared_ptr<sf::RectangleShape> getRectangle(void) const;
        void load(shared_ptr<sf::RenderWindow>, string = "", bool = true);

    private:
        size_t _max;
        size_t _row;
        bool _isText;
        size_t _total_width;

        shared_ptr<TextSfml> _text;
        shared_ptr<sf::RectangleShape> _rectangle;

    protected:
};

#endif