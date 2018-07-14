#include <iostream>
#include "stack.h"

using namespace std;

template <class T>
T a(T A, T B)
{
    return A+B;
}

template <class stack_entry>
MyStack<stack_entry>::MyStack()
{
    count=0;
}

template <class stack_entry>
bool MyStack<stack_entry>::empty() const
{
    bool outcome=true;
    if(count>0)
        outcome=false;
    return outcome;
}


template <class stack_entry>
Error_code MyStack<stack_entry>::push(const stack_entry &item)
{
    a(10,1);
    Error_code outcome=success;
    if(count>=MAX)
        outcome=overflow;
    else
        entry[count++]=item;
    return outcome;
}

template <class stack_entry>
Error_code MyStack<stack_entry>::pop()
{
    Error_code outcome=success;
    if(count==0)
        outcome=underflow;
    else
        count--;
    return outcome;
}


template <class stack_entry>
Error_code MyStack<stack_entry>::top(stack_entry &item) const
{
    Error_code outcome=success;
    if(count==0)
        outcome=underflow;
    else
        item=entry[count-1];
    return outcome;
}
