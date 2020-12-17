//For this part of the homework, you will turn in one file named maze.cpp that contains the Coord class (if you use it) and the pathExists function and nothing more.

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

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    Coord start     (sr     ,sc     );
    Coord end       (er     ,ec     );
    
    Coord up        (sr-1   ,sc     );
    Coord down      (sr+1   ,sc     );
    Coord left      (sr     ,sc-1   );
    Coord right     (sr     ,sc+1   );
    
    if (start.r() == end.r() && start.c() == end.c())
        return true;
    
    maze [start.r()] [start.c()] = '#';
    
    if(maze[up.r()][up.c()] == '.' &&
       pathExists(maze, up.r(), up.c(), end.r(), end.c()) )//up
            return true;
    
    if(maze[down.r()][down.c()] == '.' &&
       pathExists(maze, down.r(), down.c(), end.r(), end.c()) )//down
            return true;
    
    if(maze[left.r()][left.c()] == '.' &&
       pathExists(maze, left.r(), left.c(), end.r(), end.c()) )//left
            return true;
   
    if( maze[right.r()][right.c()] == '.' &&
       pathExists(maze, right.r(), right.c(), end.r(), end.c()) )//right
        return true;
    
    return false;
}
