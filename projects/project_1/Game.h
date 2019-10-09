#ifndef GAME_H
#define GAME_H

//includes
#include "globals.h"
//class declaration
class Arena;
//

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
};

#endif

