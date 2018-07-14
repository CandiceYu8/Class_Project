#ifndef KLOTSKI_H
#define KLOTSKI_H
#include <iostream>
#include <set>
#include <vector>
#include <cstring>
using namespace std;

typedef struct node
{
    string str;
    struct node *pre;
    int steps;
}Node;

class klotski
{
    public:
        klotski();                       //initialize start status.
        virtual ~klotski();
        void PrintString(string str);     //print the store[index]->string.
        bool Judge();                    //judge whether this change can be realized.
        void BFS();
        bool Existed(string str);        //judge whether it is already in exist.
        int FindZero(int index);         //return the index of zero in string.
    //private:
        vector<Node *> store;     //store status.
        set<string> exist;        //judge whether has been used.
        string end_;              //end string.
        int cur;                  //current index;
};


#endif // KLOTSKI_H
