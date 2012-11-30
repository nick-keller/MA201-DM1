#ifndef MOUSEWRAPPER_H
#define MOUSEWRAPPER_H

#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

/*
This class wraps mouse events. It handles left and right buttons, position and movement.
*/
class MouseWrapper
{
    public:
        MouseWrapper();
        enum Button { Left, Right };

        void bind(const Event& event);
        const Vector2f getMovement();
        const Vector2f getClickAt(Button btn) const;
        const int getX() const;
        const bool isBtnDown(Button btn) const;

    protected:

    private:
        Vector2f m_currentPos;
        Vector2f m_prevPos;
        Vector2f m_clickAt[2];
        bool m_buttons[2];
};

#endif // MOUSEWRAPPER_H
