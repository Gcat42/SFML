#ifndef PQUEUE_H
#define PQUEUE_H
#include <iostream>
#include <iomanip>
#include "heap.h"
#include "info.h"

using namespace std;

template <typename T>
class PQueue
{
public:
    PQueue();
    bool push(const T& value, int p);
    T pop();
    info<T> Pop_debug();
    bool is_empty() const;
    int size() const;
    void print_tree() const;

    template <typename U>
    friend ostream& operator <<(ostream& outs, const PQueue<U>& print_me);
    bool verify() const;
private:
    Heap<info<T>> _heap;
    int serial_num;
};

template <typename T>
PQueue<T>::PQueue(): serial_num(0){}

template <typename T>
bool PQueue<T>::push(const T& value, int p)
{
    info<T> insertInfo(value, p, serial_num++);
    _heap.insert(insertInfo);
    return true;
}

template <typename T>
T PQueue<T>::pop()
{
    info<T> popped(_heap.remove());
    return popped.item;
}

template <typename T>
info<T> PQueue<T>::Pop_debug()
{
    cout << "POP DEBUG:\n";
    info<T> popped = _heap.remove();
    return popped;
}

template <typename T>
bool PQueue<T>::is_empty() const
{
    return _heap.is_empty();
}

template <typename T>
int PQueue<T>::size() const
{
    return _heap.size();
}

template <typename T>
void PQueue<T>::print_tree() const
{
    _heap.print_tree();
}

template <typename U>
ostream& operator <<(ostream& outs, const PQueue<U>& print_me)
{
    outs<< print_me._heap;
    return outs;
}

template <typename T>
bool PQueue<T>::verify() const
{
    return _heap.verify();
}
#endif