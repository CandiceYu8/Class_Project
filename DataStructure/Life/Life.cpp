#include <iostream>
#include<stdlib.h>
#include "life.h"

int in_row=0, in_col=0;  //the input row and column
using namespace std;

void Life::initialize()    //initialize configuration
{
    int cnt, i, j, x, y;
    for(i=0; i<maxrow; i++)
    {
        for(j=0; j<maxcol; j++)
        {
            Life::grid[i][j]=0;
        }
    }
    cout << "enter the row of your array:(row<=20)" <<endl;
    cin >> in_row;
    cout << "enter the column of your array:(col<=60)" <<endl;
    cin >> in_col;
    cout << "enter the total number of life:" << endl;
    cin >> cnt;
    cout << "enter the (x,y) of life:" << endl;
    for (i=0; i<cnt; i++)
    {
        cin >> x;
        cin >> y;
        Life::grid[x][y]=1;
    }
}

void Life::print()         //print current configuration
{
    int i, j;
    for(i=0; i<in_row; i++)
    {
        for(j=0; j<in_col; j++)
        {
            cout << Life::grid[i][j] << " ";
        }
        cout << endl;
    }
}


int Life::neighbor_count(int row, int col)    //calculate its neighbor_count
{
    int ncount=0;
    int i, j;
    for (i=((row-1)>=0?(row-1):row); i<=((row+1)<in_row?(row+1):row); i++)
    {
        for (j=((col-1)>=0?(col-1):col); j<=((col+1)<in_col?(col+1):col); j++)
        {
            if(Life::grid[i][j]==1)
            {
                ncount++;
            }
        }
    }
    ncount-=Life::grid[row][col];
    return ncount;
}


void Life::print_neighbor()    //print the number of neighbor
{
    int i, j;
    for(i=0; i<in_row; i++)
    {
        for(j=0; j<in_col; j++)
        {
            cout << Life::neighbor_count(i,j) << " ";
        }
        cout << endl;
    }
}


void Life::update()       //one iteration
{
    int i, j;
    int sum, self;
    int backup_array[in_row][in_col];   //backup pre_neighbor_count
    for(i=0; i<in_row; i++)
    {
        for(j=0; j<in_col; j++)
        {
            backup_array[i][j]=Life::neighbor_count(i,j);
        }
    }
    for(i=0; i<in_row; i++)
    {
        for(j=0; j<in_col; j++)
        {
            sum=backup_array[i][j];     //pre_neighbor_count
            self=Life::grid[i][j];         //1:life 0:die
            if(sum>=4 || sum<=1)
                Life::grid[i][j]=0;
            if(sum==3)
                Life::grid[i][j]=1;
            if (sum==2 && self==0)
                Life::grid[i][j]=0;
        }
    }
}
