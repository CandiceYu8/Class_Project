#include <iostream>
#include <vector>
#include "Integer.h"
#include "Sort.h"
using namespace std;

int main()
{
    int i;
    int n;
    int digit = 0;
    cout << "please enter the size of your vector:" << endl;
    cin >> n;
    cin.clear();
    cin.sync();
    vector<Integer> a;
    for(i=0; i<n; i++)
    {
        Integer temp(1);
        a.push_back(temp);
    }
    for(i=0; i<n; i++)
    {
        if(digit < a[i].GetSize())
            digit = a[i].GetSize();
    }
    //MSD(a, 0, n-1, digit);
    LSD(a, 0, n-1, 1,  digit);
    for(i=0; i<n; i++)
    {
        cout << a[i];
        //a[i]<<(cout);
    }

    //cout << ++a[0] << endl;
    cout << a[0]++ << endl;
    cout << a[0] << endl;

    //test operator overwrite
    //a:123456789123456789123456789123456789123456789123456789123456789123456789
    //b:24353
//    Integer a(1);
//    Integer b(1);
//    Integer c;
//    c = a+b;
//    cout << "a:" << a << endl;
//    cout << "b:" << b << endl;
//    cout << "c:" << c << endl;
//    if(a>b)
//        cout << "a>b" << endl;
//    else
//        cout << "a<=b" << endl;
    return 0;
}
