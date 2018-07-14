#include <iostream>
#include "Linked_table.h"

using namespace std;

int main()
{
    int id;
    int location;
    Link_table table1;
    Link_table table2;
    STUDENT *head2;
    table1.Initiate_table();  //create table1
    cout << "please input the location after where you want to insert a student's info:" <<endl;
    cin >> location;
    table1.Insert(location);                 //1.insert student's info by location.
    table1.Print_table();             //show table after insertion.
    cout << "please input the student's id which you want to delete:n<=" << endl;
    cin >> id;
    table1.Delete(id);                 //2.delete a student's info according to its id.
    table1.Print_table();             //show table after deletion.
    table1.Inverse();                 //3.inverse table1
    table1.Sort();                    //4.Sort table1 by students' score.
    cout << "table1 after sort:" << endl;
    table1.Print_table();             //show table1 after sort.
    head2 = table2.Initiate_table();  //create table2
    table2.Sort();                    //4.Sort table2 by students' score.
    cout << "table2 after sort:" << endl;
    table2.Print_table();             //show table2 after sort.
    table1.Merge_table(head2);        //5.merge table1 and table2.
    table1.Print_table();             //show table1 after merge.
    table1.ClearTable();              //free memory. Because table2 has already linked to table1, so there is no need to free table2 any more.
    return 0;
}
