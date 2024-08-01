#ifndef MYSTACK_H
#define MYSTACK_H
#include <iostream>
#include <assert.h>
#include "../linked_list_functions/linkedlistfunctionsTemplated.h"
#include "../node/node.h"

using namespace std;
template <typename ITEM_TYPE>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                 //give access to list to access _ptr
        Iterator(): _ptr(nullptr){}            //default ctor
        Iterator(node<ITEM_TYPE>* p)
        {
            _ptr = p;
        }      //Point Iterator to where p is pointing to
        ITEM_TYPE operator *()
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
        {                        //member operator:++it or ++it = new_value
            assert(_ptr != nullptr);
            _ptr = _ptr->_next;
            return *this;
        }

        friend Iterator operator++(Iterator& it, int unused)
        {        //friend operator: it++
            assert(it._ptr != nullptr);
            Iterator holder(it._ptr);
            ++it;
            return holder;
        }

    private:
        node<ITEM_TYPE>* _ptr;    //pointer being encapsulated
    };

    Stack();
    Stack(const Stack<ITEM_TYPE>& copyMe);
    ~Stack();
    Stack<ITEM_TYPE>& operator=(const Stack<ITEM_TYPE>& RHS);
    ITEM_TYPE top();
    bool empty() const;
    void push(ITEM_TYPE item);
    ITEM_TYPE pop();
    template<typename T>
    friend ostream& operator<<(ostream& outs, const Stack<T>& printMe);
    void print_backwards();
    Iterator begin() const;                   //Iterator to the head node
    Iterator end() const;                     //Iterator to NULL
    int size() const { return _size; }

private:
    node<ITEM_TYPE>* _top;
    int _size;
};


template <typename ITEM_TYPE>
Stack<ITEM_TYPE>::Stack(): _top(nullptr), _size(0){}

/// BIG THREE
template <typename ITEM_TYPE>
Stack<ITEM_TYPE>::Stack(const Stack<ITEM_TYPE>& copyMe): _size(0)
{
    _top = _copy_list<ITEM_TYPE>(copyMe._top);
    _size = copyMe._size;
}

template <typename ITEM_TYPE>
Stack<ITEM_TYPE>::~Stack()
{
    _clear_list<ITEM_TYPE>(_top);
}

template <typename ITEM_TYPE>
Stack<ITEM_TYPE>& Stack<ITEM_TYPE>::operator=(const Stack<ITEM_TYPE>& RHS)
{
    _clear_list<ITEM_TYPE>(_top);
    _top = _copy_list(RHS._top);
    _size = RHS._size;
    return *this;
}
/// 

template <typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::top()
{
    assert(_top != nullptr);
    return _top->_item;
}

template <typename ITEM_TYPE>
bool Stack<ITEM_TYPE>::empty() const
{
    return (_top == nullptr && _size == 0);
}

template <typename ITEM_TYPE>
void Stack<ITEM_TYPE>::push(ITEM_TYPE item)
{
    _insert_head(_top, item);
    _size++;
}

template <typename ITEM_TYPE>
ITEM_TYPE Stack<ITEM_TYPE>::pop()
{
    assert(!empty());
    ITEM_TYPE popped = _delete_node<ITEM_TYPE>(_top, _top);
    _size--;
    return popped;
}

template<typename T>
ostream& operator<<(ostream& outs, const Stack<T>& printMe)
{
    if(printMe.empty())
        outs << "STACK IS EMPTY\n";
    else
    {
        outs << "{Stack : " << printMe._size << "} ";
        _print_list(outs, printMe._top);
    }
    outs << endl;
    return outs;
}

template <typename ITEM_TYPE>
void Stack<ITEM_TYPE>::print_backwards()
{
    if(empty())
    {
        cout << "EMPTY QUEUE (backwards)\n";
        return;
    }
    _print_list_backwards(_top);
}

template <typename ITEM_TYPE>
typename Stack<ITEM_TYPE>::Iterator Stack<ITEM_TYPE>::begin() const
{
    typename Stack<ITEM_TYPE>::Iterator it(_top);
    return it;
}
//Iterator to the head node

template <typename ITEM_TYPE>
typename Stack<ITEM_TYPE>::Iterator Stack<ITEM_TYPE>::end() const
{
    typename Stack<ITEM_TYPE>::Iterator it(nullptr);
    return it;
}
//Iterator to NULL
#endif