#ifndef OP_H_INCLUDED
#define OP_H_INCLUDED
#define MAX 100

enum Error_code{overflow, underflow, success};

template <class T>   //both operator and operand
class Stack
{
public:
    Stack();
    bool empty() const;
    Error_code push(const T &item);
    Error_code pop();
    Error_code top(T &item) const;
private:
    int count;
    T entry[MAX];
};

#endif // OP_H_INCLUDED
