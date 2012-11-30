#include "SinIntegral.h"

SinIntegral::SinIntegral(Axis& axis, float precision) : Function(axis, precision, 36.2f, Color(197,21,21))
{
    m_limit = 1.57079632679;
}

double SinIntegral::partialSum(const float& x, const int& k) const
{
    return (double)( pow(-1, k) * pow(x, 2*k+1) )/( (double)(2*k+1)*this->fact(2*k+1) );
}

const bool SinIntegral::nextOrder(const int& n, const float& x) const
{
    return n<50;
}
