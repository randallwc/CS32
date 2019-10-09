#include "Board.h"

Board::Board(int nHoles, int nInitialBeansPerHole)
{
    if(nHoles < 0) // if invalid holes
        nHoles = 1;
    if(nInitialBeansPerHole < 0) // if invalid number of initil beans per hole
        nInitialBeansPerHole = 0;
    m_holes = nHoles;
    m_beansPH = nInitialBeansPerHole;
    m_north.push_back(0); // make north pot
    m_south.push_back(0); // make south pot
    for(int i = 1; i <= m_holes; i++) // push beans onto stack
    {
        m_north.push_back(m_beansPH);
        m_south.push_back(m_beansPH);
    }
}

Board::Board (const Board &other) : m_north(other.m_north), m_south(other.m_south) // copy constructor
{
    m_holes = other.m_holes;
    m_beansPH = other.m_beansPH;
}

int Board::holes() const
{
    return m_holes;
}

int Board::beans(Side s, int hole) const
{
    if(hole < 0 || hole > m_holes)
        return -1;
    if(s == NORTH)
    {
        return m_north.at(hole);
    }
    else
    {
        return m_south.at(hole);
    }
}

int Board::beansInPlay(Side s) const
{
    int count = 0;
    if(s == NORTH)
    {
        for(int i = 1; i <= m_holes; i++)
        {
            count = count + m_north.at(i); // add to count each loop
        }
        return count;
    }
    else
    {
        for(int i = 1; i <= m_holes; i++)
        {
            count = count + m_south.at(i);
        }
        return count;
    }
}
int Board::totalBeans() const
{
    int count = 0;
    for(int i = 0; i <= m_holes; i++)
    {
        count = count + m_north.at(i) + m_south.at(i);
    }
    return count;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
    if(hole <= 0 || hole > m_holes) // check if hole is valid
        return false;
    int count = 0;
    if(s == NORTH) // if start size is NORTH
    {
        count = m_north.at(hole); // get ammount of beans at hole
        if(count == 0) // if zero return
            return false;
        m_north.at(hole) = 0; // set beans at hole to zero
        int pos = hole - 1; // start position for first loop is one hole to the left of chosen hole
        
        while(count != 0) // while loop for looping through the board
        {
            for(int i = pos; i >= 0 && count != 0; i--) // backwards while loop for north
            {
                m_north.at(i)++;
                count--;
                if(count == 0)
                {
                    endSide = NORTH;
                    endHole = i;
                    return true;
                }
            }
            pos = m_holes; // set the start for next loop to be the last hole
            for(int i = 1; i < m_south.size() ; i++) // loop through south from first hole to last
            {
                m_south.at(i)++;
                count--;
                if(count == 0)
                {
                    endSide = SOUTH;
                    endHole = i;
                    return true;
                }
            }
//            if(count < 0)
//                exit(4);
        }
        return true;
    }
    else // if start side is SOUTH
    {
        count = m_south.at(hole); // make a count of how many beans
        if(count == 0)
            return false;
        m_south.at(hole) = 0; // make starting hole = 0
        
        int pos = hole + 1; // starting position for the first loop is one past the chosen hole
        
        while(count != 0) // while loop for looping through the board
        {
            for(int i = pos; i < m_south.size() && count != 0; i++) // loop through south
            {
                m_south.at(i)++;
                count--;
                if(count == 0)
                {
                    endSide = SOUTH;
                    endHole = i;
                    return true;
                }
            }
            pos = 1; // set starting position for next loop to one
            if(count != 0) // add to south's pot
            {
                m_south.at(0)++;
                count--;
            }
            if(count == 0)
            {
                endSide = SOUTH;
                endHole = 0;
                return true;
            }
            for(int i = m_holes; i > 0; i--) // loop backwards through north
            {
                m_north.at(i)++;
                count--;
                if(count == 0)
                {
                    endSide = NORTH;
                    endHole = i;
                    return true;
                }
            }
//            if(count < 0)
//                exit(4);
        }
        return true;
    }
}

bool Board::moveToPot(Side s, int hole, Side potOwner)
{
    if (hole <= 0 || hole > m_holes) // bad input
    {
        return false;
    }
    int count = 0;
    if (s == NORTH) // if north
    {
        count = m_north.at(hole); // get a count value
        m_north.at(hole) = 0;  // set hole to 0
    }
    else // if south
    {
        count = m_south.at(hole);
        m_south.at(hole) = 0;
    }
    
    if(potOwner == NORTH)
    {
        m_north.at(0) = m_north.at(0) + count;//increment pot with count
        return true;
    }
    else
    {
        m_south.at(0) = m_south.at(0) + count;
        return true;
    }
}

bool Board::setBeans(Side s, int hole, int beans)
{
    if(hole < 0 || hole > m_holes)// invalid hole
    {
        return false;
    }
    if(s == NORTH) // if north
    {
        m_north.at(hole) = beans; // change number at vector
        return true;
    }
    else // if south
    {
        m_south.at(hole) = beans;
        return true;
    }
}
