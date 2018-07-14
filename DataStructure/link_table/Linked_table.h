#ifndef LINKED_TABLE_H_INCLUDED
#define LINKED_TABLE_H_INCLUDED
#include <string>

using namespace std;

typedef struct Student
{
    int id;
    char name[10];
    float score;
    struct Student *prior;
    struct Student *next;
    Student()
    {
        prior = NULL;
        next = NULL;
    }
} STUDENT;


class Link_table
{
public:
    Link_table();            //initiate class private members.
    STUDENT *Initiate_table();   //Create a new linked_table.
    void Insert(int location);   //insert a student's info by location.
    void Delete(int delete_id);  //delete a student's info by its id.
    void Inverse();          //print linked_table from back to forth.
    void Sort();            //sort the table according to students' scores.
    void Merge_table(STUDENT *head2);     //merge two sorted table to one table.
    void Print_table();     //print current linked_table.
    int ShowCount();       //print the number of the students.
    void ClearTable();      //free space.
    ~Link_table();         //destruct. free head pointer.
private:
    STUDENT *head;          //the head of the table, not including student's info.
    int count;              //the number of the students.
};

#endif // LINKED_TABLE_H_INCLUDED
