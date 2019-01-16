#ifndef RATIONAL_H
#define RATIONAL_H
#include <cmath>
#include <iostream>
#include <cassert>

// Шаблон функции нахождения наибольшего общего делителя
// рекурсивный алгоритм Евклида
// Ну мало ли класс переедет на long? а так да, избыточно.
template<typename T>
T getGCD(T a, T b)
{
    a = abs(a);
    b = abs(b);

    if (a == b)return a;
    if (a > b)std::swap(a, b);
    return getGCD(a, b - a);
}

template<typename T>
T getLCM(T a, T b)
{
    return (a * b) / getGCD(a, b);
}

class Rational
{
public:
    Rational():numerator(0), denominator(1), negative(false){}
    Rational(int numerator, int denominator);

    int Numerator() const;
    int Denominator() const;
    bool isEqualByAbs(const Rational &rat) const;
    bool isNegative() const;

    friend std::ostream& operator << (std::ostream &out, const Rational &rat);

    friend std::istream& operator >> (std::istream &in, Rational &rat);

    friend bool operator == (const Rational &rat1, const Rational &rat2);

    friend bool operator != (const Rational &rat1, const Rational &rat2);

    Rational operator + (const Rational &rat)
    {
        if(denominator == rat.denominator) return Rational(numerator + rat.numerator, denominator);
        else
        {
            int lcm = getLCM(denominator, rat.denominator);
            return Rational(   (numerator*(lcm/denominator)) + (rat.numerator*(lcm/rat.denominator)) , lcm  );
        }
    }

    Rational operator - (const Rational &rat)
    {
        if(denominator == rat.denominator) return Rational(numerator - rat.numerator, denominator);
        else
        {
            int lcm = getLCM(denominator, rat.denominator);
            return Rational(   (numerator*(lcm/denominator)) - (rat.numerator*(lcm/rat.denominator)) , lcm  );
        }
    }

    Rational operator * (const Rational &rat)
    {
        return Rational(numerator * rat.numerator, denominator * rat.denominator);
    }

    Rational operator / (const Rational &rat)
    {
        assert(rat.numerator != 0);
        return (Rational(numerator, denominator) * Rational(rat.isNegative()?(rat.denominator*-1):rat.denominator, abs(rat.numerator)));
        //return (Rational(numerator, denominator) * Rational(rat.denominator,rat.numerator));
    }

private:
    int numerator;
    int denominator;
    bool negative;

    void MakeRational(int num, int denom);
};

#endif // RATIONAL_H
