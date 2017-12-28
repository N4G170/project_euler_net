#include "eulerproblems.h"
#include "utils.hpp"
#include "message_writer.h"

#include "clock.h"

#include <map>
#include <set>
#include <array>
#include <vector>
#include <string>
#include <iostream>
#include "defines.hpp"
#include <fstream>

void Problem042()
{
    //auto clock_id = Clock::Instance()->StartClock();

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

    unsigned long total_triangle_words = 0;

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

    ProblemsResults::Instance()->SetStoredResult("42", std::to_string(total_triangle_words));
    //MessageWriter::Instance()->WriteToOutputBox("P047: "+std::to_string(current_fibonacci_term)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P042: "+std::to_string(total_triangle_words)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

std::string Problem047()//does not work yet, no idea what the problem is
{
    auto clock_id = Clock::Instance()->StartClock();

    std::vector<unsigned long> primes = PrimeBoolVectorToIntVector(SieveOfEratosthenes(1000000));

    std::set<std::pair<unsigned long, unsigned long>> unique_factors;
    std::vector<std::map<unsigned long, unsigned long>> all_factors;
    unsigned long first_of_sequence = 0;

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


    //MessageWriter::Instance()->WriteToOutputBox("P047: "+std::to_string(current_fibonacci_term)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    return ("P047: "+std::to_string(first_of_sequence)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}


void Problem048()
{
    //auto clock_id = Clock::Instance()->StartClock();

    BigInt_t number = 0;
    BigInt_t power = 0;

    for(int i = 1; i < 1001; i++)
    {
        power = boost::multiprecision::pow( BigInt_t(i), i);//big numbers pow function
        number += power;
    }

    std::string result = number.str().substr(number.str().size() - 10);

    ProblemsResults::Instance()->SetStoredResult("48", result);
    //MessageWriter::Instance()->WriteToOutputBox("P047: "+std::to_string(current_fibonacci_term)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P048: "+result+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}
