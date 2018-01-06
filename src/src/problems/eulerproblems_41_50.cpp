#include "eulerproblems.hpp"
#include "utils.hpp"
#include "message_writer.hpp"

#include "clock.hpp"

#include <map>
#include <set>
#include <array>
#include <vector>
#include <string>
#include <iostream>
#include "defines.hpp"//big numbers
#include <fstream>
#include <array>

std::string Problem042()
{
    std::ifstream file ("data/problems/p042");
    std::string line;

    std::vector<std::string> words;
    std::set<unsigned int> triangle_numbers;//for its find function

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

    ulong_t total_triangle_words = 0;

    if(!words.empty())
    {
        //build abc values
        //std::string abc = "abcdefghijklmnopqrstuvwxyz";
        std::string abc = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::map<char, int> abc_value;

        for(unsigned int i = 0; i <  abc.size(); i++)
        {
            abc_value.emplace(abc[i], i+1);//set each letter value
        }
        //sort words, alphabetically
        sort( words.begin(), words.end(), std::less<std::string>() );

        //generate triangle numbers tn = n(n+1)/2
        for(unsigned int i = 0; i < 100; i++ )
            triangle_numbers.insert( i * (i+1) / 2 );

        for(unsigned int i = 0; i <  words.size(); i++)
        {
            unsigned int word_value = WordAlphabeticalValue( Trim(words[i], "\""), abc_value );

            if(triangle_numbers.find(word_value) != triangle_numbers.end())
                total_triangle_words++;
        }
    }

    return (std::to_string(total_triangle_words));
}

std::string Problem047()//does not work yet, no idea what the problem is
{
    std::vector<ulong_t> primes = PrimeBoolVectorToIntVector(SieveOfEratosthenes(1000000));

    std::set<std::pair<ulong_t, ulong_t>> unique_factors;
    std::vector<std::map<ulong_t, ulong_t>> all_factors;
    ulong_t first_of_sequence = 0;

    unsigned int limit = 1000000;

    for(unsigned int i = 0; i < limit; i++)//calculate the factors for all number in the limit
        all_factors.push_back(PrimeFactorsOfNumber(i));


    for(unsigned int i = 0; i < limit-4; i++)
    {
        bool jump_to_next = false;
        unique_factors.clear();


        for(int j = 0; j < 4; j++)//sequence must have 4 elements
        {
            for(auto factor : all_factors[i + j])
            {
                auto result = unique_factors.insert(factor);//first is the factor base, second is the factor exponent

                if(!result.second)//factor already exists
                {
                    jump_to_next = true;
                    break;
                }
            }
            if(jump_to_next)//break the sequence loop so a new one can be started
                break;
        }

        if(jump_to_next)
            continue;

        //when the code gets here, the result was found
        first_of_sequence = i;
    }

    return (std::to_string(first_of_sequence));
}


std::string Problem048()
{
    BigInt_t number{0};
    BigInt_t power{0};

    for(int i = 1; i < 1001; i++)
    {
        mpz_ui_pow_ui(power.get_mpz_t(), i, i);
        number += power;
    }

    std::string result = number.get_str().substr(number.get_str().size() - 10);
    //MessageWriter::Instance()->WriteToOutputBox("P047: "+std::to_string(current_fibonacci_term)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    return (result);
}

std::string Problem049()
{
    std::string result;

    std::vector<ulong_t> primes = PrimeBoolVectorToIntVector( SieveOfEratosthenes(10000));//only 4 digit primes are needed

    // auto IsPermutation = [](long number_1, long number_2)->bool
    // {
    //     std::array<short, 10> digits_count{{ 0,0,0,0,0,0,0,0,0,0 }};//only in C++11 we need to use {{}}. since c++14, {} are ok, but since my lint keeps marking it with a warnning, I used {{}}
    //
    //     while(number_1 != 0)
    //     {
    //         digits_count[ number_1 % 10 ]++;
    //         number_1 /= 10;
    //     }
    //
    //     while(number_2 != 0)
    //     {
    //         digits_count[ number_2 % 10 ]--;
    //         number_2 /= 10;
    //     }
    //
    //     for( short digit_count : digits_count)
    //         if(digit_count > 0)
    //             return false;
    //
    //     return true;
    // };

    auto FindPrime = [&primes](ulong_t prime, unsigned int start_index)->bool
    {
        for( ; start_index < primes.size(); start_index++)
        {
            if(primes[start_index] == prime)
                return true;
        }

        return false;
    };

    //as we only need 4 digit numbers, we remove all of the smaller ones
    int last_to_remove{};
    for(last_to_remove = 0; NumberOfDigits(primes[last_to_remove]) < 4; last_to_remove++);

    primes.erase( primes.begin(), primes.begin()+last_to_remove);

    for(unsigned int i{0}; i < primes.size(); i++)
    {
        for(unsigned int p = i + 1; p < primes.size(); p++)
        {
            int difference = primes[p] - primes[i];//get the difference with the "next" prime and use it to calculate the third term

            if(FindPrime(primes[p] + difference, p))
            {
                if( IsPermutation( primes[i], primes[p] ) && IsPermutation( primes[p], primes[p] + difference ))
                {
                    if(primes[i] != 1487)//we know only one other sequence exists, other than 1487, 4817, 8147
                    {
                       result = std::to_string(primes[i]) + std::to_string(primes[p]) + std::to_string(primes[p] + difference);
                       i = primes.size();//will break upper loop
                       break;//break lower loop
                    }
                }
            }
        }
    }

    // MessageWriter::Instance()->WriteToOutputBox("P049: "+result+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    return result;
}
