#include "eulerproblems.hpp"
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
#include <set>

#include "graphs_and_grids.hpp"
#include "message_writer.hpp"
#include "clock.hpp"

//Implementation is based on problems 18 and 67
std::string Problem081()
{
    //NSEW
    DirectionsFlags directions{false, true, true, false};

    //load grid
    std::vector<int> grid = LoadProblemMatrixAsRowMajorVector("p081");

    long_t short_path = FindShortPath(0, 80*80-1, 80, 80, grid, directions);

    // MessageWriter::Instance()->WriteToOutputBox("P081: "+std::to_string(short_path)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    return std::to_string(short_path);
}

//Based on testing I'm getting the write path, but the value result is wrong
//Need more testing
std::string Problem082()
{
    //NSEW
    DirectionsFlags directions{true, true, true, false};

    //load grid
    std::vector<int> grid = LoadProblemMatrixAsRowMajorVector("p082");
    int width = 80;

    long_t short_path = LONG_MAX;

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < width; j++)
        {
            long_t tmp_path = FindShortPath(i * width, j * width + (width-1), width, width, grid, directions);

            if(tmp_path < short_path)
                short_path = tmp_path;
        }
    }

    return std::to_string(short_path);
}

std::string Problem083()
{
    //NSEW
    DirectionsFlags directions{true, true, true, true};

    //load grid
    std::vector<int> grid = LoadProblemMatrixAsRowMajorVector("p083");

    long_t short_path = FindShortPath(0, 80*80-1, 80, 80, grid, directions);

    return std::to_string(short_path);
}
