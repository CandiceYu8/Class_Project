#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#define MAX 10

enum Error_code{underflow, overflow, success};;
using namespace std;

template <class stack_entry>
class MyStack
{
public:
    MyStack();
    bool empty() const;
    Error_code pop();
    Error_code top(stack_entry &item) const;
    Error_code push(const stack_entry &item);
private:
    int count;
    stack_entry entry[MAX];
};

template <class T>
T a(T A, T B);

#endif // STACK_H_INCLUDED
