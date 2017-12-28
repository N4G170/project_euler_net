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

#include "graphs.h"
#include "message_writer.h"
#include "clock.h"

//Implementation is based on problems 18 and 67
void Problem081()
{
    //auto clock_id = Clock::Instance()->StartClock();

    std::ifstream numbers_file ("data/problems/p081");
    std::string line;

    std::vector< std::vector< SimpleGraphNode_p8x > > nodes;

    if (numbers_file.is_open())
    {
        //new line vector
        std::vector< SimpleGraphNode_p8x > line_vector;

        std::vector< std::string > line_elements;


        while ( getline (numbers_file,line))
        {
            line = Trim(line);

            line_vector.clear();
            line_elements.clear();

            if(line.empty())//for safety
                break;

            line_elements = Explode( line, "," );

            for( unsigned int i = 0; i < line_elements.size(); i++ )
            {
                //create a node for each number in the file
                SimpleGraphNode_p8x node;

                node.m_min_value_parent = nullptr;
                node.m_left_node = nullptr;
                node.m_right_node = nullptr;
                node.m_top_node = nullptr;
                node.m_bottom_node = nullptr;

                //convert string to ulong
                node.m_value = std::stoul( line_elements[i] );
                node.m_min_value = INT_MAX;
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
        for(unsigned int l=0; l < nodes.size(); l++)//each line (last line is ignored, as it has no children)
        {
            for(unsigned int c = 0; c < nodes[l].size(); c++)//line element
            {
                if(l < nodes.size() - 1)//not last line
                {
                    nodes[l][c].m_bottom_node = &nodes[l + 1][c];
                }

                if(c < nodes[l].size() - 1)//not last column
                {
                    nodes[l][c].m_right_node = &nodes[l][c + 1];
                }

            }
        }

        //Dijkstra's like algorithm
        std::queue<SimpleGraphNode_p8x*> nodes_to_check_df;
        int min_value = INT_MAX;;

        SimpleGraphNode_p8x* current_node = nullptr;

        nodes_to_check_df.push(&nodes[0][0]);
        nodes_to_check_df.front()->m_min_value = nodes_to_check_df.front()->m_value;//set min value to its value, for the first node

        while(!nodes_to_check_df.empty())
        {
            current_node = nodes_to_check_df.front();
            nodes_to_check_df.pop();

            if(current_node->m_bottom_node == nullptr && current_node->m_right_node == nullptr )//reached the final nodes, so we "extract" its value
            {
                if(current_node->m_min_value < min_value)
                {
                    min_value = current_node->m_min_value;
                }
            }
            if(current_node->m_bottom_node != nullptr)//left side will be checked first
            {
                if(current_node->m_min_value + current_node->m_bottom_node->m_value < current_node->m_bottom_node->m_min_value)
                {
                    current_node->m_bottom_node->m_min_value = current_node->m_min_value + current_node->m_bottom_node->m_value;
                    current_node->m_bottom_node->m_min_value_parent = current_node;//set min parent for path backtrack
                }

                if(!current_node->m_bottom_node->m_stored)
                {
                    current_node->m_bottom_node->m_stored = true;
                    nodes_to_check_df.push(current_node->m_bottom_node);
                }
            }
            if(current_node->m_right_node != nullptr)
            {
                if(current_node->m_min_value + current_node->m_right_node->m_value < current_node->m_right_node->m_min_value)
                {
                    current_node->m_right_node->m_min_value = current_node->m_min_value + current_node->m_right_node->m_value;
                    current_node->m_right_node->m_min_value_parent = current_node;//set min parent for path backtrack
                }

                if(!current_node->m_right_node->m_stored)
                {
                    current_node->m_right_node->m_stored = true;
                    nodes_to_check_df.push(current_node->m_right_node);
                }
            }
        }

        ProblemsResults::Instance()->SetStoredResult("81", std::to_string(min_value));
         //MessageWriter::Instance()->WriteToOutputBox("P018: "+std::to_string(max_value)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
         //return ("P081: "+std::to_string(min_value)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    }
    else
    {
        MessageWriter::Instance()->WriteLineToConsole("ERROR: failed to open input file at \"data/problems/p081\"");
        //MessageWriter::Instance()->WriteToOutputBox("ERROR: failed to open input file at \"data/problems/p018\"");
        //return ("ERROR: failed to open input file at \"data/problems/p081\"");
    }
}

//Based on testing I'm getting the write path, but the value result is wrong
//Need more testing
std::string Problem082()
{
    auto clock_id = Clock::Instance()->StartClock();

    std::ifstream numbers_file ("data/problems/p083");//p083 has the same matrix as the example, so I use it to test the algorithm
    std::string line;

    std::vector< std::vector< SimpleGraphNode_p8x > > nodes;

    if (numbers_file.is_open())
    {
        //new line vector
        std::vector< SimpleGraphNode_p8x > line_vector;

        std::vector< std::string > line_elements;


        while ( getline (numbers_file,line))
        {
            line = Trim(line);

            line_vector.clear();
            line_elements.clear();

            if(line.empty())//for safety
                break;

            line_elements = Explode( line, "," );

            for( unsigned int i = 0; i < line_elements.size(); i++ )
            {
                SimpleGraphNode_p8x node;

                node.m_min_value_parent = nullptr;
                node.m_left_node = nullptr;
                node.m_right_node = nullptr;
                node.m_top_node = nullptr;
                node.m_bottom_node = nullptr;

                //convert string to ulong
                node.m_value = std::stoul( line_elements[i] );
                node.m_min_value = INT_MAX;
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
        for(unsigned int l=0; l < nodes.size(); l++)//each line (last line is ignored, as it has no children)
        {
            for(unsigned int c = 0; c < nodes[l].size(); c++)//line element
            {
                if(l < nodes.size() - 1)//not last line
                {
                    nodes[l][c].m_bottom_node = &nodes[l + 1][c];
                }

                if(c < nodes[l].size() - 1)//not last column
                {
                    nodes[l][c].m_right_node = &nodes[l][c + 1];
                }

                if(l > 0)//not first line
                {
                    nodes[l][c].m_top_node = &nodes[l - 1][c];
                }
            }
        }


        //Dijkstra's like algorithm
        std::queue<SimpleGraphNode_p8x*> nodes_to_check_df;
        int min_value = INT_MAX;;


        for(unsigned int i = 0; i<nodes.size(); i++)
        {
            SimpleGraphNode_p8x* current_node = nullptr;

            nodes_to_check_df.push(&nodes[i][0]);


            for(unsigned int l=0; l < nodes.size(); l++)//each line (last line is ignored, as it has no children)
            {
                for(unsigned int c = 0; c < nodes[l].size(); c++)//line element
                {
                    nodes[l][c].m_min_value = INT_MAX;
                }
            }

            nodes_to_check_df.front()->m_min_value = nodes_to_check_df.front()->m_value;//set max value to its value, for the first node

            while(!nodes_to_check_df.empty())
            {
                current_node = nodes_to_check_df.front();
                nodes_to_check_df.pop();

                if(current_node->m_right_node == nullptr )//reached the final nodes, so we "extract" its value
                {
                    if(current_node->m_min_value < min_value)
                    {
                        min_value = current_node->m_min_value;

                        //min_value = 0;
                        auto p = current_node;
                        while(p->m_min_value_parent)
                        {
                            //min_value+=p->m_value;
                            std::cout<<p->m_value<<"\n";
                            p=p->m_min_value_parent;
                        }
                    }

//                    //clear tmp values
//                    auto p = current_node;
//                    while(p->m_min_value_parent)
//                    {
//                        p->m_min_value = INT_MAX;
//                        auto tmp = p->m_min_value_parent;
//                        p->m_min_value_parent = nullptr;
//                        p=tmp;
//                    }
                }
                if(current_node->m_bottom_node != nullptr)//left side will be checked first
                {
                    if(current_node->m_min_value + current_node->m_bottom_node->m_value < current_node->m_bottom_node->m_min_value)
                    {
                        current_node->m_bottom_node->m_min_value = current_node->m_min_value + current_node->m_bottom_node->m_value;
                        current_node->m_bottom_node->m_min_value_parent = current_node;//set max parent for path backtrack
                    }

                    if(!current_node->m_bottom_node->m_stored)
                    {
                        current_node->m_bottom_node->m_stored = true;
                        nodes_to_check_df.push(current_node->m_bottom_node);
                    }
                }
                if(current_node->m_right_node != nullptr)
                {
                    if(current_node->m_min_value + current_node->m_right_node->m_value < current_node->m_right_node->m_min_value)
                    {
                        current_node->m_right_node->m_min_value = current_node->m_min_value + current_node->m_right_node->m_value;
                        current_node->m_right_node->m_min_value_parent = current_node;
                    }

                    if(!current_node->m_right_node->m_stored)
                    {
                        current_node->m_right_node->m_stored = true;
                        nodes_to_check_df.push(current_node->m_right_node);
                    }
                }
                if(current_node->m_top_node != nullptr)
                {
                    if(current_node->m_min_value + current_node->m_top_node->m_value < current_node->m_top_node->m_min_value)
                    {
                        current_node->m_top_node->m_min_value = current_node->m_min_value + current_node->m_top_node->m_value;
                        current_node->m_top_node->m_min_value_parent = current_node;
                    }

                    if(!current_node->m_top_node->m_stored)
                    {
                        current_node->m_top_node->m_stored = true;
                        nodes_to_check_df.push(current_node->m_top_node);
                    }
                }
            }
        }
         //MessageWriter::Instance()->WriteToOutputBox("P018: "+std::to_string(max_value)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
         return ("P082: "+std::to_string(min_value)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    }
    else
    {
        MessageWriter::Instance()->WriteLineToConsole("ERROR: failed to open input file at \"data/problems/p082\"");
        //MessageWriter::Instance()->WriteToOutputBox("ERROR: failed to open input file at \"data/problems/p018\"");
        return ("ERROR: failed to open input file at \"data/problems/p081\"");
    }
}
