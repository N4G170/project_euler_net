#include "eulerproblems.h"
#include <vector>
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


#include <SDL2/SDL_ttf.h>
#include <thread>
#include <future>
#include <chrono>
using namespace std::chrono_literals;

#include "graphs.h"
#include "message_writer.h"
#include "clock.h"

void Problem011()
{
    //auto clock_id = Clock::Instance()->StartClock();

    int grid[20][20] =  {{ 8,  2, 22, 97, 38, 15,  0, 40,  0, 75,  4,  5,  7, 78, 52, 12, 50, 77, 91,  8},
                         {49, 49, 99, 40, 17, 81, 18, 57, 60, 87, 17, 40, 98, 43, 69, 48,  4, 56, 62,  0},
                         {81, 49, 31, 73, 55, 79, 14, 29, 93, 71, 40, 67, 53, 88, 30,  3, 49, 13, 36, 65},
                         {52, 70, 95, 23,  4, 60, 11, 42, 69, 24, 68, 56,  1, 32, 56, 71, 37,  2, 36, 91},
                         {22, 31, 16, 71, 51, 67, 63, 89, 41, 92, 36, 54, 22, 40, 40, 28, 66, 33, 13, 80},
                         {24, 47, 32, 60, 99,  3, 45,  2, 44, 75, 33, 53, 78, 36, 84, 20, 35, 17, 12, 50},
                         {32, 98, 81, 28, 64, 23, 67, 10, 26, 38, 40, 67, 59, 54, 70, 66, 18, 38, 64, 70},
                         {67, 26, 20, 68,  2, 62, 12, 20, 95, 63, 94, 39, 63,  8, 40, 91, 66, 49, 94, 21},
                         {24, 55, 58,  5, 66, 73, 99, 26, 97, 17, 78, 78, 96, 83, 14, 88, 34, 89, 63, 72},
                         {21, 36, 23,  9, 75,  0, 76, 44, 20, 45, 35, 14,  0, 61, 33, 97, 34, 31, 33, 95},
                         {78, 17, 53, 28, 22, 75, 31, 67, 15, 94,  3, 80,  4, 62, 16, 14,  9, 53, 56, 92},
                         {16, 39,  5, 42, 96, 35, 31, 47, 55, 58, 88, 24,  0, 17, 54, 24, 36, 29, 85, 57},
                         {86, 56,  0, 48, 35, 71, 89,  7,  5, 44, 44, 37, 44, 60, 21, 58, 51, 54, 17, 58},
                         {19, 80, 81, 68,  5, 94, 47, 69, 28, 73, 92, 13, 86, 52, 17, 77,  4, 89, 55, 40},
                         { 4, 52,  8, 83, 97, 35, 99, 16,  7, 97, 57, 32, 16, 26, 26, 79, 33, 27, 98, 66},
                         {88, 36, 68, 87, 57, 62, 20, 72,  3, 46, 33, 67, 46, 55, 12, 32, 63, 93, 53, 69},
                         { 4, 42, 16, 73, 38, 25, 39, 11, 24, 94, 72, 18,  8, 46, 29, 32, 40, 62, 76, 36},
                         {20, 69, 36, 41, 72, 30, 23, 88, 34, 62, 99, 69, 82, 67, 59, 85, 74,  4, 36, 16},
                         {20, 73, 35, 29, 78, 31, 90,  1, 74, 31, 49, 71, 48, 86, 81, 16, 23, 57,  5, 54},
                         { 1, 70, 54, 71, 83, 51, 54, 69, 16, 92, 33, 48, 61, 43, 52,  1, 89, 19, 67, 48}};

    short grid_size = 20;
    long max_product = 1;
    std::string str = "";

    for(int i = 0; i < grid_size; i++)//row
    {
        for(int j=0; j < grid_size; j++)//column
        {
            long product = 1;
            for(int k = j; k < j + 4 && k < grid_size; k++)//horizontal, right
            {
                product *= grid[i][k];

            }
            if(product > max_product)
            {
                max_product = product;
            }
            product = 1;

            for(int k = i; k < i + 4 && k < grid_size; k++)//vertical, down
            {
                product *= grid[k][j];
            }
            if(product > max_product)
            {
                max_product = product;
            }
            product = 1;

            for(int k = i, l = j; k < i + 4 && l < j + 4 && k < grid_size && l < grid_size; k++, l++)//diagonal, down right
            {
                product *= grid[k][l];
            }
            if(product > max_product)
            {
                max_product = product;
            }
            product = 1;

            for(int k = i, l = j; k < i + 4 && l > j - 4 && k < grid_size && l > 0; k++, l--)//diagonal, down left
            {
                product *= grid[k][l];
            }
            if(product > max_product)
            {
                max_product = product;
            }
        }
    }

    ProblemsResults::Instance()->SetStoredResult("11", std::to_string(max_product));
    //MessageWriter::Instance()->WriteToOutputBox("P011: "+std::to_string(max_product)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P011: "+std::to_string(max_product)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

void Problem012()
{
    //auto clock_id = Clock::Instance()->StartClock();

    unsigned long current_number = 1;
    unsigned long i = 1;
    int total_divisors = 1;

    std::vector<unsigned long> primes = PrimeNumberPoolOfSize(70000);//number based on testing
    std::map<unsigned long, unsigned long> prime_factors;

    while(total_divisors < 500)
    {
        //clear total_divisors and jump to next triangular number
        total_divisors = 1;
        current_number = i*(i+1)/2;//triangular number formula n(n+1)/2;
        i++;

        prime_factors = PrimeFactorsOfNumber(current_number, primes);

        if(prime_factors.size() > 0)//has factors
        {
            for(auto factor_pair : prime_factors)
            {
                total_divisors *= (factor_pair.second + 1);//second is the exponent
            }
        }
    }

    ProblemsResults::Instance()->SetStoredResult("12", std::to_string(current_number));
    //MessageWriter::Instance()->WriteToOutputBox("P012: "+std::to_string(current_number)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P012: "+std::to_string(current_number)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

void Problem013()
{
    //auto clock_id = Clock::Instance()->StartClock();

    //mpz_class belongs to the big number lib gmpxx
    std::list<BigInt_t> all_numbers;
    BigInt_t result;

    std::ifstream numbers_file ("data/problems/p013");
    std::string line;

    if (numbers_file.is_open())
    {
        while ( getline (numbers_file,line) )//each line is a different number
            all_numbers.push_back(BigInt_t(line));
        numbers_file.close();

        for(BigInt_t& single_number : all_numbers)
        {
            result+=single_number;
        }

        ProblemsResults::Instance()->SetStoredResult("13", result.str().substr(0,10));
       //MessageWriter::Instance()->WriteToOutputBox("P013: "+result.get_str().substr(0,10)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
       //return ("P013: "+result.get_str().substr(0,10)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");

    }
    else
    {
        MessageWriter::Instance()->WriteLineToConsole("ERROR: failed to open input file at \"data/problems/p013\"");
        //MessageWriter::Instance()->WriteToOutputBox("ERROR: failed to open input file at \"data/problems/p013\"");
        //return ("ERROR: failed to open input file at \"data/problems/p013\"");
    }
}

void Problem014()
{
    //auto clock_id = Clock::Instance()->StartClock();

    //Collatz sequence
    //n → n/2 (n is even)
    //n → 3n + 1 (n is odd)
    int result = 2;
    int max_chain_length = 0;

    for(int i = 2; i <= 1000000; i++)//all number until 1'000'000
    {
        unsigned long current_number = i;
        int chain_length = 2;//includes the number itself and number 1

        while(current_number > 1)
        {
            if(current_number % 2 == 0)
                current_number = current_number/2;
            else
                current_number = 3* current_number + 1;

            chain_length++;
        }

        if(chain_length > max_chain_length)
        {
            max_chain_length = chain_length;
            result = i;
        }

    }

    ProblemsResults::Instance()->SetStoredResult("14", std::to_string(result));
    //MessageWriter::Instance()->WriteToOutputBox("P014: "+std::to_string(result)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P014: "+std::to_string(result)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

void Problem015()
{
    //auto clock_id = Clock::Instance()->StartClock();

    //{ Pascal Triangle - After some search, it seems that this specific lattice path search (only down and right),
    //is replicating the Pascal Triangle and the solution to this problem can be found with C(n, k) = n!/(k!*(n-k))
    //Which can be simplified for any grind a * b -> [(a+b)!]/[a!* b!]
    //Need to keep in mind that this problems, probably, have a simple mathematical solution
    //so:
    unsigned long a = 20;
    unsigned long b = 20;

    BigInt_t big_result = BigFactorial(a + b) / (BigFactorial(a) * BigFactorial(b));

    ProblemsResults::Instance()->SetStoredResult("15", big_result.str());
    //MessageWriter::Instance()->WriteToOutputBox("P015: "+big_result.get_str()+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P015: "+big_result.get_str()+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //}

}

void Problem016()
{
    //auto clock_id = Clock::Instance()->StartClock();

    BigInt_t big_number;

    big_number = boost::multiprecision::pow( BigInt_t(2),1000);

    std::string big_number_string=big_number.str();

    int digit_sum=0;
    for(char& digit : big_number_string)
    {
        digit_sum+=digit-'0';
    }

    ProblemsResults::Instance()->SetStoredResult("16", std::to_string(digit_sum));
    //MessageWriter::Instance()->WriteToOutputBox("P016: "+std::to_string(digit_sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P016: "+std::to_string(digit_sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

void Problem017()
{
    //auto clock_id = Clock::Instance()->StartClock();

    std::vector<std::string> digit_names;//"name" of each individual digit
    digit_names.insert(digit_names.end(), "zero");
    digit_names.insert(digit_names.end(), "one");
    digit_names.insert(digit_names.end(), "two");
    digit_names.insert(digit_names.end(), "three");
    digit_names.insert(digit_names.end(), "four");
    digit_names.insert(digit_names.end(), "five");
    digit_names.insert(digit_names.end(), "six");
    digit_names.insert(digit_names.end(), "seven");
    digit_names.insert(digit_names.end(), "eight");
    digit_names.insert(digit_names.end(), "nine");

    std::vector<std::string> ten_names;//"name" of numbers 10-19
    ten_names.insert(ten_names.end(), "ten");
    ten_names.insert(ten_names.end(), "eleven");
    ten_names.insert(ten_names.end(), "twelve");
    ten_names.insert(ten_names.end(), "thirteen");
    ten_names.insert(ten_names.end(), "fourteen");
    ten_names.insert(ten_names.end(), "fifteen");
    ten_names.insert(ten_names.end(), "sixteen");
    ten_names.insert(ten_names.end(), "seventeen");
    ten_names.insert(ten_names.end(), "eighteen");
    ten_names.insert(ten_names.end(), "nineteen");


    std::vector<std::string> scores_names;//"name" of tens >= 20
    scores_names.insert(scores_names.end(), "zero");
    scores_names.insert(scores_names.end(), "ten");
    scores_names.insert(scores_names.end(), "twenty");
    scores_names.insert(scores_names.end(), "thirty");
    scores_names.insert(scores_names.end(), "forty");
    scores_names.insert(scores_names.end(), "fifty");
    scores_names.insert(scores_names.end(), "sixty");
    scores_names.insert(scores_names.end(), "seventy");
    scores_names.insert(scores_names.end(), "eighty");
    scores_names.insert(scores_names.end(), "ninety");

    std::string hundred = "hundred";
    std::string thousand = "thousand";


    int total_letters = 0;
    for(int i = 1; i < 1001; i++)
    {
        int fraction = i;
        std::string number_name;
        bool has_hundreds = false;
        bool has_scores = false;
        bool skip_last = false;

        //thousands
        if(fraction / 1000)//has thousands
        {
            int auxilia_number = fraction - fraction % 1000;//get the thousands

            auxilia_number /= 1000;//remove the zeros

            number_name = digit_names[auxilia_number] +""+thousand;

            total_letters+=number_name.size();

            fraction = fraction % 1000;
        }

        //hundreds
        if(fraction / 100)//has hundreds
        {
            int auxilia_number = fraction - fraction % 100;//get the hundreds

            auxilia_number /= 100;//remove the zeros

            number_name = digit_names[auxilia_number] +""+hundred;

            total_letters+=number_name.size();

            fraction = fraction % 100;

            has_hundreds = true;
        }

        //scores (tens)
        if(fraction / 10)//has scores
        {

            int auxilia_number = fraction - fraction % 10;//get the scores

            if(fraction >= 20)
            {
                auxilia_number /= 10;//remove the zeros

                if(has_hundreds)//add the "and" word
                    number_name = "and"+scores_names[auxilia_number];
                else
                    number_name = scores_names[auxilia_number];
            }
            else
            {
                auxilia_number = fraction % 10;//get units

                if(has_hundreds)//add the "and" word
                    number_name = "and"+ten_names[auxilia_number];
                else
                    number_name = ten_names[auxilia_number];
                skip_last = true;
            }

            total_letters+=number_name.size();

            fraction = fraction % 10;

            has_scores = true;
        }

        //digits
        if(fraction > 0 && !skip_last)
        {
            if(has_hundreds && !has_scores)//add the "and" word
                number_name = "and"+digit_names[fraction];
            else
                number_name = digit_names[fraction];

            total_letters+=number_name.size();
        }

    }

    ProblemsResults::Instance()->SetStoredResult("17", std::to_string(total_letters));
    //MessageWriter::Instance()->WriteToOutputBox("P017: "+std::to_string(total_letters)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P017: "+std::to_string(total_letters)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

void Problem018()
{
    //auto clock_id = Clock::Instance()->StartClock();

    std::ifstream numbers_file ("data/problems/p018");
    std::string line;

    std::vector< std::vector< SimpleBinaryTreeNode<int> > > nodes;

    if (numbers_file.is_open())
    {
        //new line vector
        std::vector< SimpleBinaryTreeNode<int> > line_vector;

        std::vector< std::string > line_elements;


        while ( getline (numbers_file,line))//read the triangle from file
        {
            line = Trim(line);

            line_vector.clear();
            line_elements.clear();

            if(line.empty())//for safety
                break;

            line_elements = Explode( line, " " );

            for( unsigned int i = 0; i < line_elements.size(); i++ )
            {
                //create a new node based in a number from the file
                SimpleBinaryTreeNode<int> node;

                node.m_max_value_parent = nullptr;
                node.m_left_child = nullptr;
                node.m_right_child = nullptr;

                //convert string to ulong
                node.m_value = std::stoul( line_elements[i] );
                node.m_max_value = 0;
                node.m_stored = false;

                //save element
                line_vector.push_back( std::move(node) );
            }

            //save line in tree
            nodes.push_back(std::move( line_vector ));

        }//while( getline (numbers_file,line))

        //close file as we no longer need it
        numbers_file.close();

        //clear no longer in use vectors
        line_vector.clear();
        line_elements.clear();

        //connect nodes
        for(unsigned int l=0; l < nodes.size() - 1; l++)//each line (last line is ignored, as it has no children)
        {
            for(unsigned int e = 0; e < nodes[l].size(); e++)//line element
            {
                nodes[l][e].m_left_child = &nodes[l + 1][e];

                nodes[l][e].m_right_child = &nodes[l + 1][e + 1];
            }
        }


        //Dijkstra's like algorithm
        std::queue<SimpleBinaryTreeNode<int>*> nodes_to_check_df;
        int max_value = 0;

        SimpleBinaryTreeNode<int>* current_node = nullptr;

        nodes_to_check_df.push(&nodes[0][0]);
        nodes_to_check_df.front()->m_max_value = nodes_to_check_df.front()->m_value;//set max value to its value, for the first node

        while(!nodes_to_check_df.empty())
        {
            current_node = nodes_to_check_df.front();
            nodes_to_check_df.pop();


            if(current_node->m_left_child == nullptr && current_node->m_right_child == nullptr )//reached one of the final nodes, so we "extract" its value
            {
                if(current_node->m_max_value > max_value)
                {
                    max_value = current_node->m_max_value;
                }
            }
            if(current_node->m_left_child != nullptr)//left side will be checked first
            {
                if(current_node->m_max_value + current_node->m_left_child->m_value > current_node->m_left_child->m_max_value)
                {
                    current_node->m_left_child->m_max_value = current_node->m_max_value + current_node->m_left_child->m_value;
                    current_node->m_left_child->m_max_value_parent = current_node;//set max parent for path backtrack
                }

                if(!current_node->m_left_child->m_stored)//if the child node was not added to the queue, add it
                {
                    current_node->m_left_child->m_stored = true;
                    nodes_to_check_df.push(current_node->m_left_child);
                }
            }
            if(current_node->m_right_child != nullptr)
            {
                if(current_node->m_max_value + current_node->m_right_child->m_value > current_node->m_right_child->m_max_value)
                {
                    current_node->m_right_child->m_max_value = current_node->m_max_value + current_node->m_right_child->m_value;
                    current_node->m_right_child->m_max_value_parent = current_node;
                }

                if(!current_node->m_right_child->m_stored)//if the child node was not added to the queue, add it
                {
                    current_node->m_right_child->m_stored = true;
                    nodes_to_check_df.push(current_node->m_right_child);
                }
            }
        }

        ProblemsResults::Instance()->SetStoredResult("18", std::to_string(max_value));
         //MessageWriter::Instance()->WriteToOutputBox("P018: "+std::to_string(max_value)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
         //return ("P018: "+std::to_string(max_value)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    }
    else
    {
        MessageWriter::Instance()->WriteLineToConsole("ERROR: failed to open input file at \"data/problems/p018\"");
        //MessageWriter::Instance()->WriteToOutputBox("ERROR: failed to open input file at \"data/problems/p018\"");
        //return ("ERROR: failed to open input file at \"data/problems/p018\"");
    }

}

void Problem019()
{
    //auto clock_id = Clock::Instance()->StartClock();

    int y = 0;
    int d = 1;
    int total_sundays_day1 = 0;

    std::vector<int> month_table = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    month_table.shrink_to_fit();

    //implementation based on Gauss's algorithm for Determination of the day of the week
    for(int y_range = 1901; y_range < 2001; y_range++)//years
    {
        for(int m = 1; m < 13; m++)
        {
            //if the month is the january or february y = y - 1
            y = m < 3 ? y_range-1 : y_range;

            int w = (y + y/4 - y/100 + y/400 + month_table[m-1] + d) % 7;

            if(w == Weekdays::SUNDAY)
                total_sundays_day1++;
        }
    }

    ProblemsResults::Instance()->SetStoredResult("19", std::to_string(total_sundays_day1));
    //MessageWriter::Instance()->WriteToOutputBox("P019: "+std::to_string(total_sundays_day1)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P019: "+std::to_string(total_sundays_day1)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}

void Problem020()
{
    //auto clock_id = Clock::Instance()->StartClock();

    //this multitask implementation is not needed. I used it to test std::async, and as it works, I kept it
    std::future<BigInt_t> future_1_50 = std::async(std::launch::async, &BigPartialFactorial, 1,50);
    std::future<BigInt_t> future_51_70 = std::async(std::launch::async, &BigPartialFactorial, 51,70);
    std::future<BigInt_t> future_71_100 = std::async(std::launch::async, &BigPartialFactorial, 71,100);

    BigInt_t final_result = future_1_50.get() * future_51_70.get() * future_71_100.get();
    std::string factorial_100 = final_result.str();

    final_result = 0;//clear mpz_class var as we will reuse it to calculate the last result
    for(auto& letter : factorial_100)
    {
        if(letter != '0')//no need to sum the 0s
            final_result += (int)(letter - '0');
    }

    ProblemsResults::Instance()->SetStoredResult("20", final_result.str());
    //MessageWriter::Instance()->WriteToOutputBox("P020: "+final_result.get_str()+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    //return ("P020: "+final_result.get_str()+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
}
