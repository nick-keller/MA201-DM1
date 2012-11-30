#ifndef AXIS_H
#define AXIS_H

#include <cstdlib>
#include <iostream>
#include "MouseWrapper.h"
#include <SFML/Graphics.hpp>

using namespace sf;

/*
Handles axis rendering, events and view.
*/
class Axis
{
    public:
        Axis(RenderWindow& app, MouseWrapper& mouse);

        void render() const;
        void update();
        void reset();

        const FloatRect& getBoundaries() const;
        const Vector2f getZoom() const;
        const Vector2f getCursorPos() const;

    protected:
        void move(Vector2f dir);
        void zoom(Vector2f dir);

    private:
        void updateView();

        RenderWindow& m_app;
        MouseWrapper& m_mouse;
        View m_view;
};

#endif // AXIS_H
