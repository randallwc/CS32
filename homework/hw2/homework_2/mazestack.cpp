//Homework 2
//May 1, 2019
//William Randall
//805167986

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
//void dump(char map[10][10]);

#include <iostream>
int main()
{
    char maze[10][10] = 
    {
//        { 'X','X','X','X','X','X','X','X','X','X' },
//        { 'X','.','.','.','.','X','.','.','.','X' },
//        { 'X','.','X','X','.','X','X','X','.','X' },
//        { 'X','X','X','.','.','.','.','X','.','X' },
//        { 'X','.','X','X','X','.','X','X','X','X' },
//        { 'X','.','X','.','.','.','X','.','.','X' },
//        { 'X','.','.','.','X','.','X','.','.','X' },
//        { 'X','X','X','X','X','.','X','.','X','X' },
//        { 'X','.','.','.','.','.','.','.','.','X' },
//        { 'X','X','X','X','X','X','X','X','X','X' }
        
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };
    
    if (pathExists(maze, 3,5, 8,8))
        std::cout << "Solvable!" << std::endl;
    else
        std::cout << "Out of luck!" << std::endl;
}

#include <stack>
bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    std::stack<Coord> coordStack;
    Coord a(sr,sc);
    coordStack.push(a);
    maze[sr][sc] = '#';
    
    while(!coordStack.empty())
    {
        Coord b = coordStack.top();
        Coord south (b.r() + 1 , b.c()     );
        Coord north (b.r() - 1 , b.c()     );
        Coord east  (b.r()     , b.c() + 1 );
        Coord west  (b.r()     , b.c() - 1 );
        
        coordStack.pop();
        
        if(b.r() == er && b.c() == ec)
            return true;
        
        if(maze[south.r()][south.c()] == '.')
        {
            coordStack.push(south);
            maze[south.r()][south.c()] = '#';
        }
        
        if(maze[west.r()][west.c()] == '.')
        {
            coordStack.push(west);
            maze[west.r()][west.c()] = '#';
        }
        
        if(maze[north.r()][north.c()] == '.')
        {
            coordStack.push(north);
            maze[north.r()][north.c()] = '#';
        }
        if(maze[east.r()][east.c()] == '.')
        {
            coordStack.push(east);
            maze[east.r()][east.c()] = '#';
        }
//        dump(maze);
    }
    return false;
}

//#include <unistd.h>
//void dump(char map[10][10])
//{
//    for(int i = 0; i < 3; i++)
//        std::cerr<<std::endl;
//    usleep(1000*100);
//
//    for(int r = 0; r < 10 ; r++)
//    {
//        for(int c = 0; c < 10; c++)
//            std::cerr << map[r][c] << " ";
//        std::cerr << std::endl;
//    }
//}
