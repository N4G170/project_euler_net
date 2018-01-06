#include "utils.hpp"
#include <math.h>
#include <iostream>
#include <algorithm>
#include <map>
#include <utility>
#include <array>

/**
 * @brief Count the number of digits in a number
 * @param number - the number to be processed
 * @return Number of digits in a number
 */
unsigned int NumberOfDigits(long number)
{
    //make number positive
    if (number < 0)
        number = std::labs(number);

    //long max - 18446744073709551615 - 19 digits - 64bits

    //not pretty but fast
    if (number > 999999999999999999) return 19;
    if (number > 99999999999999999) return 18;
    if (number > 9999999999999999) return 17;
    if (number > 999999999999999) return 16;
    if (number > 99999999999999) return 15;
    if (number > 9999999999999) return 14;
    if (number > 999999999999) return 13;
    if (number > 99999999999) return 12;
    if (number > 9999999999) return 11;
    if (number > 999999999) return 10;
    if (number > 99999999) return 9;
    if (number > 9999999) return 8;
    if (number > 999999) return 7;
    if (number > 99999) return 6;
    if (number > 9999) return 5;
    if (number > 999) return 4;
    if (number > 99) return 3;
    if (number > 9) return 2;

    return 1;
}

/**
 * @brief Convert a char to the number it represents
 * @param character - the character to be converted
 * @return The literal value of the char
 */
unsigned int CharToUnsignedInt(char character)
{
    return (unsigned int)(character - '0');
}

/**
 * @brief Sieve Of Eratosthenes - an implemention of the prime number sieve created by the greek mathematician Eratosthenes of Cyrene
 * @param limit - upper limit for the sieve pool
 * @return returns a vector containing the result of the sieve for every number from 0 to limit
 */
std::vector<bool> SieveOfEratosthenes(const ulong_t& limit)
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

    return primes;
}

/**
 * @brief PrimeBoolVectorToIntVector
 * @param sieve_primes - the result from a call to the funcion @see SieveOfEratosthenes(ulong_t limit)
 * @return returns a vector only with the numbers that are primes
 */
std::vector<ulong_t> PrimeBoolVectorToIntVector(std::vector<bool> sieve_primes)
{
    std::vector<ulong_t> primes;

    unsigned int i = 0;

    for(bool a : sieve_primes)
    {
        if(a)
            primes.push_back( i );
        i++;
    }

    return primes;
}

/**
 * @brief PrimeNumberPoolofSize - calculates prime numbers untils their total count == size
 * @param size - the number of primes to be found
 * @return returns vector with the prime numbers
 */
std::vector<ulong_t> PrimeNumberPoolOfSize(unsigned int size)
{
    std::vector<ulong_t> primes;

    ulong_t number = 1;

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
bool IsPrime(ulong_t number)
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
        ulong_t test_number = 5;

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
bool IsPalindrome(ulong_t number, unsigned int base)
{
    /*std::string number_str = std::to_string(number);
    std::string reversed_number_str = number_str;
    std::reverse(reversed_number_str.begin(), reversed_number_str.end());

    return number_str == reversed_number_str;*/

    ulong_t forward_number = number;
    ulong_t reversed_number = 0;

     while (number > 0)
     {
          unsigned int digit = number % base;
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
    std::map<int, std::map<ulong_t, ulong_t>> factors;//will save all factors

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
    std::map<int, std::map<ulong_t, ulong_t>> factors;//will save all factors

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
std::map<ulong_t,ulong_t> PrimeFactorsOfNumber(ulong_t number)
{
    return PrimeFactorsOfNumber(number, PrimeBoolVectorToIntVector(SieveOfEratosthenes(number)));//inefficient
}

/**
 * @brief PrimeFactorsOfNumber - Factorize a number into its prime factors
 * @param number - number to be factorized (must be positive)
 * @param prime_numbers - pool of prime numbers to be used
 * @return returns a map with the pairs of the factors and their exponent
 */
std::map<ulong_t,ulong_t> PrimeFactorsOfNumber(ulong_t number, const std::vector<ulong_t>& prime_numbers)
{
    std::map<ulong_t,ulong_t> factors;

    ulong_t number_fraction = number;

    while(number_fraction > 1)
    {
        //calculate the factors
        for(ulong_t prime : prime_numbers)
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

std::vector<ulong_t> ProperDivisors(const ulong_t& number)
{
    std::vector<ulong_t> divisors;

    for(ulong_t i = 1; i <= number/2; i++ )
    {
        if(number % i == 0)
            divisors.push_back(i);
    }

    return divisors;
}

ulong_t SumOfProperDivisors(const ulong_t& number)
{
    ulong_t sum = 0;

    for(ulong_t i = 1; i <= number/2; i++ )
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
ulong_t Factorial(ulong_t number)
{
    if(number == 0)
        return 1;

    return number * Factorial(number-1);
}

BigInt_t BigFactorial(ulong_t number)
{
    BigInt_t big_number = 1;

    for(ulong_t i = number; i > 0; i--)
    {
        big_number *= i;
    }

    return big_number;
}

ulong_t PartialFactorial(ulong_t start_number, ulong_t end_number)
{
    ulong_t number = 1;

    for(ulong_t i = end_number; i >= start_number ; i--)
    {
        number *= i;
    }

    return number;
}

BigInt_t BigPartialFactorial(ulong_t start_number, ulong_t end_number)
{
    BigInt_t big_number = 1;

    for(ulong_t i = end_number; i >= start_number ; i--)
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
        std::string str_auxilia = str;

    	str_auxilia = Trim(str_auxilia);

        while( (position = str_auxilia.find(separator)) != std::string::npos)//found next cut area
        {
            result_sting.push_back( str_auxilia.substr(0, position) );

            str_auxilia = str_auxilia.substr( position + 1);
        }

        //stores the last section as it will not run the loop
        result_sting.push_back( str_auxilia );

        return result_sting;
}

ulong_t WordAlphabeticalValue(const std::string& word, std::map<char, int>& values)
{
    ulong_t total = 0;

    for(auto letter : word)
    {
        total += values[letter];
    }

    return std::move(total);
}
//}

double Phi(const unsigned int& number, const std::map<ulong_t,ulong_t>& factors)
{
    double phi = number;
    //phi also known as Euler's totient function can be calculated using the expression
    //
    //phi(n) = n * (1 - 1/p1) * ... * (1 - 1/pn), where p1...pn are the prime factors or n

    for(auto factor : factors)
    {
        phi *= (1.0 - 1.0/(double)factor.first);
    }

    return phi;
}

long long Phi(const unsigned int& number, const std::vector<ulong_t>& primes)
{
    long long phi = number;
    int remainder = number;
    int prime = 0;
    double root = std::sqrt(number);

    for(unsigned int i = 0; i < primes.size() && prime <= root; i++)
    {
        prime = primes[i];

        if(remainder == 1)//there is nothing else to do here
            break;

        if(number % prime == 0)
        {
            //phi *= (1 - 1 / prime);//this "rule" needs the vars to be doubles or we have precision errors
            //so we can use the other version -> (1-1/prime) = prime/prime - 1/prime = (prime-1)/prime  (it is the same thing)
            phi *= (prime - 1);
            phi /= prime;

            //the while loop removes all the extra occurrence of the current prime
            //phi only need one instance of each prime factors ex: 4 = 2^2, phi only needs one 2 so we remove the other
            while(remainder % prime == 0)
                remainder /= prime;
        }
    }
    //if a number is a prime as it is bigger than 'root' we have to apply it to phi
    if(remainder > 1)
    {
        phi = phi * (remainder - 1);
        phi /= remainder;
    }

    return phi;
}

std::vector<unsigned short> GetDigits(long number)
{
    std::vector<unsigned short> digits;

    while(number!= 0)
    {
        digits.push_back( number%10 );
        number /= 10;
    }

    return digits;
}

ulong_t ConcatenateDigits(const std::vector<unsigned short>& digits)
{
    ulong_t number{0};

    for( int i =  digits.size() - 1; i >= 0; i--)
    {
        number += digits[i] * std::pow(10,i);
    }

    return number;
}

bool IsPermutation(long number_1, long number_2)
{
    std::array<short, 10> digits_count{{ 0,0,0,0,0,0,0,0,0,0 }};//only in C++11 we need to use {{}}. since c++14, {} are ok, but since my lint keeps marking it with a warnning, I used {{}}

    while(number_1 != 0)
    {
        digits_count[ number_1 % 10 ]++;
        number_1 /= 10;
    }

    while(number_2 != 0)
    {
        digits_count[ number_2 % 10 ]--;
        number_2 /= 10;
    }

    for( short digit_count : digits_count)
        if(digit_count > 0)
            return false;

    return true;
}
