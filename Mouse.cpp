#include "Mouse.h"

MouseWrapper::MouseWrapper()
{
    Vector2f pos = Vector2f(0,0);
    Vector2f presPos = Vector2f(0,0);
}

void MouseWrapper::bind(Event& event)
{
    if(event.Type == Event::MouseMoved)
    {
        //MouseWrapper::presPos = MouseWrapper::pos;
        //MouseWrapper::pos = Vector2f(event.MouseMove.X, event.MouseMove.Y);
    }
}

int MouseWrapper::getX()
{
    return 0;
}
