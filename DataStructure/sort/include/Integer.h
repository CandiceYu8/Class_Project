#ifndef INTEGER_H
#define INTEGER_H
#include <iostream>
#include <vector>
using namespace std;

class Integer
{
    public:
        Integer();
        Integer(int temp);      //initialize vector.
        int GetSize();          //number.size()
        int GetOne(int position);       //return number[position]
        //comparison operators
        bool operator ==(const Integer &b)const;
        bool operator >(const Integer &b)const;
        bool operator <(const Integer &b)const;
        //assignment operator
        Integer &operator =(const Integer &b);
        //arithmetic operators
        Integer operator +(Integer &b);
        //out stream operator
        friend ostream &operator <<(ostream &out, const Integer &a);
        //ostream &operator <<(ostream &out);
        //single operator
        Integer &operator ++();
        Integer operator ++(int);
    //private:
        vector<int> number;
};

#endif // INTEGER_H
