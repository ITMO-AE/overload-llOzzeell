#include "rational.h"

Rational::Rational(int numerator, int denomenator):negative(false)
{
    Rational::MakeRational(numerator, denomenator);
}

void Rational::MakeRational(int num, int denom)
{
    if(num == 0)
    {
        numerator = num;
        denominator = 1;
    }
    else
    {
        int gdc = getGCD(num, denom);
        numerator = gdc > 1? abs(num) / gdc : abs(num);
        denominator = gdc > 1? abs(denom) / gdc : abs(denom);

        if((num < 0 || denom < 0) && !(num < 0 && denom < 0))
        {
            numerator = (numerator * -1);
            negative = true;
        }
    }
}

int Rational::Numerator() const
{
    return numerator;
}

int Rational::Denominator() const
{
    return denominator;
}

bool Rational::isEqualByAbs(const Rational &rat) const
{
    if(abs(numerator) == abs(rat.numerator) && denominator == rat.denominator) return true;
    else return false;
}

bool Rational::isNegative() const
{
    return negative;
}

std::ostream& operator << (std::ostream &out, const Rational &rat)
{
    out << rat.numerator << '/' << rat.denominator;
    return out;
}

std::istream& operator >> (std::istream &in, Rational &rat)
{
    if(in.rdbuf()->in_avail())
    {
        int a,b;
        char k;
        in >> a>>k>>b;
        rat.MakeRational(a,b);
    }

    return in;
}

bool operator == (const Rational &rat1, const Rational &rat2)
{
    return (rat1.numerator == rat2.numerator && rat1.denominator == rat2.denominator);
}

bool operator != (const Rational &rat1, const Rational &rat2)
{
    return !(rat1.numerator == rat2.numerator && rat1.denominator == rat2.denominator);
}
