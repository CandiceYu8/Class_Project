#include <iostream>
#include "Cir_Link.h"

using namespace std;

Cir_Link::Cir_Link()
{
    int i;
    n = 0;
    NODE *cur = NULL;
    head = new NODE;
    cur = head;
    cout << "please enter n:" << endl;
    cin >> n;
    cout << "please enter m:" << endl;
    cin >> m;
    head->data = 1;
    head->next = NULL;
    for (i=2; i<=n; i++)
    {
        NODE *pt = new NODE;
        if(pt!=NULL)
        {
            pt->data = i;
            pt->next = NULL;
            cur->next = pt;
            cur = pt;
        }
    }
    tail = cur;
    tail->next = head;
}

Cir_Link::~Cir_Link()
{

}


void Cir_Link::Print_Node()
{
    NODE *pt;
    for(pt=head; pt->next!=head; pt=pt->next)
    {
        cout << pt->data << endl;
    }
    cout << pt->data << endl;
}

void Cir_Link::Delete_Node()
{
    int i = n-1;
    int cnt = 1;
    NODE *pt = head;
    while(i)
    {
        if(cnt == m && pt->data!=0)
        {
            cout << "delete:" << pt->data << endl;
            cout << "m:" << m << endl;
            pt->data = 0;
            pt = pt->next;
            cnt = 1;
            i--;
        }
        else
        {
            if (pt->data!=0)
            {
                cnt++;
            }
            pt = pt->next;
        }
    }
}
