#include "Function.h"

Function::Function(Axis& axis, float precision, float stopAt, Color color) : m_axis(axis), m_precision(precision), m_color(color), m_limit(0), m_stopAt(stopAt)
{
}

void Function::render(const float cursorX, const bool drawTangent) const
{
    const FloatRect& boundaries = m_axis.getBoundaries();
    const Vector2f zoom = m_axis.getZoom();

    // Draw asymptotes (dashed line)
    glBegin(GL_LINES);
        glColor3ub(115, 191, 78);

        // Draw infinite asymptote
        for(float i(0); i<boundaries.Right; i += 20.f/zoom.x)
        {
            glVertex2d(i, -m_limit);
            glVertex2d(i+8.f/zoom.x, -m_limit);
        }

        // Draw -infinite asymptote
        for(float i(0); i>boundaries.Left; i -= 20.f/zoom.x)
        {
            glVertex2d(i, m_limit);
            glVertex2d(i-8.f/zoom.x, m_limit);
        }
    glEnd();

    // Draw tangent
    double fCursor = this->forX(cursorX);
    if(drawTangent)
    {
        // Calculate local derivate
        float coef = ( this->forX(cursorX+1.f/zoom.x) - this->forX(cursorX-1.f/zoom.x) ) / ( 2.f/zoom.x );
        float length = boundaries.Right-boundaries.Left;
        glBegin(GL_LINES);
            glColor3ub(243, 159, 39);
            glVertex2d(cursorX-length, -(fCursor-length*coef));
            glVertex2d(cursorX+length, -(fCursor+length*coef));
        glEnd();
    }

    // Draw function
    glBegin(GL_LINE_STRIP);
        glColor3ub(m_color.r, m_color.g, m_color.b);
        for(float i(boundaries.Left); i <= boundaries.Right; i += 2.f/zoom.x)
            glVertex2d(i, -this->forX(i));
    glEnd();

    // Draw f(cursor)
    glBegin(GL_QUADS);
        glVertex2d(cursorX, -fCursor+5.f/zoom.y);
        glVertex2d(cursorX+5.f/zoom.x, -fCursor);
        glVertex2d(cursorX, -fCursor-5.f/zoom.y);
        glVertex2d(cursorX-5.f/zoom.x, -fCursor);
    glEnd();
}

const float Function::forX(const float& x) const
{
    if(x > m_stopAt || x < -m_stopAt)
        return x>0 ? m_limit : -m_limit;

    double sum(0);

    // Estimate infinite sum
    for(int k(0); this->nextOrder(k, x); ++k)
        sum += this->partialSum(x, k);

    return (float)sum;
}

double Function::partialSum(const float& x, const int& k) const
{
    // Calculate partial sum for x and k
    return 0;
}

const bool Function::nextOrder(const int& n, const float& x) const
{
    // Check if we need to calculate next order
    return false;
}

double Function::fact(const int n) const
{
    double r(1);

    // Calculate factorial of n
    for(int i(2); i<=n; ++i)
        r *= i;

    return r;
}
