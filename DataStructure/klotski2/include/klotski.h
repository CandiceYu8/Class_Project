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
        klotski();                       //initialize start status and end status.
        virtual ~klotski();
        void PrintString(string str);     //print the store[index]->string.
        bool Judge();                    //judge whether this change can be realized.
        void BFS(set<string>&set_name, vector<Node *>&vector_name, int &cur_);
        void BBFS();
        bool Existed(set<string>&set_name, string str);        //judge whether it is already in exist.
        int FindZero(vector<Node *>&vector_name, int index);         //return the index of zero in string.
    private:
        vector<Node *> store_head;     //store status from head.
        vector<Node *> store_back;     //store status from back.
        set<string> exist_head;        //judge whether has been used from head.
        set<string> exist_back;        //judge whether has been used from back.
        int cur_head;                  //current index of head;
        int cur_back;                  //current index of back;
};


#endif // KLOTSKI_H
