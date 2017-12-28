#ifndef EULERPROBLEMS_H
#define EULERPROBLEMS_H

#include <string>
#include <mutex>
#include <map>
#include <thread>
#include <vector>
#include <queue>
#include "server_socket_TCP.hpp"
#include "server_socket_UDP.hpp"

/**
 * \brief Singleton class storing the calculated results for the problems
 */
class ProblemsResults
{
    public:
        virtual ~ProblemsResults();

        /**
         * \brief Singleton instance
         */
        static std::unique_ptr<ProblemsResults>& Instance();

        //we delete the copy constructor and the assign operator to avoid the accidental copy of our mais instance
        ProblemsResults(ProblemsResults const&)     = delete;
        void operator=(ProblemsResults const&)    = delete;

        void SetStoredResult(std::string problem_number, std::string result);

        //for TCP clients
        void RequestProblem(std::string problem_number, int client_index, ServerSocketTCP* server);

        //for UDP clients
        void RequestProblem(std::string problem_number, IPaddress client_ip, ServerSocketUDP* server);

    private:
        ProblemsResults();

        void SolveProblem(std::string problem_number);

        static std::unique_ptr<ProblemsResults> s_instance;

        /**
        * \brief Constrols access to \see m_results
        */
        std::mutex m_results_mutex;

        /**
        * \brief Stores the results from previously calculated problems
        */
        std::map<std::string, std::string> m_results;
        /**
        * \brief Map with the problem number as key and a list of clients waiting for its result to be calculated
        * The std::pair stores the id in the int if the client is a tcp client and the ipaddr if udp client (the int will be -1 to mark it as an udp client)
        */
        std::map<std::string, std::queue< std::pair<int,IPaddress> >> m_problems_being_solved;

        /**
        * \brief Map storing the thread running
        */
        std::map<std::thread::id, std::thread> m_running_thread;

        /**
        * \brief Pointer to the instance of the TCP server (used to write the results on the stream)
        */
        ServerSocketTCP* m_tcp_server;

        /**
        * \brief Pointer to the instance of the UDP server (used to send the results)
        */
        ServerSocketUDP* m_udp_server;
};

//{ 1-10 Implemented in eulerproblems_1_10.cpp
/**
 * \brief <a href="https://projecteuler.net/problem=1" target="blank" > Project Euler Problem 1 </a> - Multiples of 3 and 5
 * \details Find the sum of all the multiples of 3 or 5 below 1000.
 */
void Problem001();

/**
 * \brief <a href="https://projecteuler.net/problem=2" target="blank" > Project Euler Problem 2 </a> - Even Fibonacci numbers
 * \details By considering the terms in the Fibonacci sequence whose values do not exceed four million, find the sum of the even-valued terms.
 */
void Problem002();

/**
 * \brief <a href="https://projecteuler.net/problem=3" target="blank" > Project Euler Problem 3 </a> - Largest prime factor
 * \details What is the largest prime factor of the number 600851475143 ?
 */
void Problem003();

/**
 * \brief <a href="https://projecteuler.net/problem=4" target="blank" > Project Euler Problem 4 </a> - Largest palindrome product
 * \details A palindromic number reads the same both ways. Find the largest palindrome made from the product of two 3-digit numbers.
 */
void Problem004();

/**
 * \brief <a href="https://projecteuler.net/problem=5" target="blank" > Project Euler Problem 5 </a> - Smallest multiple
 * \details What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
 */
void Problem005();

/**
 * \brief <a href="https://projecteuler.net/problem=6" target="blank" > Project Euler Problem 6 </a> - Sum square difference
 * \details Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.
 */
void Problem006();

/**
 * \brief <a href="https://projecteuler.net/problem=7" target="blank" > Project Euler Problem 7 </a> - 10001st prime
 * \details What is the 10 001st prime number?
 */
void Problem007();

/**
 * \brief <a href="https://projecteuler.net/problem=8" target="blank" > Project Euler Problem 8 </a> - Largest product in a series
 * \details Find the thirteen adjacent digits in the 1000-digit number that have the greatest product. What is the value of this product?
 */
void Problem008();

/**
 * \brief <a href="https://projecteuler.net/problem=9" target="blank" > Project Euler Problem 9 </a> - Special Pythagorean triplet
 * \details There exists exactly one Pythagorean triplet for which a + b + c = 1000. Find the product abc.
 */
void Problem009();

/**
 * \brief <a href="https://projecteuler.net/problem=10" target="blank" > Project Euler Problem 10 </a> - Summation of primes
 * \details Find the sum of all the primes below two million.
 */
void Problem010();
//}

//{ 11-20 Implemented in eulerproblems_11_20.cpp
/**
 * \brief <a href="https://projecteuler.net/problem=11" target="blank" > Project Euler Problem 11 </a> - Largest product in a grid
 * \details What is the greatest product of four adjacent numbers in the same direction (up, down, left, right, or diagonally) in the 20×20 grid?
 */
void Problem011();

/**
 * \brief <a href="https://projecteuler.net/problem=12" target="blank" > Project Euler Problem 12 </a> - Highly divisible triangular number
 * \details What is the value of the first triangle number to have over five hundred divisors?
 */
void Problem012();

/**
 * \brief <a href="https://projecteuler.net/problem=13" target="blank" > Project Euler Problem 13 </a> - Large sum
 * \details Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
 */
void Problem013();

/**
 * \brief <a href="https://projecteuler.net/problem=14" target="blank" > Project Euler Problem 14 </a> - Longest Collatz sequence
 * \details Which starting number, under one million, produces the longest chain?
 */
void Problem014();

/**
 * \brief <a href="https://projecteuler.net/problem=15" target="blank" > Project Euler Problem 15 </a> - Lattice paths
 * \details How many such routes are there through a 20×20 grid?
 */
void Problem015();

/**
 * \brief <a href="https://projecteuler.net/problem=16" target="blank" > Project Euler Problem 16 </a> - Power digit sum
 * \details What is the sum of the digits of the number 2^1000?
 */
void Problem016();

/**
 * \brief <a href="https://projecteuler.net/problem=17" target="blank" > Project Euler Problem 17 </a> - Number letter counts
 * \details If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used?
 */
void Problem017();

/**
 * \brief <a href="https://projecteuler.net/problem=18" target="blank" > Project Euler Problem 18 </a> - Maximum path sum I
 * \details Find the maximum total from top to bottom of the given triangle.
 */
void Problem018();

/**
 * \brief <a href="https://projecteuler.net/problem=19" target="blank" > Project Euler Problem 19 </a> - Counting Sundays
 * \details How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
 */
void Problem019();

/**
 * \brief <a href="https://projecteuler.net/problem=20" target="blank" > Project Euler Problem 20 </a> - Factorial digit sum
 * \details Find the sum of the digits in the number 100!
 */
void Problem020();
//}

//{ 21-30 Implemented in eulerproblems_21_30.cpp

/**
 * \brief <a href="https://projecteuler.net/problem=21" target="blank" > Project Euler Problem 21 </a> - Amicable numbers
 * \details Evaluate the sum of all the amicable numbers under 10000.
 */
void Problem021();

/**
 * \brief <a href="https://projecteuler.net/problem=22" target="blank" > Project Euler Problem 22 </a> - Names scores
 * \details What is the total of all the name scores in the file?
 */
void Problem022();

/**
 * \brief <a href="https://projecteuler.net/problem=23" target="blank" > Project Euler Problem 23 </a> - Non-abundant sums
 * \details Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
 */
void Problem023();

/**
 * \brief <a href="https://projecteuler.net/problem=24" target="blank" > Project Euler Problem 24 </a> - Lexicographic permutations
 * \details What is the millionth lexicographic permutation of the digits 0, 1, 2, 3, 4, 5, 6, 7, 8 and 9?
 */
void Problem024();

/**
 * \brief <a href="https://projecteuler.net/problem=25" target="blank" > Project Euler Problem 25 </a> - 1000-digit Fibonacci number
 * \details What is the index of the first term in the Fibonacci sequence to contain 1000 digits?
 */
void Problem025();

/**
 * \brief <a href="https://projecteuler.net/problem=26" target="blank" > Project Euler Problem 26 </a> - Reciprocal cycles(Not ready yet)
 * \details Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.
 */
std::string Problem026();

/**
 * \brief <a href="https://projecteuler.net/problem=27" target="blank" > Project Euler Problem 27 </a> - Quadratic primes
 * \details Find the product of the coefficients, a and b, for the quadratic expression that produces the maximum number of primes for consecutive values of n, starting with n = 0.
 */
void Problem027();

//std::string Problem028();

/**
 * \brief <a href="https://projecteuler.net/problem=29" target="blank" > Project Euler Problem 29 </a> - Distinct powers
 * \details How many distinct terms are in the sequence generated by ab for 2 ≤ a ≤ 100 and 2 ≤ b ≤ 100?
 */
void Problem029();

/**
 * \brief <a href="https://projecteuler.net/problem=30" target="blank" > Project Euler Problem 30 </a> - Digit fifth powers
 * \details Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
 */
void Problem030();
//}

//{ 31-40 Implemented in eulerproblems_31_40.cpp
//std::string Problem031();
//std::string Problem032();
//std::string Problem033();

/**
 * \brief <a href="https://projecteuler.net/problem=34" target="blank" > Project Euler Problem 34 </a> - Digit factorials
 * \details Find the sum of all numbers which are equal to the sum of the factorial of their digits.
 */
void Problem034();

/**
 * \brief <a href="https://projecteuler.net/problem=35" target="blank" > Project Euler Problem 35 </a> - Circular primes
 * \details How many circular primes are there below one million?
 */
void Problem035();

/**
 * \brief <a href="https://projecteuler.net/problem=36" target="blank" > Project Euler Problem 36 </a> - Double-base palindromes
 * \details Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.
 */
void Problem036();
//std::string Problem037();
//std::string Problem038();
//std::string Problem039();
//std::string Problem040();
//}

//{ 41-50 Implemented in eulerproblems_41_50.cpp
//std::string Problem041();

/**
 * \brief <a href="https://projecteuler.net/problem=42" target="blank" > Project Euler Problem 42 </a> - Coded triangle numberss
 * \details Using a 16K text file containing nearly two-thousand common English words, how many are triangle words?
 */
void Problem042();
//std::string Problem043();
//std::string Problem044();
//std::string Problem045();
//std::string Problem046();

/**
 * \brief <a href="https://projecteuler.net/problem=47" target="blank" > Project Euler Problem 47 </a> - Distinct primes factors (Not ready yet)
 * \details Find the first four consecutive integers to have four distinct prime factors. What is the first of these numbers?
 */
std::string Problem047();

/**
 * \brief <a href="https://projecteuler.net/problem=48" target="blank" > Project Euler Problem 48 </a> - Self powers
 * \details Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.
 */
void Problem048();
//std::string Problem049();
//std::string Problem050();
//}

//{ 51-60 Implemented in eulerproblems_51_60.cpp

/**
 * \brief <a href="https://projecteuler.net/problem=51" target="blank" > Project Euler Problem 51 </a> - Prime digit replacements (Not ready yet)
 * \details Find the smallest prime which, by replacing part of the number (not necessarily adjacent digits) with the same digit, is part of an eight prime value family.
 */
std::string Problem051();
//std::string Problem052();
//std::string Problem053();

/**
 * \brief <a href="https://projecteuler.net/problem=54" target="blank" > Project Euler Problem 54 </a> - Poker hands
 * \details How many hands does Player 1 win?
 */
std::string Problem054();
//std::string Problem055();
//std::string Problem056();
//std::string Problem057();
//std::string Problem058();
//std::string Problem059();
//std::string Problem060();
//}

//{ 61-70 Implemented in eulerproblems_61_70.cpp

/**
 * \brief <a href="https://projecteuler.net/problem=48" target="blank" > Project Euler Problem 48 </a> - Cyclical figurate numbers
 * \details Find the sum of the only ordered set of six cyclic 4-digit numbers for which each polygonal type: triangle, square, pentagonal, hexagonal, heptagonal, and octagonal, is represented by a different number in the set.
 */
std::string Problem061();
//std::string Problem062();
//std::string Problem063();
//std::string Problem064();
//std::string Problem065();
//std::string Problem066();

/**
 * \brief <a href="https://projecteuler.net/problem=67" target="blank" > Project Euler Problem 67 </a> - Maximum path sum II
 * \details Find the maximum total from top to bottom in a 15K text file containing a triangle with one-hundred rows.
 */
void Problem067();
//std::string Problem068();
//std::string Problem069();
//std::string Problem070();
//}

//{ 71-80 Implemented in eulerproblems_71_80.cpp
//std::string Problem071();

/**
 * \brief <a href="https://projecteuler.net/problem=72" target="blank" > Project Euler Problem 72 </a> - Counting fractions
 * \details How many elements would be contained in the set of reduced proper fractions for d ≤ 1,000,000?
 */
std::string Problem072();
//std::string Problem073();
//std::string Problem074();
//std::string Problem075();
//std::string Problem076();
//std::string Problem077();
//std::string Problem078();
//std::string Problem079();
//std::string Problem080();
//}

//{ 81-90 Implemented in eulerproblems_81_90.cpp

/**
 * \brief <a href="https://projecteuler.net/problem=81" target="blank" > Project Euler Problem 81 </a> - Path sum: two ways
 * \details Find the minimal path sum, in a 31K text file containing a 80 by 80 matrix, from the top left to the bottom right by only moving right and down.
 */
void Problem081();

/**
 * \brief <a href="https://projecteuler.net/problem=82" target="blank" > Project Euler Problem 82 </a> - Path sum: three ways
 * \details Find the minimal path sum, in a 31K text file containing a 80 by 80 matrix, from the left column to the right column.
 */
std::string Problem082();
//std::string Problem083();
//std::string Problem084();
//std::string Problem085();
//std::string Problem086();
//std::string Problem087();
//std::string Problem088();
//std::string Problem089();
//std::string Problem090();
//}

//{ 91-100 Implemented in eulerproblems_91_100.cpp
//std::string Problem091();
//std::string Problem092();
//std::string Problem093();

/**
 * \brief <a href="https://projecteuler.net/problem=94" target="blank" > Project Euler Problem 94 </a> - Almost equilateral triangles
 * \details Find the sum of the perimeters of all almost equilateral triangles with integral side lengths and area and whose perimeters do not exceed one billion (1,000,000,000).
 */
std::string Problem094();
//std::string Problem095();
//std::string Problem096();
//std::string Problem097();
//std::string Problem098();
//std::string Problem099();
//std::string Problem100();
//}

#endif // EULERPROBLEMS_H
