#include "eulerproblems.hpp"
#include "utils.hpp"
#include "message_writer.hpp"

#include "clock.hpp"
#include "poker_hand.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

std::string Problem051()//does not work yet
{
    int sequence_size = 0;
    ulong_t current_number = 56003;//this value comes from the problem description
    ulong_t min_number = ULONG_MAX;


    while(sequence_size < 8)
    {
        current_number++;

        std::string number_string = std::to_string(current_number);
        unsigned int number_length = number_string.size();

        //replace one digit
        for(int i = number_length-1; i >= 0 && sequence_size < 6; i--)//change replacement position
        {
            int j = 0;//replacement digit

            if(i == 0)//if we are replacing the first digit, the replacement has to be 1-9
                j = 1;

            sequence_size = 0;//clear counter
            number_string = std::to_string(current_number);//reset number string
            min_number = ULONG_MAX;//reset min

            for(;j < 10; j++)
            {
                number_string[i]=j;
                ulong_t number = std::stoul(number_string);

                if(IsPrime(number))
                {
                    sequence_size++;

                    if(min_number < number)
                        min_number = number;
                }
            }
        }
    }

    //MessageWriter::Instance()->WriteLineToConsole("Sequence: "+std::to_string(sequence_size)+" - Number:"+std::to_string(min_number));
    return ("Sequence: "+std::to_string(sequence_size)+" - Number:"+std::to_string(min_number));
}

std::string Problem052()
{
    long_t result{0};

    // 2x, 3x, 4x, 5x, and 6x
    for(long_t i{10}; ; ++i)
    {
        long_t base_number_of_digits{ (long_t)NumberOfDigits(i) };
        long_t multiple_2{ i * 2 };
        if(NumberOfDigits(multiple_2) == base_number_of_digits)
        {
            long_t multiple_3{ i * 3 };
            if(NumberOfDigits(multiple_3) == base_number_of_digits)
            {
                long_t multiple_4{ i * 4 };
                if(NumberOfDigits(multiple_4) == base_number_of_digits)
                {
                    long_t multiple_5{ i * 5 };
                    if(NumberOfDigits(multiple_5) == base_number_of_digits)
                    {
                        long_t multiple_6{ i * 6 };
                        if(NumberOfDigits(multiple_6) == base_number_of_digits)
                        {
                            if( IsPermutation(multiple_2, multiple_3) && IsPermutation(multiple_2, multiple_4) &&
                                IsPermutation(multiple_2, multiple_5) && IsPermutation(multiple_2, multiple_6) )
                            {
                                result = i;
                                break;
                            }
                        }//6
                    }//5
                }//4
            }//3
        }//2
    }

    return std::to_string(result);
}

std::string Problem054()//does not work yet
{
    /*auto clock_id = Clock::Instance()->StartClock();

    mpz_class result;

    std::ifstream poker_file ("data/problems/p054");
    std::string line;
    std::vector<std::string> exploded_line;

    PokerHand player_1;
    PokerHand player_2;

    exploded_line.resize( 10, "");//resize the vector to 10 (cards), to save memory (we know from the problem that each play has 10 cards)

    if (poker_file.is_open())
    {
        while ( getline (poker_file,line) )//each line is a different match
        {
            line = Trim( line );

            if(line.empty())
                break;

            exploded_line = Explode( line, " ");

            for(auto a : exploded_line)
                std::cout<<a;
            std::cout<<std::endl;

            player_1.SetHand(exploded_line, 0, 4);
            player_2.SetHand(exploded_line, 5, 9);

            std::cout<<"P1: ";
            for(auto a : player_1.GetHand())
                std::cout<<a.first << "" << a.second;
            std::cout<<" ------- ";

//            std::cout<<"P2: ";
//            for(auto a : player_2.GetHand())
//                std::cout<<a.first << "" << a.second;
//            std::cout<<std::endl;
            */
//        }
//
//        poker_file.close();
//
//       //MessageWriter::Instance()->WriteToOutputBox("P054:  in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
//       return ("P054:  in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
//
//    }
//    else
//    {
//        MessageWriter::Instance()->WriteLineToConsole("ERROR: failed to open input file at \"data/problems/p054\"");
//        //MessageWriter::Instance()->WriteToOutputBox("ERROR: failed to open input file at \"data/problems/p054\"");
//        return ("ERROR: failed to open input file at \"data/problems/p054\"");
//    }
    return "";
}
