#include "MouseWrapper.h"

MouseWrapper::MouseWrapper() : m_currentPos(0,0), m_prevPos(0,0)
{
    m_buttons[Left] = false;
    m_buttons[Right] = false;
    m_clickAt[Left] = Vector2f(0,0);
    m_clickAt[Right] = Vector2f(0,0);
}

void MouseWrapper::bind(const Event& event)
{
    // Handle mouse position
    if(event.Type == Event::MouseMoved)
    {
        m_prevPos = m_currentPos;
        m_currentPos = Vector2f(event.MouseMove.X, event.MouseMove.Y);
    }

    // Handle button release
    else if(event.Type == Event::MouseButtonReleased)
    {
        if(event.MouseButton.Button == Mouse::Left)
            m_buttons[Left] = false;
        if(event.MouseButton.Button == Mouse::Right)
            m_buttons[Right] = false;
    }

    // Handle button press
    else if(event.Type == Event::MouseButtonPressed)
    {
        if(event.MouseButton.Button == Mouse::Left)
        {
            m_buttons[Left] = true;
            m_clickAt[Left] = m_currentPos;
        }
        if(event.MouseButton.Button == Mouse::Right)
        {
            m_buttons[Right] = true;
            m_clickAt[Right] = m_currentPos;
        }
    }
}

const Vector2f MouseWrapper::getMovement()
{
    // Calculate dx and dy
    Vector2f r = m_currentPos - m_prevPos;
    m_prevPos = m_currentPos;
    return r;
}

const Vector2f MouseWrapper::getClickAt(Button btn) const
{
    return m_clickAt[btn];
}

const bool MouseWrapper::isBtnDown(Button btn) const
{
    return m_buttons[btn];
}

const int MouseWrapper::getX() const
{
    return m_currentPos.x;
}
