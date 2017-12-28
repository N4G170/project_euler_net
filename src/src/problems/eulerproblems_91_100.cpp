#include "eulerproblems.h"

#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <utility>
#include <bitset>
#include <cmath>

#include "message_writer.h"
#include "clock.h"
#include "graphs.h"
#include "utils.hpp"

//Once again, the implementation is Mathematically correct
//and once again it suffers from precision errors
//I've calculated the area based on sides that the function marks as correct and I noticed that the decimal elements of the area are missing
//I've yet to find the reason why
std::string Problem094()
{
    //auto clock_id = Clock::Instance()->StartClock();

    unsigned long long perimeter_sum = 0;

    //unsigned int perimeter_limit = 1 000 000 000;
    unsigned long perimeter_limit = 100000000;

    //as we are working with integral numbers, as stated in the problem, the base cannot be an odd number, as we will divide it by 2 (area = height*base/2)
    for(unsigned int side = 3; ; side += 2 )
    {
        long double base_1 = side + 1;
        long double base_2 = side - 1;
        long double perimeter_1 = side * 2 + base_1;
        long double perimeter_2 = side * 2 + base_2;

        if(perimeter_1 < perimeter_limit )//side + 1
        {
            //Heron of Alexandria area formula a=SQRT(s(s-a)(s-b)(s-c)) where s = perimeter/2
            long double s = perimeter_1/2.0;
            long double a = s * (s-side)*(s-side)*(s-base_1);
            long double area = std::sqrt( a );

            std::cout.precision(25);
                std::cout<<"("<<side<<","<<side<<","<<base_1<<") P:"<<perimeter_1<<" A:"<<area<<" S:"<<s<<" a:"<<a<<std::endl;

            if( std::fmod(area, 1) == 0 )
            {
                perimeter_sum += perimeter_1;
//                std::cout.precision(25);
//                std::cout<<"("<<side<<","<<side<<","<<base_1<<") P:"<<perimeter_1<<" A:"<<area<<" S:"<<s<<" a:"<<a<<std::endl;
                //std::cout<<"("<<side<<","<<side<<","<<base<<") B:"<<b<<" H:"<<h<<" hei:"<<height<<std::endl;
            }
        }
        if(perimeter_2 < perimeter_limit )//side - 1
        {
            //Heron of Alexandria area formula a=SQRT(s(s-a)(s-b)(s-c)) where s = perimeter/2
            long double s = perimeter_2/2.0;
            long double a = s * (s-side)*(s-side)*(s-base_2);
            long double area = std::sqrt( a );

            std::cout.precision(25);
            std::cout<<"("<<side<<","<<side<<","<<base_2<<") P:"<<perimeter_2<<" A:"<<area<<" S:"<<s<<" a:"<<a<<std::endl;
           // MessageWriter::Instance()->WriteToOutputBox("P094: "+std::to_string(area));

            if( std::fmod(area, 1) == 0 )
            {
                perimeter_sum += perimeter_1;
//                std::cout.precision(25);
//                std::cout<<"("<<side<<","<<side<<","<<base_2<<") P:"<<perimeter_2<<" A:"<<area<<" S:"<<s<<" a:"<<a<<std::endl;
                //std::cout<<"("<<side<<","<<side<<","<<base<<") B:"<<b<<" H:"<<h<<" hei:"<<height<<std::endl;
            }
        }
        if(perimeter_1 > perimeter_limit && perimeter_2 > perimeter_limit)
            break;

//        //from Pitagoras Theorem, c^2 = a^2 + b^2
//        //we have side^2 = (base/2)^2 + a^2 <=> a^2 = side^2 - (base/2)^2 <=> a = sqrt(side^2 - (base/2)^2)
//        unsigned long half_base = base / 2;
//        long double b = std::pow(half_base, 2);
//        long double h = std::pow(side, 2);
//
//        //the 'a' from the formula
//        long double height = std::sqrt(h - b);
//
//        if( std::fmod(height, 1) == 0 )//no need to calculate the area, as we will, always, have an integral area if the height is integral
//        {
//            perimeter_sum += perimeter;
//            std::cout<<"("<<side<<","<<side<<","<<base<<") P:"<<perimeter<<" A:"<<(height*half_base)<<std::endl;
//            //std::cout<<"("<<side<<","<<side<<","<<base<<") B:"<<b<<" H:"<<h<<" hei:"<<height<<std::endl;
//        }

//        //Heron of Alexandria area formula a=SQRT(s(s-a)(s-b)(s-c)) where s = perimeter/2
//        long double s = perimeter/2.0;
//        long double a = s * (s-side)*(s-side)*(s-base);
//        long double area = std::sqrt( a );
//
//        if( std::fmod(area, 1) == 0 )
//        {
//            perimeter_sum += perimeter;
//            //std::cout.precision(25);
//            //std::cout<<"("<<side<<","<<side<<","<<base<<") P:"<<perimeter<<" A:"<<area<<" S:"<<s<<" a:"<<a<<std::endl;
//            //std::cout<<"("<<side<<","<<side<<","<<base<<") B:"<<b<<" H:"<<h<<" hei:"<<height<<std::endl;
//        }

        //if(side == 5)
            //std::cout<<side<<","<<side<<","<<base<<" - "<<(base/2)*height<<std::endl;
    }

    std::cout<<perimeter_sum<<std::endl;
    //MessageWriter::Instance()->WriteToOutputBox("P036: "+std::to_string(double_palindrome_sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");

    //return ("P036: "+std::to_string(double_palindrome_sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    return "";
}

