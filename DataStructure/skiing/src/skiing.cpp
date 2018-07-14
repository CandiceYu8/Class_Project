#include <iostream>
#include "skiing.h"
using namespace std;

skiing::skiing()
{
    cout << "please input the row and column of your matrix:" << endl;
    cin >> row >> col;
    cout << "please enter the height of your matrix" << endl;
    int i, j;
    for (i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            cin >> height[i][j];
            length[i][j] = 0;
        }
    }
}


void skiing::SearchMaxLength()
{
    int i, j;
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            length[i][j] = MaxLength(i, j);
        }
    }
}



int skiing::MaxLength(int x, int y)  //x,y:location.
{
    int i;
    int new_x, new_y;
    int cur_height, new_len, new_height;
    int result = 0, temp_len = 0;
    int dir[4][2]={1,0,-1,0,0,1,0,-1};
    for (i=0; i<4; i++)
    {
        new_x = x+dir[i][0];
        new_y = y+dir[i][1];
        if(new_x>=0 && new_y>=0 && new_x<row && new_y<col)
        {
            cur_height = height[x][y];
            new_height = height[new_x][new_y];
            new_len = length[new_x][new_y];
            if(cur_height > new_height)
            {
                if(new_len != 0)
                {
                    temp_len = new_len + cur_height - new_height;
                }
                else
                {
                    temp_len = MaxLength(new_x, new_y) + cur_height - new_height;
                }
            }
        }
        if(temp_len > result)   //choose the longest of the four direction.
        {
            result = temp_len;
        }
    }
    return result;
}


int skiing::ReturnMaxLength()
{
    int i, j;
    int result = 0;
    for(i=0; i<row; i++)
    {
        for(j=0; j<col; j++)
        {
            if(length[i][j] > result)
            {
                result = length[i][j];
            }
        }
    }
    return result;
}

void skiing::PrintLength()
{
    cout << "The length from the point:" << endl;
    int i, j;
    for (i=0; i<row; i++)
    {
        for (j=0; j<col; j++)
        {
            cout << length[i][j] << " ";
        }
        cout << endl;
    }
}

skiing::~skiing()
{
    cout << "destroy matrix" << endl;
}
