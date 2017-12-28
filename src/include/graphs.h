#ifndef GRAPHS_H
#define GRAPHS_H


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

#endif // GRAPHS_H
