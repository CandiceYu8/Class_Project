#include <iostream>
#include "puzzle.h"
#include <string>
#include <set>
#include <time.h>

using namespace std;

int main()
{
//    123470685
    clock_t start,finish;
   double totaltime;
   start=clock();
    matrix m1;
    finish=clock();
   totaltime=(double)(finish-start)/CLOCKS_PER_SEC;
   cout<<"\n�˳��������ʱ��Ϊ"<<totaltime<<"�룡"<<endl;
    return 0;
}
