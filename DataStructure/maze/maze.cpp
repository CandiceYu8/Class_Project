#include <iostream>
#include <cstring>
#include "maze.h"
#include "Queue.h"

using namespace std;

void Maze::InitMatrix(int row_, int col_)   //Initiate position and noted_matrix.
{
    row = row_;
    col = col_;
    memset(noted, 0, sizeof(noted));
}


void Maze::InitMaze()   //Input your maze.
{
    int i, j;
    cout << "please input your maze(1:walls, 0:roads)." << endl;
    for (i=0; i<row; i++)
    {
        for (j=0; j<col; j++)
        {
            cin >> matrix[i][j];
        }
    }
}


bool Maze::BFS(Pos in, Pos out)   //return whether you can find a way to solve the maze.
{
    int i;
    bool find = false;
    int neighbor;
    Pos neigh[4];
    que.append(in);
    while (!que.empty())
    {
        que.retrieve(position);
        detailed[position.cur_row][position.cur_col]=position;
        noted[position.cur_row][position.cur_col]=1;     //note that position has been added.
        que.serve();
        if (position.cur_row==out.cur_row && position.cur_col==out.cur_col)
        {
            find = true;
            break;
        }
        neighbor = GetNeighbor(position, neigh);
        for (i=0; i<neighbor; i++)
        {
            que.append(neigh[i]);
            detailed[neigh[i].cur_row][neigh[i].cur_col]=neigh[i];
        }
    }
    return find;
}


int Maze::GetNeighbor(Pos cur, Pos neigh[4])  //search whether one point can go to four directions, if can, store it in the array.
{
    int cnt=0;
    int x = cur.cur_row;
    int y = cur.cur_col;
    //down
    if ((x+1)<row && matrix[x+1][y]!=1 && noted[x+1][y]!=1)
    {
        neigh[cnt].cur_row = x+1;
        neigh[cnt].cur_col = y;
        neigh[cnt].pre_row = x;
        neigh[cnt].pre_col = y;
        cnt++;
    }
    //right
    if ((y+1)<col && matrix[x][y+1]!=1 && noted[x][y+1]!=1)
    {
        neigh[cnt].cur_row = x;
        neigh[cnt].cur_col = y+1;
        neigh[cnt].pre_row = x;
        neigh[cnt].pre_col = y;
        cnt++;
    }
    //up
    if ((x-1)>=0 && matrix[x-1][y]!=1 && noted[x-1][y]!=1)
    {
        neigh[cnt].cur_row = x-1;
        neigh[cnt].cur_col = y;
        neigh[cnt].pre_row = x;
        neigh[cnt].pre_col = y;
        cnt++;
    }
    //left
    if ((y-1)>=0 && matrix[x][y-1]!=1 && noted[x][y-1]!=1)
    {
        neigh[cnt].cur_row = x;
        neigh[cnt].cur_col = y-1;
        neigh[cnt].pre_row = x;
        neigh[cnt].pre_col = y;
        cnt++;
    }
    return cnt;
}



void Maze::PrintTheNearstWay(Pos in, Pos out)  //search from back to forth, then store it in the array and print it.
{
    int cnt=0, i;
    Pos cur_pos;
    Pos result[row*col];
    position = out;
    while (position.cur_col!=in.cur_col || position.cur_row!=in.cur_row)  //when not meet in, store in the array.
    {
        result[cnt++] = position;
        cur_pos = position;
        position.cur_row = detailed[cur_pos.cur_row][cur_pos.cur_col].pre_row;
        position.cur_col = detailed[cur_pos.cur_row][cur_pos.cur_col].pre_col;
    }
    result[cnt]=position;
    for (i=cnt; i>=0; i--)   //print the array.
    {
        cout << result[i].cur_row << " " << result[i].cur_col << endl;
    }
}


void Maze::PrintMatrix()  //print the matrix you just put in.
{
    int i, j;
    cout << "Following is the maze you put in." << endl;
    for (i=0; i<row; i++)
    {
        for (j=0; j<col; j++)
        {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
}


void Maze::PrintDetailed()   //print the detailed_matrix.
{
    int i, j;
    for (i=0; i<row; i++)
    {
        for (j=0; j<col; j++)
        {
            cout << i << " " << j << ":"
                 << detailed[i][j].cur_row << " "
                 << detailed[i][j].cur_col << " "
                 << detailed[i][j].pre_row << " "
                 << detailed[i][j].pre_col << " "
                 << endl;
        }
    }
}
