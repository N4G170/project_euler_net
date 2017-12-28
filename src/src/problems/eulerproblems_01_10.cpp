#include "eulerproblems.h"
#include <vector>
#include <list>
#include "utils.hpp"
#include <math.h>
#include <iostream>
#include "defines.hpp"//big numbers
#include <string>
#include <fstream>//files

#include "message_writer.h"
#include "clock.h"

/**
 * \brief <a href="https://projecteuler.net/problem=1" target="blank" > Project Euler Problem 1 </a> - Multiples of 3 and 5
 * \details Find the sum of all the multiples of 3 or 5 below 1000.
 */
void Problem001()
{
    //auto clock_id = Clock::Instance()->StartClock();

    int limit = 1000;
    int sum = 0;

    for(int i=0; i<limit; i++)
        if(i%3 == 0 || i%5 == 0)
            sum += i;

    ProblemsResults::Instance()->SetStoredResult("1", std::to_string(sum));
    //MessageWriter::Instance()->WriteToOutputBox("P001: "+std::to_string(sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P001: "+std::to_string(sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

/**
 * \brief <a href="https://projecteuler.net/problem=2" target="blank" > Project Euler Problem 2 </a> - Even Fibonacci numbers
 * \details By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.
 */
void Problem002()
{
    //auto clock_id = Clock::Instance()->StartClock();

    int limit = 4000000;
    int sum = 0;
    int previous_1 = 1;
    int previous_2 = 1;
    int current = 0;

    while(previous_1 < limit)
    {
        current = previous_1 + previous_2;

        previous_2 = previous_1;
        previous_1 = current;

        if((current & 1) == 0)//from some testing this is faster that %2
            sum += current;
    }

    ProblemsResults::Instance()->SetStoredResult("2", std::to_string(sum));
    //MessageWriter::Instance()->WriteToOutputBox("P002: "+std::to_string(sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P002: "+std::to_string(sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

/**
 * \brief <a href="https://projecteuler.net/problem=3" target="blank" > Project Euler Problem 3 </a> - Largest prime factor
 * \details What is the largest prime factor of the number 600851475143 ?
 */
void Problem003()
{
    //auto clock_id = Clock::Instance()->StartClock();

    long number = 600851475143;

    //get a vector with all the numbers that are primes up to sqrt(600851475143)
    //the limit is sqrt(600851475143) because we are looking for 600851475143 factors and there are none bigger that sqrt(600851475143)
    std::vector<unsigned long> primes = PrimeBoolVectorToIntVector(SieveOfEratosthenes(sqrt(number)));
    unsigned long max_factor = 0;

    //find all factors
    while(number > 1)
    {
        for(unsigned long prime : primes)
        {
            if(number % prime == 0)//factor found
            {
                number = number / prime;//update number

                if(prime > max_factor)
                    max_factor = prime;
                break;//if we find a valid prime factor, we go back to the first prime
            }
        }
    }

    ProblemsResults::Instance()->SetStoredResult("3", std::to_string(max_factor));
    //MessageWriter::Instance()->WriteToOutputBox("P003: "+std::to_string(max_factor)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P003: "+std::to_string(max_factor)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

/**
 * \brief <a href="https://projecteuler.net/problem=4" target="blank" > Project Euler Problem 4 </a> - Largest palindrome product
 * \details A palindromic number reads the same both ways. Find the largest palindrome made from the product of two 3-digit numbers.
 */
void Problem004()
{
    //auto clock_id = Clock::Instance()->StartClock();

    int biggest_palindrome = 0;
    for(int i=999; i>99; i--)
    {
        for(int j=999; j>99; j--)
        {
            int product = i*j;

            if(IsPalindrome(product))
                if(biggest_palindrome < product)
                    biggest_palindrome = product;
        }
    }

    ProblemsResults::Instance()->SetStoredResult("4", std::to_string(biggest_palindrome));
    //MessageWriter::Instance()->WriteToOutputBox("P004: "+std::to_string(biggest_palindrome)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P004: "+std::to_string(biggest_palindrome)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

/**
 * \brief <a href="https://projecteuler.net/problem=5" target="blank" > Project Euler Problem 5 </a> - Smallest multiple
 * \details What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
 */
void Problem005()
{
    //auto clock_id = Clock::Instance()->StartClock();

    std::vector<int> numbers{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

    //the solution to this problem is the least common multiple (lcm) of al the number from 1 to 20
    ProblemsResults::Instance()->SetStoredResult("5", std::to_string(LeastCommonMultiple(numbers)));
    //MessageWriter::Instance()->WriteToOutputBox("P005: "+std::to_string(LeastCommonMultiple(numbers)) + " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P005: "+std::to_string(LeastCommonMultiple(numbers)) + " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

/**
 * \brief <a href="https://projecteuler.net/problem=6" target="blank" > Project Euler Problem 6 </a> - Sum square difference
 * \details Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
 */
void Problem006()
{
    //auto clock_id = Clock::Instance()->StartClock();

    int sum_of_squares = 0;
    int square_of_sum = 0;

    for(int i=1; i<101; i++)
    {
        sum_of_squares += i*i;
        square_of_sum += i;
    }

    square_of_sum *= square_of_sum;

    ProblemsResults::Instance()->SetStoredResult("6", std::to_string(square_of_sum - sum_of_squares));
    //MessageWriter::Instance()->WriteToOutputBox("P006: "+std::to_string(square_of_sum - sum_of_squares)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P006: "+std::to_string(square_of_sum - sum_of_squares)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

/**
 * \brief <a href="https://projecteuler.net/problem=7" target="blank" > Project Euler Problem 7 </a> - 10001st prime
 * \details What is the 10 001st prime number?
 */
void Problem007()
{
    //auto clock_id = Clock::Instance()->StartClock();

    //the limit used in the SieveOfEratosthenes call was chosen based on trial and error, as no data for it was given
    std::vector<unsigned long> primes = PrimeBoolVectorToIntVector(SieveOfEratosthenes(150000));//has 13848

    //We use 10000 index as the vector starts at 0, so index 10000 = prime 10001
    ProblemsResults::Instance()->SetStoredResult("7", std::to_string(primes[10000]));
    //MessageWriter::Instance()->WriteToOutputBox("P007: "+std::to_string(primes[10000])+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P007: "+std::to_string(primes[10000])+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

/**
 * \brief <a href="https://projecteuler.net/problem=8" target="blank" > Project Euler Problem 8 </a> - Largest product in a series
 * \details Find the thirteen adjacent digits in the 1000-digit number that have the greatest product. What is the value of this product?
 */
void Problem008()
{
    //auto clock_id = Clock::Instance()->StartClock();

    int ascii_zero='0';//will be used for fast chat -> int casts
    std::string str_int =  "73167176531330624919225119674426574742355349194934"
                            "96983520312774506326239578318016984801869478851843"
                            "85861560789112949495459501737958331952853208805511"
                            "12540698747158523863050715693290963295227443043557"
                            "66896648950445244523161731856403098711121722383113"
                            "62229893423380308135336276614282806444486645238749"
                            "30358907296290491560440772390713810515859307960866"
                            "70172427121883998797908792274921901699720888093776"
                            "65727333001053367881220235421809751254540594752243"
                            "52584907711670556013604839586446706324415722155397"
                            "53697817977846174064955149290862569321978468622482"
                            "83972241375657056057490261407972968652414535100474"
                            "82166370484403199890008895243450658541227588666881"
                            "16427171479924442928230863465674813919123162824586"
                            "17866458359124566529476545682848912883142607690042"
                            "24219022671055626321111109370544217506941658960408"
                            "07198403850962455444362981230987879927244284909188"
                            "84580156166097919133875499200524063689912560717606"
                            "05886116467109405077541002256983155200055935729725"
                            "71636269561882670428252483600823257530420752963450";

    unsigned long greatest_product = 0;

    for(unsigned int i=0; i<str_int.size()-13; i++)//-13 because we are looking for 13 long chains
    {
        unsigned long tmp_product = 1;
        for(int j=0; j<13; j++)//the chain is allways horizontal, as it is a single number and not multiple ones as str_int declaration might sugest
        {
            if(str_int[i+j] == ascii_zero)
                break;

            tmp_product *= (int)(str_int[i+j] - ascii_zero);
        }

        if(tmp_product > greatest_product)
            greatest_product = tmp_product;
    }

    ProblemsResults::Instance()->SetStoredResult("8", std::to_string(greatest_product));
    //MessageWriter::Instance()->WriteToOutputBox("P008: "+std::to_string(greatest_product)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P008: "+std::to_string(greatest_product)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

/**
 * \brief <a href="https://projecteuler.net/problem=9" target="blank" > Project Euler Problem 9 </a> - Special Pythagorean triplet
 * \details There exists exactly one Pythagorean triplet for which a + b + c = 1000. Find the product abc.
 */
void Problem009()
{
    //a^2 + b^2 = c^2
    //Euclid's formula
    //a = m^2 - n^2
    //b = 2mn
    //c = m^2 + n^2
    //m > n

    //After some reading about a^2 + b^2 = c^2 (Pythagorean theorem), I found the Euclid's formula that allows the discovery of abc based on two numbers (m,n)

    //auto clock_id = Clock::Instance()->StartClock();

    int a = 0, b = 0, c = 0;
    int m, n;
    int product = 0;

    for(n = 1; product == 0; n++)
    {
        a = b = c = 0;

        for(m = n + 1; a+b+c < 1000; m++)
        {
            a = m*m -n*n;
            b = 2*m*n;
            c = m*m +n*n;

            if(a+b+c == 1000)
                product = a*b*c;
        }
    }

    ProblemsResults::Instance()->SetStoredResult("9", std::to_string(product));
    //MessageWriter::Instance()->WriteToOutputBox("P009: "+std::to_string(product)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P009: "+std::to_string(product)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

/**
 * \brief <a href="https://projecteuler.net/problem=10" target="blank" > Project Euler Problem 10 </a> - Summation of primes
 * \details Find the sum of all the primes below two million.
 */
void Problem010()
{
    //auto clock_id = Clock::Instance()->StartClock();

    long sum = 0;

    //will return all primes < 2 Million
    std::vector<unsigned long> primes = PrimeBoolVectorToIntVector(SieveOfEratosthenes(2000000));

    for(auto& prime : primes)
        sum += prime;

    ProblemsResults::Instance()->SetStoredResult("10", std::to_string(sum));
    //MessageWriter::Instance()->WriteToOutputBox("P010: "+std::to_string(sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P010: "+std::to_string(sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}
