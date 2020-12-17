#include "ScoreList.h"

ScoreList::ScoreList():m_sequence()
{
    
}

bool ScoreList::add(unsigned long score)
{
    if (score > 100)
    {
        return false;
    }
    if (m_sequence.insert(m_sequence.size(), score) == -1)
    {
        return false;
    }
    return true;
}

bool ScoreList::remove(unsigned long score)
{
    int loc = m_sequence.find(score);
    if (loc == -1)
    {
        return false;
    }
    m_sequence.erase(loc);
    return true;
}

int ScoreList::size() const
{
    return m_sequence.size();
}

unsigned long ScoreList::minimum() const
{
    if (m_sequence.empty())
    {
        return NO_SCORE;
    }
    
    unsigned long min;
    m_sequence.get(0, min);
    
    unsigned long temp;
    
    for(int i = 0; i < m_sequence.size(); i++)
    {
        m_sequence.get(i, temp);
        
        if (min > temp)
        {
            min = temp;
        }
    }
    return min;
}

unsigned long ScoreList::maximum() const
{
    if (m_sequence.empty())
    {
        return NO_SCORE;
    }
    
    unsigned long max;
    m_sequence.get(0, max);
    
    unsigned long temp;
    
    for(int i = 0; i < m_sequence.size(); i++)
    {
        m_sequence.get(i, temp);
        
        if (max < temp)
        {
            max = temp;
        }
    }
    return max;
}
