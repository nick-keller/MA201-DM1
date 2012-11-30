#ifndef MOUSE_H
#define MOUSE_H

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

class MouseWrapper
{
    public:
        MouseWrapper();

        void bind(Event& event);
        int getX();

    protected:

    private:
        Vector2f pos;
        Vector2f presPos;
};

#endif // MOUSE_H
