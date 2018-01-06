#ifndef FRACTION_HPP
#define FRACTION_HPP

#include <string>

template<typename T>
class Fraction
{
    private:
        T m_numerator;
        T m_denominator;
        double m_ratio;
    public:
        T Numerator() const { return m_numerator; }
        void Numerator(const T& numerator) { m_numerator = numerator; UpdateRatio(); }

        T Denominator() const { return m_denominator; }
        void Denominator(const T& denominator) { m_denominator = denominator; UpdateRatio(); }

        double Ratio() const { return m_ratio; }
        //void Ratio(const double& ratio) { m_ratio = ratio; }

    public:
        Fraction();
        Fraction(T numerator, T denominator);
        Fraction(const Fraction<T>& other);

        Fraction& operator = (const Fraction<T>& other);

        ~Fraction();


        bool operator < (const Fraction<T>& other) const;
        bool operator <= (const Fraction<T>& other) const;
        bool operator > (const Fraction<T>& other) const;
        bool operator >= (const Fraction<T>& other) const;
        bool operator == (const Fraction<T>& other) const;
        bool Equals (const T& numerator, const T& denominator) const;
        bool LessThan (const T& numerator, const T& denominator) const;
        bool LessThanEquals (const T& numerator, const T& denominator) const;
        bool GreaterThan (const T& numerator, const T& denominator) const;
        bool GreaterThanEquals (const T& numerator, const T& denominator) const;

        bool operator() (const Fraction<T>& left_fraction, const Fraction<T>& right_fraction) const;//used by multiset

        std::string ToString(bool remove_decimals = true) const;
        void UpdateRatio();
};

#endif//FRACTION_HPP
