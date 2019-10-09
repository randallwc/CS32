#include "Game.h"
#include <iostream>

Game::Game(const Board& b, Player* south, Player* north)
: m_north(north), m_south(south), m_board(b), m_turn(SOUTH)
{

}

void Game::display() const
{
    int holes = m_board.holes();
    std::cout << "\t "<<m_north->name() << std::endl << "    "; // outputs north's name
    for(int i = 1; i <= holes; i++) // outputs the north holes
    {
        std::cout << m_board.beans(NORTH, i) << "  ";
    }
    std::cout << std::endl << "  " <<m_board.beans(NORTH, 0); // outputs north's pot
    for(int i = 0; i < holes; i++) // outputs the spaces
    {
        std::cout<<"   ";
    }
    std::cout << m_board.beans(SOUTH, 0) << std::endl << "    "; // outputs south's pot
    for(int i = 1; i <= holes; i++) // outputs south's holes
    {
        std::cout << m_board.beans(SOUTH, i) << "  ";
    }
    std::cout << std::endl;
    std::cout << "\t " <<m_south->name() << std::endl;
}

//      Homer
//   2  2  2
// 0         0
//   2  2  2
//      Marge


void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
    // if the player who's turn it is can still make a move game isnt over
    if(m_board.beansInPlay(NORTH) > 0 && m_board.beansInPlay(SOUTH) > 0)
    {
        over = false;
        return;
    }
    //if north wins
    if(m_board.beans(NORTH, 0) + m_board.beansInPlay(NORTH) > m_board.beans(SOUTH, 0) + m_board.beansInPlay(SOUTH))
    {
        over = true;
        hasWinner = true;
        winner = NORTH;
        return;
    }
    //if south wins
    if(m_board.beans(SOUTH, 0) + m_board.beansInPlay(SOUTH) > m_board.beans(NORTH, 0) + m_board.beansInPlay(NORTH))
    {
        over = true;
        hasWinner = true;
        winner = SOUTH;
        return;
    }
    // if there is a tie
    if(m_board.beans(NORTH, 0) + m_board.beansInPlay(NORTH) == m_board.beans(SOUTH, 0) + m_board.beansInPlay(SOUTH))
    {
        over = true;
        hasWinner = false;
        return;
    }
}

bool Game::move()
{
    
    bool over = false;
    bool hasWinner = false;
    Side winner = NORTH;
    status(over, hasWinner, winner);
    if(over) // if already over
    {
        if(m_board.beansInPlay(SOUTH) == 0 || m_board.beansInPlay(NORTH) == 0)// if there is a winner then sweep
        {
            for(int i = 1; i <= m_board.holes(); i++)
            {
                m_board.moveToPot(NORTH, i, NORTH);
                m_board.moveToPot(SOUTH, i, SOUTH);
            }
        }
        return false;
    }
    
    while (1)// infinite loop until game is over
    {
        int move = -1;
        
        if(m_turn == NORTH) // if north's turn
        {
            move = m_north->chooseMove(m_board, m_turn);
        }
        else if(m_turn == SOUTH) // if south's turn
        {
            move = m_south->chooseMove(m_board, m_turn);
        }
        
        if(move == -1) // if invalid move break because game is over
        {
            break;
        }
        
        Side endSide;
        int endHole;
//        assert(m_board.sow(m_turn, move, endSide, endHole));
        if(!m_board.sow(m_turn, move, endSide, endHole)) // if sow of the move
        {
            exit(11);
        }
        
        if(endSide == m_turn) // if end side is on the same side
        {
            if(endHole == 0) // if end hole is in a pot
            {
                status(over, hasWinner, winner);
                if(over)// if game over break
                {
                    break;
                }
                display();
                std::string name;
                if(m_turn == NORTH)
                {
                    name = m_north->name();
                }
                else
                {
                    name = m_south->name();
                }
                std::cout << name <<" gets another turn."<< std::endl;
                continue;
            }
            if(m_turn == endSide && m_board.beans(endSide, endHole) == 1 && m_board.beans(opponent(endSide), endHole) > 0) // do a capture
            {
                m_board.moveToPot(m_turn, endHole, m_turn);
                m_board.moveToPot(opponent(m_turn), endHole, m_turn);
            }
            break;
        }
        else// if end side is on the other side of the board
        {
            break;
        }
//        exit(12);
    }
    
    status(over, hasWinner, winner);
    bool oneSideHasBeans = m_board.beansInPlay(NORTH) > 0 || m_board.beansInPlay(SOUTH) > 0;
    if(over && oneSideHasBeans)
    {
        display();
        std::string name;
        if(m_board.beansInPlay(NORTH))
            name = m_north->name();
        else
            name = m_south->name();
        
        std::cout << "Sweeping remaining beans into " << name << "'s pot."<< std::endl;
        for(int i = 1; i <= m_board.holes(); i++) // sweep beans into pot
        {
            m_board.moveToPot(NORTH, i, NORTH);
            m_board.moveToPot(SOUTH, i, SOUTH);
        }
    }
    
    m_turn = opponent(m_turn); // when over change the turn
    return true;
}

void Game::play()
{
    bool over = false;
    bool hasWinner = false;
    Side winner;
    status(over, hasWinner, winner);
    if(m_board.beansInPlay(SOUTH) == 0 || m_board.beansInPlay(NORTH) == 0)// if there is a winner then sweep
    {
        for(int i = 1; i <= m_board.holes(); i++)
        {
            m_board.moveToPot(NORTH, i, NORTH);
            m_board.moveToPot(SOUTH, i, SOUTH);
        }
    }
    bool pressEnter = false;
    if(!m_north->isInteractive() && !m_south->isInteractive())// if both are interactive then you have to press enter
    {
        pressEnter = true;
    }

    display();
    while(!over)
    {
        move();
        display();
        status(over, hasWinner, winner);
        if(pressEnter)
        {
            std::cout << "Press ENTER to continue";
            std::cin.ignore();
        }
    }
    
    if(hasWinner)
    {
        std::string name;
        if(winner == NORTH)
        {
            name = m_north->name();
        }
        else
        {
            name = m_south->name();
        }
        std::cout << "The winner is "<< name <<"." << std::endl;
    }
    else if (!hasWinner)
    {
        std::cout << "The game resulted in a tie." << std::endl;
    }
}

int Game::beans(Side s, int hole) const
{
    return m_board.beans(s, hole);
}

