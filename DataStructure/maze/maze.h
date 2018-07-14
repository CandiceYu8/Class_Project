#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED
#include "Queue.h"
#include "Queue.cpp"
#define MAX_MAZE_SIZE 10

typedef struct Poistion
{
    int cur_row;  //current row
    int cur_col;  //current column
    int pre_row;  //previous row
    int pre_col;  //previous column
} Pos;


class Maze
{
private:
    int row, col;   //the row and col of your input maze.
    Pos position;   // a temp position ready to put in queue.
    Pos detailed[MAX_MAZE_SIZE][MAX_MAZE_SIZE];  //the passerby point's detailed info :current(x,y) and previous(x,y)
    int matrix[MAX_MAZE_SIZE][MAX_MAZE_SIZE];   //store the maze you put in.
    int noted[MAX_MAZE_SIZE][MAX_MAZE_SIZE];   //if a position has been added, mark it as 1.
    CirQueue<Pos> que;

public:
    void InitMatrix(int row_, int col_);   //Initiate position and noted_matrix.
    void InitMaze();   //Input your maze.
    int GetNeighbor(Pos cur, Pos neigh[4]);  //search whether one point can go to four directions, if can, store it in the array.
    bool BFS(Pos in, Pos out);   //return whether you can find a way to solve the maze.
    void PrintTheNearstWay(Pos in, Pos out);  //search from back to forth, then store it in the array and print it.
    void PrintMatrix();  //print the matrix you just put in.
    void PrintDetailed();   //print the detailed_matrix.
};

#endif // MAZE_H_INCLUDED
