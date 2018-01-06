#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <map>
#include <string>

#include "defines.hpp"

/**
 * @brief Count the number of digits in a number
 * @param number - the number to be processed
 * @return Number of digits in a number
 */
unsigned int NumberOfDigits(long number);

/**
 * @brief Convert a char to the number it represents
 * @param character - the character to be converted
 * @return The literal value of the char
 */
unsigned int CharToUnsignedInt(char character);

/**
 * @brief Sieve Of Eratosthenes - an implemention of the prime number sieve created by the greek mathematician Eratosthenes of Cyrene
 * @param limit - upper limit for the sieve pool
 * @return returns a vector containing the result of the sieve for every number from 0 to limit
 */
std::vector<bool> SieveOfEratosthenes(const ulong_t& limit);

/**
 * @brief PrimeBoolVectorToIntVector
 * @param sieve_primes - the result from a call to the funcion @see SieveOfEratosthenes(ulong_t limit)
 * @return returns a vector only with the numbers that are primes
 */
std::vector<ulong_t> PrimeBoolVectorToIntVector(std::vector<bool> sieve_primes);

/**
 * @brief PrimeNumberPoolofSize - calculates prime numbers untils their total count == size
 * @param size - the number of primes to be found
 * @return returns vector with the prime numbers
 */
std::vector<ulong_t> PrimeNumberPoolOfSize(unsigned int size);

/**
 * @brief IsPrime - check if a number is prime (this implementations is based on the rule "All primes greater than 3 can be written in the form 6k+/-1.")
 * @param number - the number to be checked
 * @return true/false - is the given number a prime
 */
bool IsPrime(ulong_t number);

/**
 * @brief IsPalindrome - check if a given number is a palindrome (you can read it the same way left -> right and right -> left)
 * @param number - the number to be checked
 * @return true/false - if the number is or is not a palindrome
 */
bool IsPalindrome(ulong_t number, unsigned int base = 10);

/**
 * @brief GeneratePalindrome - Generates a plalindrome based on a numbers in a given base
 * @param odd_digit_count - generates a odd digit count palindrome or not (ex: odd->12321; even->123321)
 * @return the generated palindrome
 */
unsigned int GeneratePalindrome(unsigned int base_number, unsigned int base, bool odd_digit_count);


/**
 * @brief LeastCommonMultiple - implementation of a least common multiple (lcm) of a list of numbers
 * @param numbers - list of the number to be used in the calculation of the lcm
 * @return the lcm for the received list of numbers
 *
 */
int LeastCommonMultiple(std::vector<int> numbers);

/**
 * @brief LeastCommonMultiple - implementation of a least common multiple (lcm) of only two numbers
 * @param numbers - list of the number to be used in the calculation of the lcm
 * @return the lcm for the received list of numbers
 */
int LeastCommonMultiple(int a, int b);

/**
 * @brief GreatestCommonDivisor - implementation of the Euclidean algorithm for GDC calculation
 * @param a, b - numbers of which we calculate the gcd
 * @return the gcd of 'a' and 'b'
 */
int GreatestCommonDivisor(int a, int b);

/**
 * @brief PrimeFactorsOfNumber - Factorize a number into its prime factors(inefficient implementation)
 * @param number - number to be factorized (must be positive)
 * @return returns a map with the pairs of the factors and their exponent
 */
std::map<ulong_t,ulong_t> PrimeFactorsOfNumber(ulong_t number);

/**
 * @brief PrimeFactorsOfNumber - Factorize a number into its prime factors
 * @param number - number to be factorized (must be positive)
 * @param prime_numbers - pool of prime numbers to be used
 * @return returns a map with the pairs of the factors and their exponent
 */
std::map<ulong_t,ulong_t> PrimeFactorsOfNumber(ulong_t number, const std::vector<ulong_t>& prime_numbers);

/**
 * @brief Calculates the proper divisors (mod == 0) of a given number
 * @return std::vector with all the proper divisors
 */
std::vector<ulong_t> ProperDivisors(const ulong_t& number);

/**
 * @brief Calculates the proper divisors (mod == 0) of a given number and calculats its sum
 * @return Sum of all the proper divisors
 */
ulong_t SumOfProperDivisors(const ulong_t& number);

/**
 * @brief Check if two numbers form two consecutives links of a chain
 * (NOTE:10 function specific to a single problem, may need to make generic in the future, or change to lamda)
 * @param divisor - the factor to be used as the left and right
 * @return Whether or not the numbers form links of a chain
 */
bool AreChainNumbers(unsigned int left, unsigned int right, unsigned int divisor);

//{ Factorial
/**
 * @brief Calculates Factorial of a number
 * @return The factorial
 */
ulong_t Factorial(ulong_t number);

/**
 * @brief Calculates Factorial of a number, using GMP big numbers
 * @return The GMP big number factorial
 */
BigInt_t BigFactorial(ulong_t number);

/**
 * @brief Calculates a partial factorial of a number
 * @return The partial factorial
 */
ulong_t PartialFactorial(ulong_t start_number, ulong_t end_number);

/**
 * @brief Calculates a partial factorial of a number, using GMP big numbers
 * @return The GMP big number partial factorial
 */
BigInt_t BigPartialFactorial(ulong_t start_number, ulong_t end_number);
//}

//{ String Manipulation
/**
 * @brief Trims whitespaces from the left and right of a string
 * Calls TrimLeft and TrimRight internally
 * @return The trimmed string
 */
std::string Trim(const std::string& str);
/**
 * @brief Trims a specific std::string from the left and right of a string
 * Calls TrimLeft and TrimRight internally
 * @return The trimmed string
 */
std::string Trim(const std::string& str, const std::string& target);

/**
 * @brief Trims whitespaces from the left of a string
 * @return The trimmed string
 */
std::string TrimLeft(const std::string& str);
/**
 * @brief Trims whitespaces from the right of a string
 * @return The trimmed string
 */
std::string TrimRight(const std::string& str);

/**
 * @brief Trims a specific std::string from the left of a string
 * @return The trimmed string
 */
std::string TrimLeft(const std::string& str, const std::string& target);
/**
 * @brief Trims a specific std::string from the right of a string
 * @return The trimmed string
 */
std::string TrimRight(const std::string& str, const std::string& target);

/**
 * @brief Breaks the string in sub strings every time the given separator is found
 * @return std::vector with the substrings
 */
std::vector< std::string > Explode(const std::string& str, const std::string& separator);

/**
 * @brief Calculates the alphabetical value of a word, based on the position of each letter in the alphabet
 * @return The alphabetical value
 */
ulong_t WordAlphabeticalValue(const std::string& word, std::map<char, int>& values);

//}


double Phi(const unsigned int& number, const std::map<ulong_t,ulong_t>& factors);
long long Phi(const unsigned int& number, const std::vector<ulong_t>& primes);
bool IsPermutation(long number_1, long number_2);

std::vector<unsigned short> GetDigits(long number);
ulong_t ConcatenateDigits(const std::vector<unsigned short>& digits);



#endif // UTILS_HPP
