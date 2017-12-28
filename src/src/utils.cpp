#include "utils.hpp"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <map>
#include <utility>

/**
 * @brief Sieve Of Eratosthenes - an implemention of the prime number sieve created by the greek mathematician Eratosthenes of Cyrene
 * @param limit - upper limit for the sieve pool
 * @return returns a vector containing the result of the sieve for every number from 0 to limit
 */
std::vector<bool> SieveOfEratosthenes(const unsigned long& limit)
{
    std::vector<bool> primes(limit + 1, true);//0 is included because we use the index to identify the number

    primes[0] = false;//0 not prime
    primes[1] = false;//1 not prime
    double root = floor(sqrt(limit));

    //will only calculate up to the root of the number, because between the number and its square root, only the number itself is a divisor
    for(unsigned int i = 2; i <= root; i++)
    {
        //mark as false evry power of the current number in i
        for(unsigned int j=i*i; j <= limit; j+=i)
        {
            primes[j]=false;
        }
    }

    return std::move(primes);
}

/**
 * @brief PrimeBoolVectorToIntVector
 * @param sieve_primes - the result from a call to the funcion @see SieveOfEratosthenes(unsigned long limit)
 * @return returns a vector only with the numbers that are primes
 */
std::vector<unsigned long> PrimeBoolVectorToIntVector(std::vector<bool> sieve_primes)
{
    std::vector<unsigned long> primes;

    unsigned int i = 0;

    for(bool a : sieve_primes)
    {
        if(a)
            primes.push_back( i );
        i++;
    }

    return std::move(primes);
}

/**
 * @brief PrimeNumberPoolofSize - calculates prime numbers untils their total count == size
 * @param size - the number of primes to be found
 * @return returns vector with the prime numbers
 */
std::vector<unsigned long> PrimeNumberPoolOfSize(unsigned int size)
{
    std::vector<unsigned long> primes;

    unsigned long number = 1;

    while(primes.size() < size)
    {
        if(IsPrime((number)))
        {
            primes.insert(primes.end(), number);
        }

        number++;
    }

    return primes;
}

/**
 * @brief IsPrime - check if a number is prime (this implementations is based on the rule "All primes greater than 3 can be written in the form 6k+/-1.")
 * @param number - the number to be checked
 * @return true/false - is the given number a prime
 */
bool IsPrime(unsigned long number)
{
    if(number <= 1)
        return false;
    else if(number < 4)//includes 2 and 3
        return true;
    else if(number % 2 == 0)//all pair bigger than 2 are NOT primes
        return false;
    else if(number < 9)//includes 5 and 7
        return true;
    else if(number % 3 == 0)
        return false;
    else//All primes greater than 3 can be written in the form 6k+/-1.
    {
        double root = std::sqrt(number);
        unsigned long test_number = 5;

        while(test_number <= root)
        {
            if(number % test_number == 0)
                return false;
            if(number % (test_number + 2) == 0)
                return false;

            test_number += 6;
        }

        return true;
    }

}


/**
 * @brief IsPalindrome - check if a given number is a palindrome (you can read it the same way left -> right and right -> left)
 * @param number - the number to be checked
 * @return true/false - if the number is or is not a palindrome
 */
bool IsPalindrome(unsigned long long number, unsigned int base)
{
    /*std::string number_str = std::to_string(number);
    std::string reversed_number_str = number_str;
    std::reverse(reversed_number_str.begin(), reversed_number_str.end());

    return number_str == reversed_number_str;*/

    unsigned long long forward_number = number;
    unsigned long long reversed_number = 0;
    unsigned int digit;

     while (number > 0)
     {
          digit = number % base;
          reversed_number = reversed_number * base + digit;
          number = number / base;
     }
     return (forward_number == reversed_number);
}

unsigned int GeneratePalindrome(unsigned int base_number, unsigned int base, bool odd_digit_count)
{
    unsigned int palindrome = base_number;

    if(odd_digit_count)
        base_number /= base; //remove the last digit as it will not be doubled, EX: base_number = 123, palindrome will be 12321 so we remove the 3 to not double it

    while(base_number > 0)
    {
        palindrome = palindrome * base + base_number % base;//add the remainder. palindrome * base will shift the number one place to the left
        base_number /= base;//remove the digit we added to the palindrome
    }

    return palindrome;
}

/**
 * @brief LeastCommonMultiple - implementation of a least common multiple (lcm) of a list of numbers
 * @param numbers - list of the number to be used in the calculation of the lcm
 * @return the lcm for the received list of numbers
 *
 */
int LeastCommonMultiple(std::vector<int> numbers)
{
    std::map<int, std::map<unsigned long, unsigned long>> factors;//will save all factors

    for(int number : numbers)
    {
        if(number > 1)//1 is not a prime and cannot be factorized
            factors[number] = PrimeFactorsOfNumber(number);
    }

    std::map<unsigned int, unsigned int> highest_powers;

    for(auto& n : factors)//find highest powers of factors
    {
        for(auto& factor : n.second)//each prime factor for the number in n.first
        {
            std::map<unsigned int,unsigned int>::iterator it = highest_powers.find(factor.first);//try to find the corrent prime factor in the highest powers map

            if(it == highest_powers.end())//does not exist
            {
                highest_powers[factor.first] = factor.second;
            }
            else
            {
                if(highest_powers[factor.first] < factor.second)//found higher power
                    highest_powers[factor.first] = factor.second;
            }
        }
    }

    //calculate lcm
    int lcm = 1;

    for(auto& factor : highest_powers)
    {
        lcm *= std::pow(factor.first, factor.second);
    }

    return lcm;
}

int LeastCommonMultiple(int a, int b)
{
    std::map<int, std::map<unsigned long, unsigned long>> factors;//will save all factors

    factors[a] = PrimeFactorsOfNumber(a);
    factors[b] = PrimeFactorsOfNumber(b);

    std::map<unsigned int, unsigned int> highest_powers;

    for(auto& n : factors)//find highest powers of factors
    {
        for(auto& factor : n.second)//each prime factor for the number in n.first
        {
            std::map<unsigned int,unsigned int>::iterator it = highest_powers.find(factor.first);//try to find the corrent prime factor in the highest powers map

            if(it == highest_powers.end())//does not exist
            {
                highest_powers[factor.first] = factor.second;
            }
            else
            {
                if(highest_powers[factor.first] < factor.second)//found higher power
                    highest_powers[factor.first] = factor.second;
            }
        }
    }

    //calculate lcm
    int lcm = 1;

    for(auto& factor : highest_powers)
    {
        lcm *= std::pow(factor.first, factor.second);
    }

    return lcm;
}

int GreatestCommonDivisor(int a, int b)
{
    while (a != b)
    {
        if(a > b)
           a = a - b;
        else
           b = b - a;
    }

    return a;
}

/**
 * @brief PrimeFactorsOfNumber - Factorize a number into its prime factors (inefficient implementation)
 * @param number - number to be factorized (must be positive)
 * @return returns a map with the pairs of the factors and their exponent
 */
std::map<unsigned long,unsigned long> PrimeFactorsOfNumber(unsigned long number)
{
    return PrimeFactorsOfNumber(number, PrimeBoolVectorToIntVector(SieveOfEratosthenes(number)));//inefficient
}

/**
 * @brief PrimeFactorsOfNumber - Factorize a number into its prime factors
 * @param number - number to be factorized (must be positive)
 * @param prime_numbers - pool of prime numbers to be used
 * @return returns a map with the pairs of the factors and their exponent
 */
std::map<unsigned long,unsigned long> PrimeFactorsOfNumber(unsigned long number, const std::vector<unsigned long>& prime_numbers)
{
    std::map<unsigned long,unsigned long> factors;

    unsigned long number_fraction = number;

    while(number_fraction > 1)
    {
        //calculate the factors
        for(unsigned long prime : prime_numbers)
        {
            if(number_fraction % prime == 0)//valid prime
            {
                if(factors.count(prime) == 0)//does not exist (map.count(key) return 1 or 0 since it does not allow duplicates)
                {
                    factors[prime] = 1;
                }
                else //increment prime factor exponent
                {
                    factors[prime]++;
                }

                number_fraction = number_fraction / prime;//"factorize" the number
                break;//restart the prime_numbers loop
            }
        }

    }

    return factors;
}

std::vector<unsigned long> ProperDivisors(const unsigned long& number)
{
    std::vector<unsigned long> divisors;

    for(unsigned long i = 1; i <= number/2; i++ )
    {
        if(number % i == 0)
            divisors.push_back(i);
    }

    return std::move(divisors);
}

unsigned long SumOfProperDivisors(const unsigned long& number)
{
    unsigned long sum = 0;

    for(unsigned long i = 1; i <= number/2; i++ )
    {
        if(number % i == 0)
            sum += i;
    }

    return std::move(sum);
}

bool AreChainNumbers(unsigned int left, unsigned int right, unsigned int divisor)
{
    return left%divisor == (unsigned int)(right/divisor); //if divisor = 100; 2 end digits of left == 2 start digits on right
}

//{ Factorial
unsigned long Factorial(unsigned long number)
{
    if(number == 0)
        return 1;

    return number * Factorial(number-1);
}

BigInt_t BigFactorial(unsigned long number)
{
    BigInt_t big_number = 1;

    for(unsigned long i = number; i > 0; i--)
    {
        big_number *= i;
    }

    return big_number;
}

unsigned long PartialFactorial(unsigned long start_number, unsigned long end_number)
{
    unsigned long number = 1;

    for(unsigned long i = end_number; i >= start_number ; i--)
    {
        number *= i;
    }

    return number;
}

BigInt_t BigPartialFactorial(unsigned long start_number, unsigned long end_number)
{
    BigInt_t big_number = 1;

    for(unsigned long i = end_number; i >= start_number ; i--)
    {
        big_number *= i;
    }

    return big_number;
}
//}

//{ String Manipulation

std::string Trim(const std::string& str)
{
    return TrimLeft(TrimRight(str));
}

std::string TrimLeft(const std::string& str)
{
    std::size_t position = str.find_first_not_of(" ");

    if(position == std::string::npos)//empty str or only " "
        return "";

    //will remove everything prior to the position
    return str.substr( position );
}

std::string TrimRight(const std::string& str)
{
    std::size_t position = str.find_last_not_of(" ");

    if(position == std::string::npos)//empty str or only " "
        return "";

    //will remove everything after to the position + 1 (+1 because the position is an index and substr needs a length, so from 0 to position+1)
    return str.substr( 0, position+1 );
}


std::string Trim(const std::string& str, const std::string& target)
{
    return TrimLeft(TrimRight(str, target), target);
}

std::string TrimLeft(const std::string& str, const std::string& target)
{
    std::size_t position = str.find_first_not_of(target);

    if(position == std::string::npos)//empty str or only " "
        return "";

    //will remove everything prior to the position
    return str.substr( position );
}

std::string TrimRight(const std::string& str, const std::string& target)
{
    std::size_t position = str.find_last_not_of(target);

    if(position == std::string::npos)//empty str or only " "
        return "";

    //will remove everything after to the position + 1 (+1 because the position is an index and substr needs a length, so from 0 to position+1)
    return str.substr( 0, position+1 );
}

std::vector< std::string > Explode(const std::string& str, const std::string& separator)
{
        std::vector< std::string > result_sting;
    	std::string::size_type position;
        std::string str_auxilua = str;

    	str_auxilua = Trim(str_auxilua);

        while( (position = str_auxilua.find(separator)) != std::string::npos)//found next cut area
        {
            result_sting.push_back( std::move( str_auxilua.substr(0, position)) );

            str_auxilua = str_auxilua.substr( position + 1);
        }

        //stores the last section as it will not run the loop
        result_sting.push_back( str_auxilua );

        return std::move( result_sting );
}

unsigned long WordAlphabeticalValue(const std::string& word, std::map<char, int>& values)
{
    unsigned long total = 0;

    for(auto letter : word)
    {
        total += values[letter];
    }

    return std::move(total);
}
//}
