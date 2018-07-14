#include "Queue.h"

template <class Queue_entry>
CirQueue<Queue_entry>::CirQueue()     //new CirQueue.
{
    count = 0;
    front = 0;
    rear = MAX_QUEUE_SIZE-1;
}

template <class Queue_entry>
bool CirQueue<Queue_entry>::empty() const     //if queue is empty, return true. Otherwise return false.
{
    return count==0;
}

template <class Queue_entry>
bool CirQueue<Queue_entry>::full() const      //if queue is full, return true. Otherwise return false.
{
    return count==MAX_QUEUE_SIZE;
}

template <class Queue_entry>
Error_code CirQueue<Queue_entry>::append(const Queue_entry &item)   //append new item in the rear of the queue.
{
    if(count >= MAX_QUEUE_SIZE)
        return overflow;
    else
    {
        count++;
        rear = ( (rear+1) == MAX_QUEUE_SIZE)?0:(rear+1);
        entry[rear] = item;
        return success;
    }
}

template <class Queue_entry>
Error_code CirQueue<Queue_entry>::retrieve(Queue_entry &item) const   //similar to top in stack. Get the first item in a queue.
{
    if (count <= 0)
        return underflow;
    else
    {
        item = entry[front];
        return success;
    }
}

template <class Queue_entry>
Error_code CirQueue<Queue_entry>::serve()     //similar to pop in stack. Remove the first item in a queue.
{
    if(count <= 0)
        return underflow;
    else
    {
        count--;
        front = ((front+1)== MAX_QUEUE_SIZE)?0:(front+1);
        return success;
    }
}

template <class Queue_entry>
Error_code CirQueue<Queue_entry>::retrieve_and_serve(Queue_entry &item)  //While get the first item in the queue, remove it.
{
    if (count <= 0)
        return underflow;
    else
    {
        item = entry[front];
        count--;
        front = ((front+1) == MAX_QUEUE_SIZE)?0:(front+1);
        return success;
    }
}

template <class Queue_entry>
int CirQueue<Queue_entry>::size() const      //return count
{
    return count;
}

template <class Queue_entry>
void CirQueue<Queue_entry>::clear()          //clear the queue
{
    count = 0;
    front = 0;
    rear = MAX_QUEUE_SIZE-1;
}

