#ifndef GRAPHS_AND_GRIDS_HPP
#define GRAPHS_AND_GRIDS_HPP

#include <fstream>//files
#include <queue>
#include "utils.hpp"

/**
* \brief Small struct used by Euler Problems
*/
struct SquareGridGraphNode
{
    unsigned int m_node_id;//an easy way to id the node

    //as this struct will be used no "mark" points on a square grid itl will "only" have 4 connection (max)
    SquareGridGraphNode* m_up_node;
    SquareGridGraphNode* m_down_node;
    SquareGridGraphNode* m_right_node;
    SquareGridGraphNode* m_left_node;
};

/**
* \brief Small struct used by Euler Problems
*/
template<typename T>
struct SimpleBinaryTreeNode
{
    T m_value;
    T m_max_value;
    bool m_stored;

    SimpleBinaryTreeNode* m_max_value_parent;

    SimpleBinaryTreeNode* m_left_child;
    SimpleBinaryTreeNode* m_right_child;
};

/**
* \brief Small struct used by Euler Problems 81 82 83
*/
struct SimpleGraphNode_p8x
{
    int m_value;
    int m_min_value;
    bool m_stored;

    SimpleGraphNode_p8x* m_min_value_parent;

    SimpleGraphNode_p8x* m_left_node;
    SimpleGraphNode_p8x* m_right_node;
    SimpleGraphNode_p8x* m_top_node;
    SimpleGraphNode_p8x* m_bottom_node;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////            Grids           ////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DirectionsFlags
{
    bool north;
    bool south;
    bool east;
    bool west;
};

std::vector<int> LoadProblemMatrixAsRowMajorVector(const std::string& problem_file);

long FindShortPath(const int& start_index, const int& target_index, const int& grid_width, const int& grid_height, const std::vector<int>& grid, const DirectionsFlags& directions);

struct Node
{
    int index = 0;
    long total_cost;//cost to this node, includes n_cost

    Node(){}

    Node(int new_index,  long new_total_cost):index{new_index}, total_cost{new_total_cost}
    { }

    bool operator() (const Node& left_node, const Node& right_node) const//used by multiset
    {
        return left_node.total_cost < right_node.total_cost;
    }
};

/**
    \brief Extract the X coordinate from the row-major array index
*/
int GetCoordinateX(const int& index, const int& map_width);
/**
    \brief Extract the Y coordinate from the row-major array index
*/
int GetCoordinateY(const int& index, const int& map_width);
/**
    \brief Calculate the row-major array index of a given x, y pair
*/
int GetIndexFromCoordinate(const int& x, const int& y, const int& map_width);

/**
    \brief Checks if a given node position is passable or not (invalid positions are marked as impassable)
*/
const bool IsValid(const int& x, const int& y, const int& map_width, const int& map_height);



std::queue<int> GetGridNeighbors(const int& current_index, const int& map_width, const int& map_height, const DirectionsFlags& directions);

/**
\brief Return a dictionary value of the user defined default value. This function can be made generic for other container types.
*/
template< typename T, typename U>
U GetMapValue(std::map<T,U>& container, const T& key, const U& default_value);

#endif // GRAPHS_AND_GRIDS_HPP
