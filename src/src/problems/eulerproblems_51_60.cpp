#include "eulerproblems.h"
#include "utils.hpp"
#include "message_writer.h"

#include "clock.h"
#include "poker_hand.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

std::string Problem051()//does not work yet
{
    int sequence_size = 0;
    unsigned long current_number = 56003;//this value comes from the problem description
    unsigned long min_number = ULONG_MAX;


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
                unsigned long number = std::stoul(number_string);

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

std::string Problem054()//does not work yet
{
    auto clock_id = Clock::Instance()->StartClock();

    BigInt_t result;

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

            /*std::cout<<"P2: ";
            for(auto a : player_2.GetHand())
                std::cout<<a.first << "" << a.second;
            std::cout<<std::endl;*/
        }

        poker_file.close();

       //MessageWriter::Instance()->WriteToOutputBox("P054:  in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
       return ("P054:  in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");

    }
    else
    {
        MessageWriter::Instance()->WriteLineToConsole("ERROR: failed to open input file at \"data/problems/p054\"");
        //MessageWriter::Instance()->WriteToOutputBox("ERROR: failed to open input file at \"data/problems/p054\"");
        return ("ERROR: failed to open input file at \"data/problems/p054\"");
    }
}
