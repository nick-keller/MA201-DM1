#ifndef FUNCTION_H
#define FUNCTION_H

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Axis.h";

/*
Base class for functions which can be written as a power serie.
It handles OpenGL rendering, asymptote rendering and rough estimate.
*/
class Function
{
    public:
        Function(Axis& axis, float precision, float stopAt, Color color = Color(255,0,0));

        void render(const float cursorX, const bool drawTangent) const;

        virtual const float forX(const float& x) const;
        virtual const bool nextOrder(const int& k, const float& x) const;
        virtual double partialSum(const float& x, const int& k) const;

    protected:
        double fact(const int n) const;

        double m_limit;
        float m_precision;

    private:
        Axis& m_axis;
        Color m_color;
        float m_stopAt;
};

#endif // FUNCTION_H
