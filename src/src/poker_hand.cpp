#include "poker_hand.hpp"

#include <algorithm>

void PokerHand::SetHand(std::vector< std::string >& hand,unsigned int start_index,unsigned int end_index)
{
    std::pair< char, char > card {1, '1'};
    m_hand.fill(card);

    for(unsigned int i = start_index; i <= end_index; i++)
    {
        card.first = hand[i][0];
        card.second = hand[i][1];

        m_hand[i] = card;
    }

    /*std::sort(m_hand.begin(), m_hand.end(), [](std::pair< char, char > a, std::pair< char, char > b)
            {
                return b.first < a.first;
            });*/
}

bool PokerHand::WinnerOfHand(const PokerHand& opponent)
{
    return false;
}

void PokerHand::ProcessHand()
{

}

std::array< std::pair<char, char >, 5 > PokerHand::GetHand()
{
    return m_hand;
}
