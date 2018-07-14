#include <iostream>
#include<stdlib.h>
#include "life.h"
#include "life.cpp"
using namespace std;


int main()
{
    char ch;
    Life life1;
    life1.initialize();
    cout << "print:" << endl;
    life1.print();
    cout << "next:y/n" << endl;
    cin >> ch;
    while(ch=='y'||'Y')   //if 'y' or 'Y', enter next iteration
    {
        cout << "neighbor_count:" <<endl;
        life1.print_neighbor();            //print neighbor_count

        life1.update();                  //update
        cout << "print:" << endl;
        life1.print();                    //print life statement after one iteration

        cout << "next:y/n" << endl;        //ask whether need next iteration
        cin >> ch;
        if(ch!='y' && ch!='Y')
            exit(0);
    }
    return 0;
}
