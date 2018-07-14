#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include "List.h"
#define MAX_QUEUE_SIZE  10


template <class Queue_entry>
class CirQueue
{
public:
    CirQueue();                  //new CirQueue.
    bool empty() const;         //if queue is empty, return true. Otherwise return false.
    bool full() const;          //if queue is full, return true. Otherwise return false.
    Error_code append(const Queue_entry &item);     //append new item in the rear of the queue.
    Error_code serve();            //similar to pop in stack. Remove the first item in a queue.
    Error_code retrieve(Queue_entry &item) const;       //similar to top in stack. Get the first item in a queue.
    Error_code retrieve_and_serve(Queue_entry &item);   //While get the first item in the queue, remove it.
    int size() const;           //return count
    void clear();              //clear the queue
private:
    int count;      //the number of the member in a queue.
    int front, rear;
    Queue_entry entry[MAX_QUEUE_SIZE];
};


#endif // QUEUE_H_INCLUDED
