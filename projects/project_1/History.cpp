#include <iostream>
using namespace std;

#include "History.h"

History::History(int nRows,int nCols)
{
    m_row = nRows;
    m_col = nCols;
    
    for (int i = 0; i < m_row; i++)
    {
        for (int k = 0; k < m_col; k++)
        {
            Array [i][k] = 0;
        }
    }
}

bool History::record(int r, int c)
{
    if (r > m_row || r <= 0)
    {
        return false;
    }
    else if (c > m_col || c <= 0)
    {
        return false;
    }

    Array[r-1][c-1] += 1;
    return true;
}

void History::display() const
{
    char hisArr [MAXROWS] [MAXCOLS];
    
    for(int i = 0; i < m_row; i++)
    {
        for(int k = 0; k < m_col; k++)
        {
            if (Array[i][k]==0)
            {
                hisArr[i][k] = '.';
            }
            else if (Array[i][k] > 0 && Array[i][k] < 26)
            {
                hisArr[i][k] = 'A' + Array[i][k] - 1;
            }
            else if (Array[i][k] >= 26)
            {
                hisArr[i][k] = 'Z';
            }
        }
    }
    
    clearScreen();
    
    for (int i = 0; i < m_row; i++)
    {
        for (int k = 0; k < m_col; k++)
        {
            cout << hisArr[i][k];
        }
        cout << endl;
    }
    
    cout << endl;
    
}
