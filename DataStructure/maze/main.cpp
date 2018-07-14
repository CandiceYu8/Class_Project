#include <iostream>
#include "Queue.h"
#include "maze.h"

using namespace std;

int main()
{
    int row, col;
    Maze mymaze;
    Pos in;
    Pos out;
    cout << "please input the row(<10) of your maze:" << endl;
    cin >> row;
    cout << "please input the column(<10) of your maze:" << endl;
    cin >> col;
    mymaze.InitMatrix(row, col);
    mymaze.InitMaze();
//    mymaze.PrintMatrix();
    cout << "please input the row and column of your start point:" << endl
         << "please input the row and column of your end point:" << endl;
    cin >> in.cur_row >> in.cur_col >> out.cur_row >> out.cur_col;
    if (mymaze.BFS(in, out))
    {
        cout << "The nearest way to the end point:" << endl;
        mymaze.PrintTheNearstWay(in, out);
//        cout << "Detailed:" << endl;
//        mymaze.PrintDetailed();
    }
    else
        cout << "There is no way from start to the end" << endl;
    return 0;
}
