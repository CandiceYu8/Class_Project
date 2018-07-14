#include <iostream>
#include <cstring>
#include <set>
#include <vector>
#include "klotski.h"

using namespace std;

int main()
{
    //start:264137058
    //end:  815736402
    klotski test;
    if(test.Judge())
        test.BFS();
    else
        cout << "it cannot be changed into end status." << endl;
    return 0;
}


