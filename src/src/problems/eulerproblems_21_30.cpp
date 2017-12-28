#include "eulerproblems.h"
#include <vector>
#include <map>
#include <list>
#include <array>
#include "utils.hpp"
#include <math.h>
#include <iostream>
#include "defines.hpp"//big numbers
#include <string>
#include <fstream>//files
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
#include <chrono>
#include <set>

#include <thread>
#include <future>

#include <SDL2/SDL_ttf.h>
#include <thread>

#include "graphs.h"
#include "message_writer.h"
#include "clock.h"


void Problem021()
{
    //auto clock_id = Clock::Instance()->StartClock();

    //Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
    std::map<unsigned int, unsigned int> divisor_sums;

    for(int i = 0; i < 10000; i++)
    {
        divisor_sums.emplace(i, SumOfProperDivisors(i));//calculates the sum of the proper divisors for eath number in 1-10000
    }

    //If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.
    unsigned int total_amicable_numbers = 0;

    for(auto sum : divisor_sums)
    {
        if(sum.second < 10000)//the sum is inside our search bound
        {
            if( divisor_sums[sum.second] == sum.first && sum.second != sum.first && sum.second > sum.first)//the sum.second > sum.first is used to avoid repeating the evaluation
                total_amicable_numbers += divisor_sums[sum.second] + sum.second;
        }
    }

    ProblemsResults::Instance()->SetStoredResult("21", std::to_string(total_amicable_numbers));
    //MessageWriter::Instance()->WriteToOutputBox("P023: "+std::to_string(total_amicable_numbers)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P021: "+std::to_string(total_amicable_numbers)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

void Problem022()
{
    //auto clock_id = Clock::Instance()->StartClock();

    std::ifstream file ("data/problems/p022");
    std::string line;

    std::vector<std::string> words;

    if (file.is_open())
    {
        //the is only one line
        if ( getline (file,line))
        {
            line = Trim(line);
            words = Explode(line, ",");
        }//if( getline (numbers_file,line))

        //close file as we no longer need it
        file.close();
    }

    unsigned long total = 0;

    if(!words.empty())
    {
        //build abc values
        //std::string abc = "abcdefghijklmnopqrstuvwxyz";
        std::string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::map<char, int> abc_value;

        for(unsigned int i = 0; i <  abc.size(); i++)
        {
            abc_value.emplace(abc[i], i+1);//define eath letter value EX:(A = 0 + 1)
        }

        //sort the words alphabeticaly
        sort( words.begin(), words.end(), std::less<std::string>() );

        for(unsigned int i = 0; i <  words.size(); i++)
        {
            total += WordAlphabeticalValue( Trim(words[i], "\""), abc_value ) * (i + 1);
        }
    }

    ProblemsResults::Instance()->SetStoredResult("22", std::to_string(total));
    //MessageWriter::Instance()->WriteToOutputBox("P022: "+std::to_string(total)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P022: "+std::to_string(total)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

void Problem023()
{
    //auto clock_id = Clock::Instance()->StartClock();

    //A perfect number is a number for which the sum of its proper divisors is exactly equal to the number.
    //A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.

    unsigned int limit = 28133;
    std::vector<unsigned int> abundant_numbers;
    //find all abundant numbers bellow the limit
    for(unsigned int i = 0; i < limit; i++)
    {
        if(i < SumOfProperDivisors(i))//abundant number
            abundant_numbers.push_back(i);//get all abundant numbers
    }

    std::vector<bool> sums_of_abundant_numbers(limit, false);
    //calculate the sum of all amicable
    for(unsigned int i = 0; i < abundant_numbers.size(); i++)
    {
        for(unsigned int j = i; j < abundant_numbers.size(); j++)
        {
            unsigned int index = abundant_numbers[i] + abundant_numbers[j];
            if(index < limit)//valid number to the problem
                sums_of_abundant_numbers[index] = true;//is sum of two abundant numbers
        }
    }

    unsigned int sum = 0;
    for(unsigned int i = 0; i < limit; i++)
    {
        if(!sums_of_abundant_numbers[i])//number not sum of two abundants
            sum += i;//sum all numbers that are a sum of two abundant numbers
    }

    ProblemsResults::Instance()->SetStoredResult("23", std::to_string(sum));
    //MessageWriter::Instance()->WriteToOutputBox("P023: "+std::to_string(total_amicable_numbers)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P023: "+std::to_string(sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

void Problem024()
{
    //auto clock_id = Clock::Instance()->StartClock();

//    Find the largest index k such that a[k] < a[k + 1]. If no such index exists, the permutation is the last permutation.
//    Find the largest index l greater than k such that a[k] < a[l].
//    Swap the value of a[k] with that of a[l].
//    Reverse the sequence from a[k + 1] up to and including the final element a[n].

    std::string digits = "0123456789";
    unsigned int permutations = 1;

    while( permutations < 1000000 )
    {
        int k = -1;
        int l = -1;

        for(unsigned int i = 0; i < digits.size() - 1; i++ )
        {
            if( digits[i] < digits[i+1] )
            {
                if((int)i > k)
                    k = i;
            }
        }

        if(k == (int)digits.size())//last permutation reached
            break;

        for(unsigned int i = 0; i < digits.size(); i++ )
        {
            if( digits[i] > digits[k] && (int)i > k )
            {
                if((int)i > l)
                    l = i;
            }
        }

        if(l == (int)digits.size())//no more permutations
            break;

        //increase number of permutations as we can have a new valid one
        permutations++;

        //swap digits[i] and digits[k]
        std::swap( digits[k], digits[l] );

        std::reverse(digits.begin() + k + 1, digits.end());
    }

    //I implemented my Lexicographic permutations algorithm but the next block of code uses stl implementation and works
    //using the stl algorithm for Lexicographic permutations
    /*std::string str = "0123456789";

    for(unsigned int i = 1; i < 1000000; i++)
    {
        std::next_permutation(str.begin(), str.end());
    }*/

    ProblemsResults::Instance()->SetStoredResult("24", digits);
    //MessageWriter::Instance()->WriteToOutputBox("P024: "+result+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P024: "+digits+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

void Problem025()
{
    //auto clock_id = Clock::Instance()->StartClock();

    BigInt_t fn = 0;//the problem text already has F1 -> F12
    BigInt_t fn_1 = 1;//fibonacci Fn-1 -> F1 = 1
    BigInt_t fn_2 = 1;//fibonacci Fn-2 -> F2 = 1
    unsigned long current_fibonacci_term = 2;

    while(true)
    {
        //calculate fibonacci
        current_fibonacci_term++;
        fn = fn_1 + fn_2;

        if(fn.str().size() == 1000)//found first of lenght 1000 digits
            break;

        fn_2 = fn_1;
        fn_1 = fn;
    }


    ProblemsResults::Instance()->SetStoredResult("25", std::to_string(current_fibonacci_term));
    //MessageWriter::Instance()->WriteToOutputBox("P025: "+std::to_string(current_fibonacci_term)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P025: "+std::to_string(current_fibonacci_term)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");

    //Math note
    //A number 'm' uses at least 'k' digits in decimal representation if log_10(m) >= k-1
    //So this problem can be solved with the equasion'log_10(((1+Sqrt(5))/2)^n/Sqrt(5))>=999'
}

std::string Problem026()//this function is not working and I've yet to find the problem
{
   // auto clock_id = Clock::Instance()->StartClock();

    //std::map<unsigned int, mpz_class> decimal_representation;

    long double decimal_representation;//mpf -> floats, the mpz->int

    unsigned int longest_recurring_cycle_size = 0;
   // unsigned int longest_recurring_cycle_denominator = 1;

    for(float i = 11; i < 1000; i++)//will start on 11 as the problem already analysed
    {
        decimal_representation = 1 / i;

        if(std::to_string(decimal_representation).size() > 2)//has decimal
        {
            std::string number_str = std::to_string(decimal_representation).substr(2);//remove the "0."

            //if number.size()/2 is surpassed, we can no longer check for recurring cycles, as the first iteration will be longer that the remaining string
            for(unsigned int j = 0; j < number_str.size()/2; j++)
            {
                std::string section = number_str.substr(0, j+1);

                int recurring_cycle = 0;
                int pos = 0;

                while((pos = number_str.find(section, pos)) == 0)//allways the first position
                {
                    pos += section.size();
                    recurring_cycle++;
                }


                if(pos + section.size() >= number_str.size() && recurring_cycle > 1)//did not search until the section was to long (broke befor reaching the end)
                {
                    std::cout<<i<<" - "<<section<<std::endl;
                    if(longest_recurring_cycle_size < section.size())
                    {
                        longest_recurring_cycle_size = section.size();
                        //longest_recurring_cycle_denominator = i;
                        //break;
                    }
                }

            }
        }

    }

    //ProblemsResults::Instance()->SetStoredResult("19", std::to_string(total_sundays_day1));
    //return ("P026: "+std::to_string(longest_recurring_cycle_denominator)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    return ("P026: Not working, yet");
    //std::cout<<longest_recurring_cycle_denominator<<" in "<<Clock::Instance()->StopAndReturnClock(clock_id)<<" ms"<<std::endl;
}

void Problem027()
{
    //auto clock_id = Clock::Instance()->StartClock();

    unsigned int max_number_of_primes = 0;
    long coeficients_product = 1;

    std::vector<unsigned long> primes = PrimeBoolVectorToIntVector(SieveOfEratosthenes(1000));

    for(int a = -999; a < 1000; a++)
    {
        //damn the change for this prime array reduced execution time from around 17s to 900ms
        for(int b : primes)//if n = 0, b is the result, so b has to be prime for us to be able to start a chain
        {
            unsigned int number_of_primes = 0;
            //n^2 + an + b
            for(unsigned int n = 0; ; n++)
            {
                long number = n*n + a*n + b;

                if(number > 1)//positive and not 1
                {
                    if(IsPrime(number))
                    {
                        number_of_primes++;
                    }
                    else
                    {
                        if(number_of_primes >= max_number_of_primes)//found new biggest chain?
                        {
                            max_number_of_primes = number_of_primes;
                            coeficients_product = a * b;
                        }

                        break;
                    }
                }

            }
        }
    }

    ProblemsResults::Instance()->SetStoredResult("27", std::to_string(coeficients_product));
    //MessageWriter::Instance()->WriteToOutputBox("P027: "+std::to_string(coeficients_product)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P027: "+std::to_string(coeficients_product)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

void Problem029()
{
    //auto clock_id = Clock::Instance()->StartClock();

    std::set< BigInt_t > distinct_terms;
    BigInt_t term;

    for(int a = 2; a < 101; a++)
    {
        for(int b = 2; b < 101; b++)
        {
            term = boost::multiprecision::pow( BigInt_t(a), b );

            //a set does not allow multiple entries with the same value, so we do not need to check if its exists
            distinct_terms.insert( term );
        }
    }

    ProblemsResults::Instance()->SetStoredResult("29", std::to_string(distinct_terms.size()));
    //MessageWriter::Instance()->WriteToOutputBox("P029: "+std::to_string(distinct_terms.size())+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P029: "+std::to_string(distinct_terms.size())+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

void Problem030()
{
    //auto clock_id = Clock::Instance()->StartClock();

    std::array< unsigned int, 10 > fifth_powers;
    unsigned int total_sum_of_digits_fifth_powers = 0;

    for(int i = 0; i < 10; i++)//calculate the 5th power of each digit
    {
        fifth_powers[i] = (int)std::pow( i, 5 );
    }

    std::string number_str;

    //as no top limit was given in the problem, the 1000000 was chosen based on info from the clarification forum,
    //otherwise the limit would be changed until a valid one was found (valid limit = allows correct result)
    for(unsigned int i = 10; i < 1000000; i++ )
    {
        number_str = std::to_string(i);
        unsigned int sum_of_digit_powers = 0;

        for(unsigned int j = 0; j < number_str.size(); j++ )
            sum_of_digit_powers += fifth_powers[ (int)(number_str[j] - '0' ) ];

        if(sum_of_digit_powers == i)
            total_sum_of_digits_fifth_powers += i;
    }

    ProblemsResults::Instance()->SetStoredResult("30", std::to_string(total_sum_of_digits_fifth_powers));
    //MessageWriter::Instance()->WriteToOutputBox("P030: "+std::to_string(total_sum_of_digits_fifth_powers)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P030: "+std::to_string(total_sum_of_digits_fifth_powers)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}
