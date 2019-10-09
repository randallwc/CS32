#include <string>
#include "Board.h"
#include "Side.h"

#ifndef Player_h
#define Player_h

//==========================================================================
// AlarmClock ac(numMilliseconds);  // Set an alarm clock that will time out
//                                  // after the indicated number of ms
// if (ac.timedOut())  // Will be false until the alarm clock times out; after
//                     // that, always returns true.
//==========================================================================

#include <chrono>
#include <future>
#include <atomic>

class AlarmClock
{
public:
    AlarmClock(int ms)
    {
        m_timedOut = false;
        m_isRunning = true;
        m_alarmClockFuture = std::async([=]() {
            for (int k = 0; k < ms  &&  m_isRunning; k++)
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (m_isRunning)
                m_timedOut = true;
        });
    }
    
    ~AlarmClock()
    {
        m_isRunning = false;
        m_alarmClockFuture.get();
    }
    
    bool timedOut() const
    {
        return m_timedOut;
    }
    
    AlarmClock(const AlarmClock&) = delete;
    AlarmClock& operator=(const AlarmClock&) = delete;
private:
    std::atomic<bool> m_isRunning;
    std::atomic<bool> m_timedOut;
    std::future<void> m_alarmClockFuture;
};

class Player
{
private:
    std::string m_name;
public:
    Player(std::string name);
    //    Create a Player with the indicated name.
    std::string name() const;
    //    Return the name of the player.
    virtual bool isInteractive() const;
    //    Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
    virtual int chooseMove(const Board& b, Side s) const = 0;
    //    Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
    virtual ~Player();
    //    Since this class is designed as a base class, it should have a virtual destructor.
};

//A HumanPlayer chooses its move by prompting a person running the program for a move (reprompting if necessary until the person enters a valid hole number), and returning that choice. We will never test for a situation where the user doesn't enter an integer when prompted for a hole number. (The techniques for dealing with the issue completely correctly are a distraction to this project, and involve either a function like stoi or strtol, or the type istringstream.)
class HumanPlayer : public Player
{
private:
public:
    HumanPlayer(std::string name);
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~HumanPlayer();
};

//A BadPlayer is a computer player that chooses an arbitrary valid move and returns that choice. "Arbitrary" can be what you like: leftmost, nearest to pot, fewest beans, random, etc.. The point of this class is to have an easy-to-implement class that at least plays legally.
class BadPlayer : public Player
{
private:
public:
    BadPlayer(std::string name);
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~BadPlayer();
};

//Here's your chance to shine. A SmartPlayer chooses a valid move and returns it. For any game played on a board of up to six holes per side, with up to four initial beans per hole, SmartPlayer::chooseMove must return its choice in no more than five seconds. (We'll give you a way of determining the time soon; until then, you can meet this requirement by limiting the depth of your game tree search or the number of game tree positions you explore to a limit you determine experimentally.) SmartPlayer::chooseMove will be worth about 15-20% of the points for this project.
class SmartPlayer : public Player
{
private:
    int eval(const Board& board, Side side) const;
    // always evaluate w.r.t. to max player
    bool sowcap(Board& board, int move, Side side) const;
    //return true if make another move
    int minmax(const Board& board, Side side, bool isMax ,int depth, AlarmClock& ac) const ;
    // return value for a certain move
    int m_depth = 8;
public:
    SmartPlayer(std::string name);
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~SmartPlayer();
};

#endif /* Player_h */
