#ifndef HISTORY_H
#define HISTORY_H

//includes
#include "globals.h"

class History
{
private:
    int m_row;
    int m_col;
    int Array [MAXROWS] [MAXCOLS];
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
};

#endif

