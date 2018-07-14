#include <iostream>
#include <cstring>
#include "Linked_table.h"

using namespace std;
void Swap(STUDENT *a, STUDENT *b);

Link_table::Link_table()  //initiate class private members.
{
    count = 0;
    head = new STUDENT;
}


STUDENT *Link_table::Initiate_table()  //Create a new linked_table.
{
    int n, i;
    cout << "please input the number of your linked_table:" << endl;
    cin >> n;
    STUDENT *pri = head;
    for (i=0; i<n; i++)
    {
        STUDENT *cur = new STUDENT;
        cout << "please enter id, name and score:" << endl;
        cin >> cur->id >> cur->name >> cur->score;
        cur->next = NULL;
        cur->prior = pri;
        pri->next = cur;
        pri = cur;
        count++;
    }
    return head;
}


void Link_table::Print_table()    //print current linked_table.
{
    STUDENT *pt = head->next;
    cout << "print the table:" << endl;
    while (pt!=NULL)
    {
        cout << pt->id << " " << pt->name << " " << pt->score << endl;
        pt = pt->next;
    }
}

void Link_table::Insert(int location)  //insert a student's info by location.
{
    if(location<=count)
    {
        int i;
        STUDENT *in = new STUDENT;
        STUDENT *pt = head->next;
        for (i=1; i<location; i++)
        {
            pt = pt->next;
        }
        cout << "please input the info of the insert student:" << endl;
        cin >> in->id >> in->name >> in->score;
        if (pt->next!=NULL)
            pt->next->prior = in;
        in->next = pt->next;
        pt->next = in;
        in->prior = pt;
        count++;
    }
    else
        cout << "input error!" <<endl;
}


void Link_table::Delete(int delete_id)  //delete a student's info by its id.
{
    bool flag = false;
    STUDENT *pt = head->next;
    while(pt!=NULL)
    {
        if (pt->id == delete_id)
        {
            if (pt->next != NULL)
            {
                pt->prior->next = pt->next;
                pt->next->prior = pt->prior;
            }
            else
            {
                pt->prior->next = NULL;
            }
            delete pt;
            count--;
            flag = true;
            cout << "delete node whose id=" << delete_id << endl;
            break;
        }
        else
        {
            pt = pt->next;
        }
    }
    if (!flag)
        cout << "There is no such a id." << endl;
}


void Link_table::Inverse()   //print linked_table from back to forth.
{
    cout << "inversed table:" << endl;
    STUDENT *pt = head;
    while(pt->next!=NULL)
    {
        pt = pt->next;
    }
    while(pt->prior!=NULL)
    {
        cout << pt->id << " " << pt->name << " " << pt->score << endl;
        pt = pt->prior;
    }
}


int Link_table::ShowCount()   //print the number of the students.
{
    cout << "sum student:" << count << endl;
    return count;
}

void Link_table::Sort()  //sort the table according to students' scores.
{
    int i, j;
    STUDENT *pt1, *pt2;
    pt1 = head->next;
    for (i=1; i<count; i++)
    {
        pt2 = pt1->next;
        for(j=i+1; j<=count; j++)
        {
            if(pt1->score < pt2->score)
            {
                Swap(pt1, pt2);
            }
            pt2 = pt2->next;
        }
        pt1 = pt1->next;
    }
}

void Swap(STUDENT *a, STUDENT *b)
{
    int id;
    char name[10];
    float score;
    id = a->id;
    strcpy(name,a->name);
    score = a->score;
    a->id = b->id;
    b->id = id;
    strcpy(a->name, b->name);
    strcpy(b->name, name);
    a->score = b->score;
    b->score = score;
}

void Link_table::Merge_table(STUDENT *head2)  //merge two sorted table to one table.
{
    STUDENT *pt1, *pt2, *cur;
    pt1 = head->next;
    pt2 = head2->next;
    cur = head;
    while(pt1!=NULL && pt2!=NULL)
    {
        if(pt1->score >= pt2->score)
        {
            cur->next = pt1;
            pt1->prior = cur;
            pt1 = pt1->next;
        }
        else
        {
            cur->next = pt2;
            pt2->prior = cur;
            pt2 = pt2->next;
        }
        cur = cur->next;
    }
    while(pt1!=NULL)
    {
        cur->next = pt1;
        pt1->prior = cur;
        pt1 = pt1->next;
        cur = cur->next;
    }
    while(pt2!=NULL)
    {
        cur->next = pt2;
        pt2->prior = cur;
        pt2 = pt2->next;
        cur = cur->next;
    }
}


void Link_table::ClearTable()   //free memory.
{
    STUDENT *cur, *pt = head->next;
    while(pt!=NULL)
    {
        cur = pt->next;
        delete pt;
        pt = cur;
    }
}


Link_table::~Link_table()   //free head pointer.
{
    delete head;
    head = NULL;
}
