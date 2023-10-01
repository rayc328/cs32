#include <iostream>
#include <stack>
using namespace std; 

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {} //constructor 
    int r() const { return m_r; } //getter
    int c() const { return m_c; } //getter 
private:
    int m_r;
    int m_c;
};

const char encountered = '~'; //indicate algorithim has encountered starting coordinate 


int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','.','.','X','.','.','.','.','X' },
        { 'X','.','.','X','X','.','X','X','.','X' },
        { 'X','.','X','.','.','.','.','X','X','X' },
        { 'X','X','X','X','.','X','X','X','.','X' },
        { 'X','.','.','X','.','.','.','X','.','X' },
        { 'X','.','.','X','.','X','.','.','.','X' },
        { 'X','X','.','X','.','X','X','X','X','X' },
        { 'X','.','.','.','.','.','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 3, 4, 8, 1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    stack<Coord> coordStack; //declare stack of coords 
    Coord startCoord(sr, sc); //create coord object that holds starting coordinates 
    coordStack.push(startCoord);
    maze[startCoord.r()][startCoord.c()] = encountered;

    while (!coordStack.empty())
    { 
       Coord top = coordStack.top(); //coordinate at the top of the stack 
       coordStack.pop();

        if (top.r() == er && top.c() == ec) //checking if current coords match ending coords
        {
            return true; 
        }

        if (maze[top.r() + 1][top.c()] == '.') //moving south would be increasing r 
        {
            Coord moveSouth(top.r() + 1, top.c()); 
            coordStack.push(moveSouth);
            maze[top.r() + 1][top.c()] = encountered; 
        }

        if (maze[top.r()][top.c() + 1] == '.') //moving east would be increasing c
        {
            Coord moveEast(top.r(), top.c()+1);
            coordStack.push(moveEast);
            maze[top.r()][top.c()+1] = encountered;
        }

        if (maze[top.r() - 1][top.c()] == '.') //moving north would be decreasing r
        {
            Coord moveNorth(top.r() - 1, top.c());
            coordStack.push(moveNorth);
            maze[top.r() - 1][top.c()] = encountered;
        }

        if (maze[top.r()][top.c() - 1] == '.') //moving west would be decreasing c
        {
            Coord moveWest(top.r(), top.c()-1);
            coordStack.push(moveWest);
            maze[top.r()][top.c() - 1] = encountered;
        }
    }
    return false; 
}


// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise