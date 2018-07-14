#ifndef LIFE_H_INCLUDED
#define LIFE_H_INCLUDED

const int maxrow = 20, maxcol = 60;

class Life
{
public:
    void initialize();        //initialize configuration
    void print();           //print current configuration
    void print_neighbor();  //print the number of neighbor
    void update();        //one iteration
private:
    int grid[maxrow+2][maxcol+2];       //record if it is live or die
    int neighbor_count(int row, int col);   //calculate its neighbor_count
};


#endif // LIFE_H_INCLUDED
