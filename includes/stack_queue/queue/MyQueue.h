#ifndef MYQUEUE_H
#define MYQUEUE_H
#include <iostream>
#include <assert.h>
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"
#include "../node/node.h"

using namespace std;
template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;                               //give access to list to access _ptr
        Iterator(): _ptr(nullptr){}                         //default ctor
        Iterator(node<T>* p)
        {
            _ptr = p;
        }                            //Point Iterator to where p is pointing to

        T operator *()
        {
            assert(_ptr != nullptr);
            return _ptr->_item;
        }    //dereference operator
        bool is_null()
        {
            return _ptr == nullptr;
        }            //true if _ptr is NULL
        friend bool operator !=(const Iterator& left, const Iterator& right)  //true if left != right
        {
            return left._ptr != right._ptr;
        }

        friend bool operator ==(const Iterator& left, const Iterator& right)  //true if left == right
        {
            return left._ptr == right._ptr;
        }


        Iterator& operator++()
        {
            assert(_ptr != nullptr);                       
            _ptr = _ptr->_next;
            return *this;
        }  //member operator:++it or ++it = new_value

        friend Iterator operator++(Iterator& it, int unused)
        {         
            assert(it._ptr != nullptr);
            Iterator holder(it._ptr);
            ++it;
            return holder;
        }//friend operator: it++

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    Queue();

    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue& operator=(const Queue<T>& RHS);

    bool empty() const;
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const;                                     //Iterator to the head node
    Iterator end() const;                                       //Iterator to NULL
    void print_pointers();
    void print_backwards();
    int size() const { return _size; }
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe);
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};

template <typename T>
Queue<T>::Queue(): _front(nullptr), _rear(nullptr), _size(0){}

///BIG THREE
template <typename T>
Queue<T>::Queue(const Queue<T>& copyMe): _front(nullptr), _size(0)
{
    _rear = _copy_list(_front, copyMe._front);//this function returns the last node
    _size = copyMe._size;
}
template <typename T>
Queue<T>::~Queue()
{
    _clear_list(_front);
}
template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS)
{
    _clear_list(_front);
    _front = _copy_list(RHS._front);
    _rear = RHS._rear;
    _size = RHS._size;
    return *this;
}
///

template <typename T>
bool Queue<T>::empty() const
{
    return (_front == nullptr && _rear == nullptr && _size == 0);
}

template <typename T>
T Queue<T>::front()
{
    assert(_front != nullptr);
    return _front->_item;
}
template <typename T>
T Queue<T>::back()
{
    assert(_front != nullptr && _rear != nullptr);
    return _rear->_item;
}

template <typename T>
void Queue<T>::push(T item)
{
    _rear = _insert_after(_front, _rear, item);
    _size++;
}

template <typename T>
T Queue<T>::pop()
{
    assert(!empty());
    T popped = _delete_node(_front, _front);
    _size--;
    if(_front == nullptr)//if last element deleted
        _rear = nullptr;//otherwise rear should not change
    return popped;
}

template <typename T>
typename Queue<T>::Iterator Queue<T>::begin() const
{
    typename Queue<T>::Iterator it(_front);
    return it;
}   
template <typename T>                                  //Iterator to the head node
typename Queue<T>::Iterator Queue<T>::end() const
{
    typename Queue<T>::Iterator it(nullptr);
    return it;
}   
template <typename T>                                    //Iterator to NULL
void Queue<T>::print_pointers()
{
    T ptr;
    if(empty())
        cout << "EMPTY QUEUE\n";
    typename Queue<T>::Iterator it;
    for(it = begin(); it != end(); ++it)
        cout << *(*it) << " ";
    cout << endl;
}

template <typename T>
void Queue<T>::print_backwards()
{
    if(empty())
    {
        cout << "EMPTY QUEUE (backwards)\n";
        return;
    }
    _print_list_backwards(_front);
}

template<typename TT>
ostream& operator << (ostream& outs, const Queue<TT>& printMe)
{
    if(printMe.empty())
        outs << "QUEUE IS EMPTY\n";
    else
    {
        outs << "{Queue : " << printMe._size << "} ";
        _print_list(outs, printMe._front);
    }
    outs << endl;
    return outs;
}

#endif