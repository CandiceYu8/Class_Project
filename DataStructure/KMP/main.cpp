#include <iostream>
#include <string>
using namespace std;
void GetNext1(string p, int next[]);
int IndexKMP(string t, string p, int next[]);
int main()
{
    string test = "abcac";
    string compare = "ababcabcacbab";
    int len = test.size();
    int next[len];
    GetNext1(test, next);
    for (int i=0; i<len; i++)
        cout << next[i] << " ";
    cout << endl;
    cout << IndexKMP(compare, test, next) << endl;
    return 0;
}

void GetNext1(string p, int next[])
{
    int j = 0;
    int k = -1;
    next[0] = -1;
    while(j<(int)p.size()-1)
    {
        if(k==-1 || p[j]==p[k])
        {
            j++;
            k++;
            next[j] = k;  //the same as next[j+1] = k+1
        }
        else
        {
            k = next[k];
        }
    }
}

int IndexKMP(string t, string p, int next[])
{
    int i = 0;
    int j = 0;
    while(i<t.size() && j<p.size())
    {
        if(t[i] == p[j] || j==-1)
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if(j>=p.size())
        return i-p.size();
    else
        return 0;
}
