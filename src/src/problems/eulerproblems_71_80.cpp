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
#include <utility>
#include <cstdlib>

//this problem is mathematically correct (incrementaly tested the math function at http://www.wolframalpha.com/input/?i=sum(phi(n))+1%3Cn%3C10001 )
//Although when the limit > 100000 I get float precision error and the result deviats
std::string Problem072()
{
    auto clock_id = Clock::Instance()->StartClock();

    //using Euler's totient function, to calculate coprimes
    //For n/d to be a reduced proper fraction 'n' and 'd' are coprimes
    //Euler's totient function calculates the number of coprimes o a number 'n'
    int limit = 1000002;

    std::vector<unsigned long> primes = PrimeBoolVectorToIntVector(SieveOfEratosthenes(limit));
    std::vector<std::map<unsigned long,unsigned long>> prime_factors;

    //calculate prime factors of numbers
    /*for(int i = 0; i<limit; i++)
    {
        prime_factors.push_back(PrimeFactorsOfNumber(i, primes));
    }*/
    std::vector<unsigned long> numbers;
    for(int i = 0; i<limit; i++)
    {
        numbers.push_back(i);
    }
    numbers[1]=0;

    long long total_coprimes = 0;
    //calculate coprimes
    for(unsigned int p=0; p<primes.size(); p++)
    {
        for(unsigned long i=primes[p]; i<numbers.size(); i+=primes[p])
        {
            numbers[i]*=(1-1/(float)primes[p]);
        }
    }

    for(int i = 0; i<limit; i++)
    {
        total_coprimes+=numbers[i];
    }
//    for(int i=2; i<limit; i++)
//    {
//        double coprimes = i;
//
//        for(auto factors : prime_factors[i])//each pair in map
//        {
//            coprimes *= (1 - 1/(double)factors.first);//first is the prime factor base
//        }
//
//        total_coprimes+=coprimes;
//    }

    //MessageWriter::Instance()->WriteToOutputBox("P072: "+std::to_string(fractions_sequence.size())+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    return ("P072: "+std::to_string(total_coprimes)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}
