#include "fraction.hpp"
#include <cmath>

template< typename T >
Fraction<T>::Fraction():m_numerator{0}, m_denominator{1}
{
    UpdateRatio();
}

template< typename T >
Fraction<T>::Fraction(T numerator, T denominator):m_numerator{numerator}, m_denominator{denominator}
{
    UpdateRatio();
}

template< typename T >
Fraction<T>::Fraction(const Fraction<T>& other)
{
    this->m_numerator = other.m_numerator;
    this->m_denominator = other.m_denominator;
    this->m_ratio = other.m_ratio;
}

template< typename T >
Fraction<T>& Fraction<T>::operator = (const Fraction<T>& other)
{
    if(this == &other)
        return *this;

    this->m_numerator = other.m_numerator;
    this->m_denominator = other.m_denominator;
    this->m_ratio = other.m_ratio;

    return *this;
}

template< typename T >
Fraction<T>::~Fraction()
{

}

template< typename T >
bool Fraction<T>::operator < (const Fraction<T>& other) const
{
    return m_ratio < other.m_ratio;
}

template< typename T >
bool Fraction<T>::operator <= (const Fraction<T>& other) const
{
    return m_ratio <= other.m_ratio;
}

template< typename T >
bool Fraction<T>::operator > (const Fraction<T>& other) const
{
    return m_ratio > other.m_ratio;
}

template< typename T >
bool Fraction<T>::operator >= (const Fraction<T>& other) const
{
    return m_ratio >= other.m_ratio;
}

template< typename T >
bool Fraction<T>::operator == (const Fraction<T>& other) const
{
    return m_numerator == other.Numerator() && m_denominator == other.Denominator();
}

template< typename T >
bool Fraction<T>::Equals(const T& numerator, const T& denominator) const
{
    return m_numerator == numerator && m_denominator == denominator;
}

template< typename T >
bool Fraction<T>::LessThan (const T& numerator, const T& denominator) const
{
    return m_ratio < ( (double)numerator / denominator );
}

template< typename T >
bool Fraction<T>::LessThanEquals (const T& numerator, const T& denominator) const
{
    return m_ratio <= ( (double)numerator / denominator );
}

template< typename T >
bool Fraction<T>::GreaterThan (const T& numerator, const T& denominator) const
{
    return m_ratio > ( (double)numerator / denominator );
}

template< typename T >
bool Fraction<T>::GreaterThanEquals (const T& numerator, const T& denominator) const
{
    return m_ratio >= ( (double)numerator / denominator );
}

template< typename T >
bool Fraction<T>::Fraction::operator() (const Fraction& left_fraction, const Fraction& right_fraction) const//used by multiset
{
    return left_fraction.m_ratio < right_fraction.m_ratio;
}

template< typename T >
std::string Fraction<T>::ToString(bool remove_decimals) const
{
    if(remove_decimals)
        return std::to_string( static_cast<int>(m_numerator) )+"/"+std::to_string( static_cast<int>(m_denominator) );
    return std::to_string( m_numerator )+"/"+std::to_string( m_denominator );
}

template< typename T >
void Fraction<T>::UpdateRatio()
{
    m_ratio = m_numerator / m_denominator;
}

template<>
void Fraction<int>::UpdateRatio() { m_ratio = (double)m_numerator / m_denominator; }

template<>
void Fraction<short>::UpdateRatio() { m_ratio = (double)m_numerator / m_denominator; }

template<>
void Fraction<long>::UpdateRatio() { m_ratio = (double)m_numerator / m_denominator; }

template class Fraction<int>;
template class Fraction<double>;
