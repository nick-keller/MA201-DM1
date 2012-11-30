#include "ExpIntegral.h"

ExpIntegral::ExpIntegral(Axis& axis, float precision) : Function(axis, precision, 3.f, Color(33,82,182))
{
    m_limit = 0.88622692545;
}

double ExpIntegral::partialSum(const float& x, const int& k) const
{
    return (double)( pow(-1, k) * pow(x, 2*k+1) )/( (double)(2*k+1)*this->fact(k) );
}

const bool ExpIntegral::nextOrder(const int& n, const float& x) const
{
    return n<40;
}
