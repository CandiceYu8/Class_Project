#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Heap
{
public:
    Heap();
    void Build_heap(void (*visit)(int location));
    void Max_heap(int location);
    void Min_heap(int location);
    void HeapSort(void (*visit)(int location));
    void Print_heap();
private:
    vector<T> heap_array;
    int heap_size;
};


/*----------------realize-----------------*/
template <class T>
Heap<T>::Heap()
{
    heap_size = 0;
}

template <class T>
void Heap<T>::Build_heap(void (*visit)(int location))
{
    cout << "Please input your heap size:" << endl;
    cin >> heap_size;
    cout << "Please enter your number:" << endl;
    T tmp;
    int i;
    for (i=0; i<heap_size; i++)
    {
        cin >> tmp;
        heap_array.push_back(tmp);
    }

    for(i=heap_size/2; i>=0; i--)
    {
        (*visit)(i);
    }
}


template<class T>
void Heap<T>::Max_heap(int location)
{
    int largest;
    int left = 2*location;
    int right = 2*location+1;
    if(right<heap_size && heap_array[left]>heap_array[right])
    {
        largest = left;
    }
    else
    {
        largest = right;
    }
    if(heap_array[largest]>heap_array[location])
    {
        T tmp;
        tmp = heap_array[largest];
        heap_array[largest] = heap_array[location];
        heap_array[location] = tmp;
        Max_heap(largest);
    }
}



template<class T>
void Heap<T>::Min_heap(int location)
{
    int smallest;
    int left = 2*location;
    int right = 2*location+1;
    if(right<heap_size && heap_array[left]<heap_array[right])
    {
        smallest = left;
    }
    else
    {
        smallest = right;
    }
    if(heap_array[smallest]<heap_array[location])
    {
        T tmp;
        tmp = heap_array[smallest];
        heap_array[smallest] = heap_array[location];
        heap_array[location] = tmp;
        Min_heap(smallest);
    }
}


template<class T>
void Heap<T>::HeapSort(void (*visit)(int location))
{
    int i;
    T tmp;
    for(i=heap_size-1; i>0; i--)
    {
        tmp = heap_array[0];
        heap_array[0] = heap_array[i];
        heap_array[i] = tmp;
        heap_size--;
        (*visit)(0);
    }
}

template<class T>
void Heap<T>::Print_heap()
{
    vector<T>::iterator iter;
    for(iter=heap_array.begin(); iter!=heap_array.end(); iter++)
    {
        cout << *iter << " ";
    }
}
#endif // HEAP_H_INCLUDED
