#ifndef POKER_HAND_H
#define POKER_HAND_H

#include <vector>
#include <array>
#include <utility>
#include <string>

enum PokerHandRank
{
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_KIND,
    STRAIGHT_FLUSH,
    ROYAL_FLUSH
};

/**
 * \brief Class to be used in problem 54 (under construction)
 */
class PokerHand
{
    public:
        void SetHand(std::vector< std::string >& hand,unsigned int start_index,unsigned int end_index );

        bool WinnerOfHand(const PokerHand& opponent);

        std::array< std::pair<char, char >, 5 > GetHand();

    private:
        std::array< std::pair<char, char >, 5 > m_hand;
        PokerHandRank m_rank;

        void ProcessHand();
};


#endif // POKER_HAND_H
