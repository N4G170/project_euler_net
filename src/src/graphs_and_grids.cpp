#include "graphs_and_grids.hpp"
#include <set>

#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////            Grids           ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<int> LoadProblemMatrixAsRowMajorVector(const std::string& problem_file)
{
    std::ifstream numbers_file ("data/problems/"+problem_file);//p083 has the same matrix as the example, so I use it to test the algorithm
    std::string line;

    std::vector<int> grid;

    if (numbers_file.is_open())
    {
        //new line vector
        std::vector< std::string > line_elements;

        while ( getline (numbers_file,line))
        {
            line = Trim(line);

            if(line.empty())//for safety
                break;

            line_elements = Explode( line, "," );

            for( unsigned int i = 0; i < line_elements.size(); i++ )
            {
                grid.push_back( std::stoi(line_elements[i]) );
            }

        }//while( getline (numbers_file,line))

        //close file as we no longer need it
        numbers_file.close();
    }

    return grid;
}

long FindShortPath(const int& start_index, const int& target_index, const int& grid_width, const int& grid_height, const std::vector<int>& grid, const DirectionsFlags& directions)
{
    std::multiset<Node, Node> to_visit;//cost is the key amd the value is the index
    std::map<int, bool> open_nodes;//keeps record if a node is open
    std::map<int, bool> closed_nodes;//keeps record if a node is open
    std::map<int, long> g_costs;//cost of moving to a cell
    std::map<int,int> parents;

    //Start path find
    //create first node (index, cost to reach node including self value)
    Node current_node{start_index, grid[start_index]};
    to_visit.insert(current_node);//inserts the first cell in the set so we can start searching
    parents[start_index] = -1;


    while(to_visit.size() > 0)//we have elements to check and we are not closing
    {
        //get a copy of the node with lowest cost
        Node current_node = *to_visit.begin();
        //remove the first cell as we are processing it
        to_visit.erase(to_visit.begin());

        closed_nodes[current_node.index] = true;
        open_nodes[current_node.index] = false;

        //we found the destination
        if(current_node.index == target_index)
        {
            return current_node.total_cost;
        }

        //go search for neighbors
        std::queue< int > neighbors_queue = GetGridNeighbors(current_node.index, grid_width, grid_height, directions);

        while(neighbors_queue.size() > 0)
        {
            int neighbor = neighbors_queue.front();
            neighbors_queue.pop();//remove first

            if( closed_nodes[neighbor] )//node already processed in a previous step
                continue;

            //calculate the g_cost to neighbor from current node
            int new_neighbor_g_cost = current_node.total_cost + grid[neighbor];

            if(!open_nodes[neighbor] || new_neighbor_g_cost < GetMapValue<int, long>(g_costs, neighbor, grid.size()) )//new node or one with lower g_cost
            {
                g_costs[neighbor] = new_neighbor_g_cost;//set new cost
                parents[neighbor] = current_node.index;

                Node new_node{ neighbor, new_neighbor_g_cost };//(index, cost to reach node including self value)

                if(!open_nodes[neighbor])//add new to open set
                {
                    to_visit.insert(new_node);
                    open_nodes[neighbor] = true;
                }
                else//update node in the set
                {
                    //custom condition find
                    auto search_result = std::find_if(to_visit.begin(), to_visit.end(),
                    [&neighbor](const Node& stored_node)
                    {
                        return stored_node.index == neighbor;
                    });

                    if(search_result != to_visit.end())//found item
                    {
                        to_visit.erase(search_result);//remove old
                        to_visit.insert(new_node);//insert updated node
                    }
                }
            }
        }//while(neighbors_queue.size() > 0)
    }

    return -1;
}

/**
    \brief Extract the X coordinate from the row-major array index
*/
int GetCoordinateX(const int& index, const int& map_width){ return index % map_width; }
/**
    \brief Extract the Y coordinate from the row-major array index
*/
int GetCoordinateY(const int& index, const int& map_width){ return index / map_width; }
/**
    \brief Calculate the row-major array index of a given x, y pair
*/
int GetIndexFromCoordinate(const int& x, const int& y, const int& map_width){ return y * map_width + x; }

/**
    \brief Checks if a given node position is passable or not (invalid positions are marked as impassable)
*/
const bool IsValid(const int& x, const int& y, const int& map_width, const int& map_height)
{
    return x >= 0 && x < (map_width) && y >= 0 && y < (map_height);
}

std::queue<int> GetGridNeighbors(const int& current_index, const int& map_width, const int& map_height, const DirectionsFlags& directions)
{
    std::queue<int> neighbors;

    //check adjacent cells
    unsigned short current_node_y = GetCoordinateY(current_index, map_width);
    unsigned short current_node_x = GetCoordinateX(current_index, map_width);

    //up
    if(directions.north && IsValid(current_node_x, current_node_y - 1, map_width, map_height))//has row above
    {
        neighbors.push(GetIndexFromCoordinate(current_node_x, current_node_y - 1, map_width));//move one up
    }
    //down
    if(directions.south && IsValid(current_node_x, current_node_y + 1, map_width, map_height))//has row bellow
    {
        neighbors.push(GetIndexFromCoordinate(current_node_x, current_node_y + 1, map_width));//move one down
    }
    //left
    if(directions.west && IsValid(current_node_x - 1, current_node_y, map_width, map_height))//has left
    {
        neighbors.push(GetIndexFromCoordinate(current_node_x - 1, current_node_y, map_width));//move one left
    }
    //right
    if(directions.east && IsValid(current_node_x + 1, current_node_y, map_width, map_height))//has right
    {
        neighbors.push(GetIndexFromCoordinate(current_node_x + 1, current_node_y, map_width));//move one right
    }

    return neighbors;
}

/**
\brief Return a dictionary value of the user defined default value. This function can be made generic for other container types.
*/
template< typename T, typename U>
U GetMapValue(std::map<T,U>& container, const T& key, const U& default_value)
{
    auto search = container.find(key);
    if(search == container.end())//if the key does not exist, create it and set default value
        container[key] = default_value;
    return container[key];
}
