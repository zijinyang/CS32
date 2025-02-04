#include <queue>
#include <iostream>
using namespace std;

class Coord
{
  public:
    Coord(int r, int c) : m_row(r), m_col(c) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
  private:
    int m_row;
    int m_col;
};


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    queue<Coord> cqueue;
    cqueue.push(Coord(sr,sc));
    maze[sr].at(sc) = 'X';

    while(!cqueue.empty()){
        Coord currentCoord = cqueue.front();
        cqueue.pop();
        if(currentCoord.r() == er && currentCoord.c() == ec)
            return true;

        int directions[4][2] = {
            {-1,0},
            {0,1},
            {1,0},
            {0,-1}
        };

        for(int i = 0; i < 4; i++){
            if(maze[currentCoord.r()+directions[i][0]].at(currentCoord.c()+directions[i][1]) == '.'){
                cqueue.push(Coord(currentCoord.r()+directions[i][0], currentCoord.c()+directions[i][1]));
                maze[currentCoord.r()+directions[i][0]].at(currentCoord.c()+directions[i][1]) = 'X';
            }
        }
    }
    return false;
}

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X........X",
        "XX.X.XXXXX",
        "X..X.X...X",
        "X..X...X.X",
        "XXXX.XXX.X",
        "X.X....XXX",
        "X..XX.XX.X",
        "X...X....X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze, 10,10, 6,4, 1,1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
