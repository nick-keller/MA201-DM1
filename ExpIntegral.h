#ifndef EXPINTEGRAL_H
#define EXPINTEGRAL_H

#include "Function.h"

/*
\int_{0}^{x}e^{-t^{2}}dt
*/
class ExpIntegral : public Function
{
    public:
        ExpIntegral(Axis& axis, float precision);

        virtual const bool nextOrder(const int& k, const float& x) const;
        virtual double partialSum(const float& x, const int& k) const;

    protected:

    private:
};

#endif // EXPINTEGRAL_H
