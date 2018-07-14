#include "Integer.h"

Integer::Integer()
{
    //do nothing
}

Integer::Integer(int temp)  //initialize vector.
{
    char ch;
    bool flag = true;
    cout << "please enter your number:" << endl;
    do
    {
        ch = cin.get();
        if(ch != '\n')
        {
            number.push_back((ch-'0'));
        }
        else
            flag = false;
    }
    while(flag);
}

int Integer::GetSize()
{
    return number.size();
}

int Integer::GetOne(int position)
{
    return number[position];
}

ostream &operator <<(ostream &out, const Integer &a)
{
    for(unsigned i=0; i<a.number.size(); i++)
        out << a.number[i];
    out << " ";
    return out;
}

//ostream &Integer::operator <<(ostream &out)
//{
//    for(unsigned i=0; i<number.size(); i++)
//        out << number[i];
//    out << " ";
//    return out;
//}


bool Integer::operator ==(const Integer &b)const
{
    bool flag = true;
    if(number.size() == b.number.size())
    {
        for(unsigned i=0; i<number.size(); i++)
        {
            if(number[i] != b.number[i])
            {
                flag = false;
                break;
            }
        }
    }
    else
        flag = false;
    return flag;
}

bool Integer::operator >(const Integer &b)const
{
    bool flag = true;
    if(number.size() == b.number.size())
    {
        for(unsigned i=0; i<number.size(); i++)
        {
            if(number[i] <= b.number[i])
            {
                flag = false;
                break;
            }
        }
    }
    else if(number.size() < b.number.size())
        flag = false;
    return flag;
}

bool Integer::operator <(const Integer &b)const
{
    bool flag = true;
    if(number.size() == b.number.size())
    {
        for(unsigned i=0; i<number.size(); i++)
        {
            if(number[i] >= b.number[i])
            {
                flag = false;
                break;
            }
        }
    }
    else if(number.size() > b.number.size())
        flag = false;
    return flag;
}

Integer& Integer::operator =(const Integer &b)
{
    number.clear();
    for(unsigned i=0; i<b.number.size(); i++)
        number.push_back(b.number[i]);
    return *this;
}


Integer Integer::operator +(Integer &b)
{
    Integer temp;
    int i, j, digit, carry=0;
    for(i=(int)(number.size()-1), j=b.GetSize()-1; i>=0 && j>=0; i--, j--)
    {
        digit = number[i]+b.number[j]+carry;
        if(digit>=10)
        {
            digit -= 10;
            carry = 1;
        }
        else
            carry = 0;
        temp.number.insert(temp.number.begin(), digit);
    }
    while(i>=0)
    {
        digit = number[i]+carry;
        if(digit>=10)
        {
            digit -= 10;
            carry = 1;
        }
        else
            carry = 0;
        temp.number.insert(temp.number.begin(), digit);
        i--;
    }
    while(j>=0)
    {
        digit = b.number[j]+carry;
        if(digit>=10)
        {
            digit -= 10;
            carry = 1;
        }
        else
            carry = 0;
        temp.number.insert(temp.number.begin(), digit);
        j--;
    }
    return temp;
}


Integer & Integer::operator ++()
{
    vector<int>::iterator iter;
    iter = number.end()-1;
    (*iter)++;
    while(*iter >= 10)
    {
        *iter -= *iter;
        if(iter != number.begin())
        {
            iter--;
            (*iter) ++;
        }
    }
    if(iter == number.begin())
        number.insert(iter, 1);
    return *this;
}

Integer Integer::operator ++(int)
{
    Integer old(*this);
    vector<int>::iterator iter;
    iter = number.end()-1;
    (*iter)++;
    while(*iter >= 10)
    {
        *iter -= *iter;
        if(iter != number.begin())
        {
            iter--;
            (*iter) ++;
        }
    }
    if(iter == number.begin())
        number.insert(iter, 1);
    return old;
}
