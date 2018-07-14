#include <iostream>
#include <vector>

using namespace std;

int cnt = 0;
vector<int> array;
vector<int> note;
int Permutation(int cur, int num);
int main()
{
    int n;  //the size of array.
    int i;
    cout << "please enter the number of your permutation" << endl;
    cin >> n;
    for (i=0; i<n; i++)
    {
        note.push_back(0);
        array.push_back(i);
    }
    i = Permutation(0, n);
    cout << i << endl;
    return 0;
}

int Permutation(int cur, int num)  //cur: the current i_th of the vector.  num: the size of the vector.
{
    int i;
    if (cur == num)
    {
        for(i=0; i<num; i++)
        {
            cout << array[i] << " ";
        }
        cnt++;
        cout << endl;
    }
    else
    {
        for(i=0; i<num; i++)
        {
            if(!note[i])
            {
                note[i] = 1;
                array[cur] = i;
                Permutation(cur+1, num);
                note[i] = 0;
            }
        }
    }
    return cnt;
}
