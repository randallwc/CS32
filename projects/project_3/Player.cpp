#include "Player.h"
#include <iostream>

Player::Player(std::string name)
{
    m_name = name;
}

std::string Player::name() const
{
    return m_name;
}

bool Player::isInteractive() const
{
    return false;
}

Player::~Player()
{

}

//HUMAN PLAYER
HumanPlayer::HumanPlayer(std::string name) : Player(name)
{

}

bool HumanPlayer::isInteractive() const
{
    return true;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const
{
    if(b.beansInPlay(s) == 0) // if you cant make a move
        return -1;
    int move = -1;
    while(1) // infinite loop to choose moves
    {
        std::cout << "Select a hole, " << Player::name() << ": ";
        std::cin >> move;
        
        if(move > 0 && move <= b.holes() && b.beans(s, move) > 0) // break out of the loop if you make a valid move
        {
            break;
        }
        if(move <= 0 || move > b.holes())
        {
            std::cout << "The hole number must be from 1 to " << b.holes() << "." << std::endl;
        }
        else
            std::cout << "There are no beans in that hole." << std::endl;
    }
    return move;
}

HumanPlayer::~HumanPlayer()
{
    
}

//BAD PLAYER
BadPlayer::BadPlayer(std::string name) : Player(name)
{
    
}

int BadPlayer::chooseMove(const Board& b, Side s) const
{
    if(b.beansInPlay(s) == 0)
    {
        return -1;
    }
    
    int move = -1;
    int holes = b.holes();
    
    for(int i = 1; i <= holes; i++)
    {
        //pick the first hole that has more than 0 beans
        if(b.beans(s, i) > 0)
        {
            move = i;
            break;
        }
    }
    std::cout << Player::name() << " chooses hole " << move << std::endl;
    return move;
}

BadPlayer::~BadPlayer()
{
    
}

//SMART PLAYER
SmartPlayer::SmartPlayer(std::string name) : Player(name)
{
    
}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
    AlarmClock ac(4900);
    if(b.beansInPlay(s) == 0)
    {
        return -1;
    }

    int move = 0; // this is the move i will choose
    int moveVbest = -10002; // this is the best value
    int newMove = 0;
    for(int i = 1; i <= b.holes(); i++)
    {
        if(b.beans(s, i) > 0)
        {
//            std::cout << " bean number "  << i << '\n';
            Board tBoard(b); // create a temp board
            bool canSowCap = sowcap(tBoard, i, s);
            bool isMax;
            //sow at that position on a temp board
            //if you can make another turn
            if(canSowCap)
            {
                isMax = true; // tries to maximize again and is same side
                newMove = minmax(tBoard, s, isMax, m_depth, ac);// set your new move to compare with your old best move (moveVbest)
            }
            else //if you cannot make another turn
            {
                isMax = false;
                newMove = minmax(tBoard, s, isMax, m_depth, ac);// set your new move to compare with your old best move (moveVbest)
            }
            if(newMove >= moveVbest)// if your new move is better set move to i
            {
                moveVbest = newMove;
                move = i;
            }
        }
    }
    std::cout << Player::name() << " chooses hole " << move << std::endl;
    return move;
}

int SmartPlayer::eval(const Board& board, Side side) const
{
    if(board.beansInPlay(side) == 0 || board.beansInPlay(opponent(side)) == 0) // if game is over
    {
        if(board.beansInPlay(side) + board.beans(side, 0) >
           board.beansInPlay(opponent(side)) + board.beans(opponent(side), 0))//side has more beans
        {
            return 10000;
        }
        else if (board.beansInPlay(side) + board.beans(side, 0) <
                 board.beansInPlay(opponent(side)) + board.beans(opponent(side), 0))//oppo has more beans
        {
            return -10000;
        }
        else//tie
        {
            return 0;
        }
    }
    
    if(board.beans(side, 0) > board.totalBeans()/2)
    {
        return 10000;
    }
    else if(board.beans(opponent(side), 0) > board.totalBeans()/2)
    {
        return -10000;
    }
    
    //return difference between pots
    return board.beans(side, 0) - board.beans(opponent(side), 0);
}

bool SmartPlayer::sowcap(Board& board, int move, Side side) const
{
    Side endSide;
    int endHole;
    bool didSow = board.sow(side, move, endSide, endHole);
    if(!didSow)
    {
     return false;// if you cannot sow
    }

    //do capture
    if(side == endSide &&
       board.beans(endSide, endHole) == 1 &&
       board.beans(opponent(endSide), endHole) > 0) // do a capturre
    {
        board.moveToPot(side, endHole, side);
        board.moveToPot(opponent(side), endHole, side);
        return false;
    }
    //can it make another turn?
    if(endHole == 0 &&
       endSide == side)
    {
        return true;
    }

    return false; // can't make another turn
}

int SmartPlayer::minmax(const Board& board, Side side, bool isMax ,int depth, AlarmClock& ac) const
{
    int bestHoleVal;
//    if no move for player exists (i.e., game is over),
//    or if the criterion says we should not search below this node
    if(board.beansInPlay(side) == 0 || board.beansInPlay(opponent(side)) == 0 || depth == 0)
    {
        int result = eval(board, side);
        return result;
    }
    if(depth < 0)
    {
        exit(13);
    }
    if(ac.timedOut())
    {
        std::cerr << "time\n";
        return eval(board, side);
    }
    
    if(isMax)
    {
        bestHoleVal = -10001;
        for(int i = 1; i <= board.holes(); i++)// loop through possible moves
        {
            if(ac.timedOut())
            {
                std::cerr << "time\n";
                return eval(board, side);
            }
            if(board.beans(side, i) > 0)
               {
                   Board tBoard(board);
                   bool canSowCapAgain = sowcap(tBoard, i, side);// make move
                   bool oppIsMax;
                   int newMaxHole;
                   if(ac.timedOut())
                   {
                       std::cerr << "time\n";
                       return eval(board, side);
                   }
                   if(canSowCapAgain) // can take another turn
                   {
                       oppIsMax = true;
                       newMaxHole = minmax(tBoard, side, oppIsMax, depth - 1, ac);
                   }
                   else // you cannot take another turn
                   {
                       oppIsMax = false;
                       newMaxHole = minmax(tBoard, opponent(side), oppIsMax, depth - 1, ac);
                   }
                   if(bestHoleVal <= newMaxHole) // if it is a new max val
                   {
                       bestHoleVal = newMaxHole;
                   }
               }
        }
    }
    else // is minimizer
    {
        bestHoleVal = 10001;
        for(int i = 1; i <= board.holes(); i++)// loop through possible moves
        {
            if(ac.timedOut())
            {
                std::cerr << "time\n";
                return eval(board, side);
            }
            if(board.beans(side, i) > 0)
            {
                Board tBoard(board);
                bool canSowCapAgain = sowcap(tBoard, i, side);
                bool oppIsMax;
                int newMinHole;
                if(ac.timedOut())
                {
                    std::cerr << "time\n";
                    return eval(board, side);
                }
                if(canSowCapAgain) // if you can take another turn
                {
                    oppIsMax = false;
                    newMinHole = minmax(tBoard, opponent(side), oppIsMax, depth - 1, ac);
                }
                else // you cannot take another turn
                {
                    oppIsMax = true;
                    newMinHole = minmax(tBoard, opponent(side), oppIsMax, depth - 1, ac);
                }

                if(bestHoleVal >= newMinHole) // if it is a new min value
                {
                    bestHoleVal = newMinHole;
                }
            }
        }
    }
//    std::cout << bestHoleVal << '\n';
    return bestHoleVal;
}

SmartPlayer::~SmartPlayer()
{
    
}

