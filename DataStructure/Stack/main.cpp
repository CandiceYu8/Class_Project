#include <iostream>
//#include "stack.h"
#include "stack.cpp"

using namespace std;

int main()
{
    int n, i;
    double item;
    MyStack<double> numbers;
    cout << "There is an integer n followed by n decimal numbers." << endl;
    cout << "The numbers will be printed in reverse order." << endl;
    cin >> n;
    for(i=0; i<n; i++)
    {
        cin >> item;
        numbers.push(item);
    }
    while (!numbers.empty())
    {
        numbers.top(item);
        cout << item << " ";
        numbers.pop();
    }
    cout << endl;


    //"change number from 10 to 8"
//    int n, r, item;
//    MyStack<int> numbers;
//    cout << "enter the number you want to change" << endl;
//    cin >> n;
//    cout << "enter the change unit" << endl;
//    cin >> r;
//    while(n)
//    {
//        numbers.push(n%r);
//        n=n/r;
//    }
//    while(!numbers.empty())
//    {
//        numbers.top(item);
//        cout << item << "";
//        numbers.pop();
//    }
//    cout << endl;
    return 0;
}
