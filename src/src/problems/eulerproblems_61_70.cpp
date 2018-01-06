#include "eulerproblems.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <utility>
#include <array>

#include "message_writer.hpp"
#include "clock.hpp"
#include "graphs_and_grids.hpp"
#include "utils.hpp"


std::string Problem061()//does not work yet, no idea what the problem is. Might change implementation to a recursive one, as this one is messy
{
    unsigned int chain_sum = 0;

    //polygonal numbers are written as P(s,n) being 's' the number of sides (3 = triangle) and 'n' the term
    std::array< std::pair<std::vector< unsigned int >, bool>, 6> poligonal_numbers;

    //{ generate polygonal numbers

    //generate valid numbers to check for chain
    //again the 10000 was chosen "at random"
    for(unsigned int n = 1; n < 10000; n++)
    {
        unsigned int element = n * (n + 1) / 2; //P(3,n)
        if(element > 999 && element < 10000)//will give 4 digit long numbers
        {
            poligonal_numbers[0].first.push_back(element);
            poligonal_numbers[0].second = false;
            //std::cout<<n<<" - "<<element<<std::endl;
        }

        element = n * n; //P(4,n)
        if(element > 999 && element < 10000)
        {
            poligonal_numbers[1].first.push_back(element);
            poligonal_numbers[1].second = false;
        }

        element = n * (3 * n - 1) / 2; //P(5,n)
        if(element > 999 && element < 10000)
        {
            poligonal_numbers[2].first.push_back(element);
            poligonal_numbers[2].second = false;
        }

        element = n * (2 * n - 1); //P(6,n)
        if(element > 999 && element < 10000)
        {
            poligonal_numbers[3].first.push_back(element);
            poligonal_numbers[3].second = false;
        }

        element = n * (5 * n - 3) / 2; //P(7,n)
        if(element > 999 && element < 10000)
        {
            poligonal_numbers[4].first.push_back(element);
            poligonal_numbers[4].second = false;
        }

        element = n * (3 * n - 2); //P(8,n)
        if(element > 999 && element < 10000)
        {
            poligonal_numbers[5].first.push_back(element);
            poligonal_numbers[5].second = false;
        }
    }
    //}

    std::array<unsigned int, 6> chain;
    bool chain_found = false;

    //try to change to a recursive implementation as the nested fors are messy
    //check for chain
    for(unsigned int i = 0; i < poligonal_numbers.size(); i++)//check for first
    {
        //{1º
//        if(chain_found)
//            break;
        poligonal_numbers[0].second = true;//vector in use
        std::vector< unsigned int > first_vector = poligonal_numbers[0].first;

        for(unsigned int first_number : first_vector)//run through the numbers in the 1º vector
        {
            if(chain_found)
                break;

            chain.fill(0);//clear array
            std::cout<<first_number<<" - ";
            chain[0] = first_number;

            for(unsigned int j = 0; j < poligonal_numbers.size(); j++)//check for 1º element
            {
                //{2º
                if(chain_found)
                    break;
                if(poligonal_numbers[j].second)//already in use
                    continue;

                //found valid 2º vector
                poligonal_numbers[j].second = true;//vector in use
                std::vector< unsigned int > second_vector = poligonal_numbers[j].first;

                for(unsigned int second_number : second_vector)//run through the numbers in the 2º vector
                {
                    if(chain_found)
                        break;
                    //check if can use second number
                    if(std::count(chain.begin(), chain.end(), second_number ) > 0)//number exists in array, so we cannot use it
                        continue;//jump to next number
                    if(!AreChainNumbers(first_number, second_number, 100))//not members of valid chain
                        continue;
                    std::cout<<second_number<<" - ";
                    chain[1] = second_number;

                    for(unsigned int k = 0; k < poligonal_numbers.size(); k++)//check for 2º element
                    {
                        //{3º
                        if(chain_found)
                            break;
                        if(poligonal_numbers[k].second)//already in use
                            continue;

                        //found valid 3º vector
                        poligonal_numbers[k].second = true;//vector in use
                        std::vector< unsigned int > third_vector = poligonal_numbers[k].first;

                        for(unsigned int third_number : third_vector)//run through the numbers in the 2º vector
                        {
                            if(chain_found)
                                break;
                            //check if can use second number
                            if(std::count(chain.begin(), chain.end(), third_number ) > 0)//number exists in array, so we cannot use it
                                continue;//jump to next number

                            if(!AreChainNumbers(second_number, third_number, 100))//not members of valid chain
                                continue;

                            if(!AreChainNumbers(third_number, first_number, 100))//not members of valid chain
                                continue;
                            std::cout<<third_number<<" - ";
                            chain[2] = third_number;

                            for(unsigned int l = 0; l < poligonal_numbers.size(); l++)//check for first
                            {
                                //{4º
                                if(chain_found)
                                    break;
                                if(poligonal_numbers[l].second)//already in use
                                    continue;

                                //found valid 4º vector
                                poligonal_numbers[l].second = true;//vector in use
                                std::vector< unsigned int > fourth_vector = poligonal_numbers[l].first;

                                for(unsigned int fourth_number : fourth_vector)//run through the numbers in the 2º vector
                                {
                                    if(chain_found)
                                        break;

                                    //check if can use second number
                                    if(std::count(chain.begin(), chain.end(), fourth_number ) > 0)//number exists in array, so we cannot use it
                                        continue;//jump to next number
                                    if(!AreChainNumbers(third_number, fourth_number, 100))//not members of valid chain
                                        continue;
                                    std::cout<<fourth_number<<" - ";
                                    chain[3] = fourth_number;

                                    for(unsigned int m = 0; m < poligonal_numbers.size(); m++)//check for first
                                    {
                                        //{5º
                                        if(chain_found)
                                            break;
                                        if(poligonal_numbers[m].second)//already in use
                                            continue;

                                        //found valid 5º vector
                                        poligonal_numbers[m].second = true;//vector in use
                                        std::vector< unsigned int > fifth_vector = poligonal_numbers[l].first;

                                        for(unsigned int fifth_number : fifth_vector)//run through the numbers in the 2º vector
                                        {
                                            if(chain_found)
                                                break;

                                            //check if can use second number
                                            if(std::count(chain.begin(), chain.end(), fifth_number ) > 0)//number exists in array, so we cannot use it
                                                continue;//jump to next number
                                            if(!AreChainNumbers(fourth_number, fifth_number, 100))//not members of valid chain
                                                continue;
                                            std::cout<<fifth_number<<" - ";
                                            chain[4] = fifth_number;

                                            for(unsigned int n = 0; n < poligonal_numbers.size(); n++)//check for first
                                            {
                                                //{6º
                                                if(chain_found)
                                                    break;

                                                if(poligonal_numbers[n].second)//already in use
                                                    continue;

                                                //found valid 6º vector
                                                poligonal_numbers[n].second = true;//vector in use
                                                std::vector< unsigned int > sixth_vector = poligonal_numbers[l].first;

                                                for(unsigned int sixth_number : sixth_vector)//run through the numbers in the 2º vector
                                                {
                                                    if(chain_found)
                                                        break;

                                                    //check if can use second number
                                                    if(std::count(chain.begin(), chain.end(), sixth_number ) > 0)//number exists in array, so we cannot use it
                                                        continue;//jump to next number
                                                    if(!AreChainNumbers(fifth_number, sixth_number, 100))//not members of valid chain
                                                        continue;

                                                    if(!AreChainNumbers(sixth_number, first_number, 100))//close chain
                                                        continue;
                                                    std::cout<<sixth_number;
                                                    chain[5] = sixth_number;

                                                    chain_found = true;

                                                    break;

                                                }//sixth

                                                poligonal_numbers[n].second = false;//"release" the vector to be used bay another sub loop
                                                //}
                                            }
                                        }//fifth

                                        poligonal_numbers[m].second = false;//"release" the vector to be used bay another sub loop
                                        //}
                                    }
                                }//fourth

                                poligonal_numbers[l].second = false;//"release" the vector to be used bay another sub loop
                                //}
                            }
                        }//third

                        poligonal_numbers[k].second = false;//"release" the vector to be used bay another sub loop
                        //}
                    }
                }//second

                poligonal_numbers[j].second = false;//"release" the vector to be used bay another sub loop
                std::cout<<std::endl;
                //}
            }

        }
        //}
    }

    for(unsigned int chain_element : chain)
    {
        chain_sum += chain_element;
        // MessageWriter::Instance()->WriteToOutputBox("P: "+std::to_string(chain_element));
    }

    //MessageWriter::Instance()->WriteToOutputBox("P061: "+std::to_string(chain_sum)+ " in "+Clock::Instance()->StopAndReturnClock(clock_id) + " ms");
    return std::to_string(chain_sum);
}


std::string Problem067()//this is the same as problem 18 but with a bigger triangle
{
    std::ifstream numbers_file ("data/problems/p067");
    std::string line;

    std::vector< std::vector< SimpleBinaryTreeNode<int> > > nodes;

    if (numbers_file.is_open())
    {
        //new line vector
        std::vector< SimpleBinaryTreeNode<int> > line_vector;

        std::vector< std::string > line_elements;


        while ( getline (numbers_file,line))
        {
            line = Trim(line);

            line_vector.clear();
            line_elements.clear();

            if(line.empty())//for safety
                break;

            line_elements = Explode( line, " " );

            for( unsigned int i = 0; i < line_elements.size(); i++ )
            {
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

                    /*while(current_node->m_max_value_parent)
                    {
                        MessageWriter::Instance()->WriteToConsole(" - "+std::to_string(current_node->m_max_value_parent->m_value));
                    }*/
                }
            }
            if(current_node->m_left_child != nullptr)//left side will be checked first
            {
                if(current_node->m_max_value + current_node->m_left_child->m_value > current_node->m_left_child->m_max_value)
                {
                    current_node->m_left_child->m_max_value = current_node->m_max_value + current_node->m_left_child->m_value;
                    current_node->m_left_child->m_max_value_parent = current_node;//set max parent for path backtrack
                }

                if(!current_node->m_left_child->m_stored)
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

                if(!current_node->m_right_child->m_stored)
                {
                    current_node->m_right_child->m_stored = true;
                    nodes_to_check_df.push(current_node->m_right_child);
                }
            }
        }

        return std::to_string(max_value);
    }
    else
    {
        MessageWriter::Instance()->WriteLineToConsole("ERROR: failed to open input file at \"data/problems/p067\"");
        //MessageWriter::Instance()->WriteToOutputBox("ERROR: failed to open input file at \"data/problems/p067\"");
        return ("ERROR: failed to open input file at \"data/problems/p067\"");
    }
}
