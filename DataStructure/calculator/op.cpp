#include <string>
#include "op.h"

template<class T>
Stack<T>::Stack()
{
    count=0;
}

template<class T>
bool Stack<T>::empty() const
{
    bool outcome=true;
    if(count!=0)
        outcome=false;
    return outcome;
}

template<class T>
Error_code Stack<T>::push(const T &item)
{
    Error_code outcome=success;
    if(count>=MAX)
        outcome=overflow;
    else
        entry[count++]=item;
    return outcome;
}

template <class T>
Error_code Stack<T>::pop()
{
    Error_code outcome=success;
    if(count==0)
        outcome=underflow;
    else
        count--;
    return outcome;
}

template <class T>
Error_code Stack<T>::top(T &item) const
{
    Error_code outcome=success;
    if(count==0)
        outcome=underflow;
    else
        item=entry[count-1];
    return outcome;
}


