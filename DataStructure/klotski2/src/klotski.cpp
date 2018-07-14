#include "klotski.h"

klotski::klotski()      //initialize start status.
{
    Node *head = new Node;
    if(head != NULL)
    {
        cout << "please enter your start status:" << endl;
        cin >> head->str;
        head->pre = NULL;
        head->steps = 0;
        exist_head.insert(head->str);
        store_head.push_back(head);
    }
    Node *tail = new Node;
    if(head != NULL)
    {
        cout << "please enter your end status:" << endl;
        cin >> tail->str;
        tail->pre = NULL;
        tail->steps = 0;
        exist_back.insert(tail->str);
        store_back.push_back(tail);
    }
    cur_head = 0;
    cur_back = 0;
}

void klotski::PrintString(string str)            //print the store[index]->string.
{
    int i;
    for(i=0; i<9; i++)
    {
        cout << str[i] << " ";
        if((i+1)%3 == 0)
            cout << endl;
    }
}

bool klotski::Existed(set<string>&set_name, string str)           //judge whether it is already in exist.
{
    set<string>::iterator iter;
    iter = set_name.find(str);
    if(iter == set_name.end())
    {
        set_name.insert(str);
        return false;
    }
    else
        return true;
}

int InvertPair(string str)
{
    int i, j, val=0;
    for(i=0; i<8; i++)
    {
        for(j=i; j<9; j++)
        {
            if(str[i]>str[j])
                val++;
        }
    }
    return val;
}

bool klotski::Judge()                   //judge whether this change can be realized.
{
    int invert1 = InvertPair(store_head[0]->str);
    int invert2 = InvertPair(store_back[0]->str);
    if(invert1%2 == invert2%2)
        return false;
    return true;
}

int klotski::FindZero(vector<Node *>&vector_name, int index)            //return the index of zero in string.
{
    int val = -1;
    string temp = vector_name[index]->str;
    for(int i=0; i<9; i++)
    {
        if(temp[i] == '0')
        {
            val = i;
            break;
        }
    }
    return val;
}


void klotski::BFS(set<string>&set_name, vector<Node *>&vector_name, int &cur_)
{
    int zero_index = FindZero(vector_name, cur_);
    int dir[4] = {zero_index-3, zero_index+3, zero_index-1, zero_index+1};   //up, down, left, right
    for(int i=0; i<4; i++)
    {
        if(dir[i]<9 && dir[i]>=0)
        {
            if(zero_index%3==0 && (dir[i]+1)%3==0)
            {
                continue;
            }
            else if(zero_index%3==2 && (dir[i]-1)%3==2)
            {
                continue;
            }
            else
            {
                Node *node = new Node;
                if(node != NULL)
                {
                    node->str = vector_name[cur_]->str;
                    node->str[zero_index] = vector_name[cur_]->str[dir[i]];
                    node->str[dir[i]] = '0';
                    node->pre = vector_name[cur_];
                    node->steps = vector_name[cur_]->steps+1;
                    if(!Existed(set_name, node->str))
                        vector_name.push_back(node);
                }
            }
        }
    }
    cur_++;
}


Node * FindStr(vector<Node *>vector_name, string str)
{
    Node * res = NULL;
    for(int i=(int)vector_name.size()-1; i>=0; i--)
    {
        if(vector_name[i]->str == str)
            res = vector_name[i];
    }
    return res;
}

void klotski::BBFS()
{
    int cnt = 0;
    bool flag = true;
    while(flag)
    {
        set<string>::iterator iter1 = exist_back.find(store_head[cur_head]->str);
        set<string>::iterator iter2 = exist_head.find(store_back[cur_back]->str);
        if(iter1!=exist_back.end())
        {
            Node *_start = store_head[cur_head];
            Node *_end = FindStr(store_back, *iter1);
            vector<Node *> print;
            while(_start != NULL)
            {
                print.push_back(_start);
                _start = _start->pre;
            }
            cout << "following is the path:" << endl;
            for(int i=(int)print.size()-1; i>=0; i--)
            {
                PrintString(print[i]->str);
                cout << endl;
                cnt++;
            }
            _end = _end->pre;
            while(_end != NULL)
            {
                PrintString(_end->str);
                cout << endl;
                _end = _end->pre;
                cnt++;
            }
            cout << "overall steps:" << cnt << endl;
            flag = false;
        }
        else if(iter2!=exist_head.end())
        {
            Node * _end = store_back[cur_back];
            Node * _start = FindStr(store_head, *iter2);
            vector<Node *> print;
            while(_start != NULL)
            {
                print.push_back(_start);
                _start = _start->pre;
            }
            cout << "following is the path:" << endl;
            for(int i=(int)print.size()-1; i>=0; i--)
            {
                PrintString(print[i]->str);
                cout << endl;
                cnt++;
            }
            _end = _end->pre;
            while(_end != NULL)
            {
                PrintString(_end->str);
                cout << endl;
                _end = _end->pre;
                cnt++;
            }
            cout << "overall steps:" << cnt << endl;
            flag = false;
        }
        else
        {
            BFS(exist_head, store_head, cur_head);
            BFS(exist_back, store_back, cur_back);
        }
    }
}

klotski::~klotski()
{
}
