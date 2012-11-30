#ifndef SININTEGRAL_H
#define SININTEGRAL_H

#include "Function.h"

/*
\int_{0}^{x}\frac{sin(t)}{t}dt
*/
class SinIntegral : public Function
{
    public:
        SinIntegral(Axis& axis, float precision);

        virtual const bool nextOrder(const int& k, const float& x) const;
        virtual double partialSum(const float& x, const int& k) const;

    protected:

    private:

};

#endif // SININTEGRAL_H
