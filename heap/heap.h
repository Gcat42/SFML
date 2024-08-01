#ifndef HEAP_H
#define HEAP_H
#include <iostream>
#include <iomanip>
#include <assert.h>
#include "array_functions/array_functions.h"

using namespace std;

template <typename T>
class Heap
{
public:
    Heap();
    //BIG THREE
    Heap(const Heap& copy_me);
    Heap& operator =(const Heap<T>& rhs);
    ~Heap();
    //
    void insert(const T& insert_me);    //insert into the heap
    T remove();                         //remove and return top value 
    T top();                            //return the value at the top of heap
    bool is_empty() const;
    int size() const;
    int capacity() const;

    template <typename U>
    friend ostream& operator << (ostream& outs, const Heap<U>& print_me);
    bool verify() const;                //true if tree is verified to be a heap
    T *heap_array();                    //returns a copy of underlying array: don't forget to delete when done

    template <typename U>
    friend bool operator == (const Heap<U>& lhs, const Heap<U>& rhs);

    template <typename U>
    friend bool operator != (const Heap<U>& lhs, const Heap<U>& rhs);

private:
    static const int CAPACITY = 1000;
    T* _heap; //static array
    int _how_many; //num used

    void print_tree(ostream& outs = cout) const;
    void print_tree(int root, int level = 0, ostream& outs = cout) const;

    bool verify(int root) const;

    bool is_root(int i) const;
    bool is_leaf(int i) const;
    int parent_index(int i) const;
    int left_child_index(int i)const;
    int right_child_index(int i) const;
    int big_child_index(int i) const;
    void swap_with_parent(int i);
};

template <typename T>
Heap<T>::Heap():_how_many(0)
{
    _heap = allocate<T>(CAPACITY);
}

//BIG THREE
template <typename T>
Heap<T>::Heap(const Heap& copy_me)
{
    _heap = allocate<T>(CAPACITY);
    _how_many = copy_me._how_many;
    copy_array(_heap, copy_me._heap, _how_many);
}

template <typename T>
Heap<T>& Heap<T>::operator =(const Heap<T>& rhs)
{
    if(!(&rhs == this))
    {
        _how_many = rhs._how_many;
        copy_array(_heap, rhs._heap, _how_many);
    }
    return *this;
}

template <typename T>
Heap<T>::~Heap()
{
    delete [] _heap;
}

//
template <typename T>
void Heap<T>::insert(const T& insert_me)
{
    assert(_how_many < CAPACITY);
    T* last = _heap + _how_many;
    *last = insert_me;
    int insertedIndex = _how_many;
    int parentIndex = parent_index(insertedIndex);
    _how_many++;
    while(!is_root(insertedIndex) && !verify(parentIndex))//rising for inserted node if needed, if rise to the top end
    {
        swap_with_parent(insertedIndex);//need to swap insert and parent
        insertedIndex = parentIndex;//since there is a swap inserted index becomes the parents old index
        parentIndex = parent_index(insertedIndex);//then we get the parent of the old parent and try again!
    }
    assert(verify());
}   //insert into the heap

template <typename T>
T Heap<T>::remove()
{
    assert(_how_many > 0);
    T popped = *_heap;
    T* walker = _heap + _how_many - 1;//last element
    *_heap = *walker;//last element gets put to the top
    _how_many--;
    int index = 0;
    while(!verify(index))//as long as children are bigger than inserted val, it will sink
    {
        int biggerChild = big_child_index(index);
        swap_with_parent(biggerChild);//sinks insert to bigger child's position
        index = biggerChild;
    }
    assert(verify());
    return popped;
}                         //remove and return top value 

template <typename T>
T Heap<T>::top()
{
    return *_heap;
}                            //return the value at the top of heap

template <typename T>
bool Heap<T>::is_empty() const
{
    return _how_many == 0;
}

template <typename T>
int Heap<T>::size() const
{
    return _how_many;
}

template <typename T>
int Heap<T>::capacity() const
{
    return CAPACITY;
}

template <typename U>
ostream& operator << (ostream& outs, const Heap<U>& print_me)
{
    print_me.print_tree(outs);
    return outs;
}

template <typename T>
bool Heap<T>::verify() const
{
    for(int i = 0; i < _how_many; i++)//goes from first element to last element
    {
        // print_tree();
        if(!verify(i))//if the node's children are greater than the node itself
            return false;
    }
    return true;//will return true if all the nodes have went through verified
}
//true if tree is verified to be a heap

template <typename T>  
T* Heap<T>::heap_array()
{
    T* copyHeap = allocate<T>(CAPACITY);
    copyHeap = copy_array<T>(_heap, _how_many);
    return copyHeap;
}

template <typename T>
void Heap<T>::print_tree(ostream& outs) const
{
    print_tree(0, 0, outs);
}

template <typename T>
void Heap<T>::print_tree(int root, int level, ostream& outs) const
{
    if(_how_many == 0)//for empty heap
    {
        outs << "EMPTY HEAP\n";
        return;
    }
    T* walker = _heap + root;
    if(root >= _how_many)//base case since we want to do in_order from right to left
        return;
    print_tree(right_child_index(root), level + 1, outs);
    outs << right << setw(level * 6) << "[" << *walker << "]\n";
    print_tree(left_child_index(root), level + 1, outs);
}

template <typename T>
bool Heap<T>::verify(int root) const
{
    T* walker;
    T* parentVal = _heap + root;
    int leftIndex = left_child_index(root);
    int rightIndex = right_child_index(root);
    if(leftIndex < _how_many)//if leftIndex is within the boundaries of size
    {
        walker = _heap + leftIndex;
        if(*walker > *parentVal)
            return false;
    }
    else//if left doesnt exist, the right child won't exist either, meaning its verified
        return true;
    if(rightIndex < _how_many)
    {
        walker = _heap + rightIndex;
        if(*walker > *parentVal)
            return false;
    }
    return true;//will return true if both children are less than parent or if children just don't exist
}

template <typename T>
bool Heap<T>::is_root(int i) const
{
    return i == 0;
}

template <typename T>
bool Heap<T>::is_leaf(int i) const
{
    int childIndex = left_child_index(i);
    return childIndex >= _how_many;
}//no children

template <typename T>
int Heap<T>::parent_index(int i) const
{
    return (i - 1) / 2;
}

template <typename T>
int Heap<T>::left_child_index(int i)const
{
    return 2 * i + 1;
}

template <typename T>
int Heap<T>::right_child_index(int i) const 
{
    return 2 * i + 2;
}

template <typename T>
int Heap<T>::big_child_index(int i) const
{
    //will not be called when parent doesn't have at least one child
    assert(!is_leaf(i));
    int left = left_child_index(i);
    int right = right_child_index(i);//what if right child doesn't exist
    T* leftPtr = _heap + left;
    T* rightPtr = _heap + right;
    if((right < _how_many) && (*rightPtr > *leftPtr))//only returns if right child exists
        return right;
    return left;
}

template <typename T>
void Heap<T>::swap_with_parent(int i)
{
    assert(i != 0);
    int parentIndex = parent_index(i);
    T* parent = _heap + parentIndex;//pointing to
    T* child = _heap + i;
    T holder = *child;
    *child = *parent;
    *parent = holder;
}


template <typename U>
bool operator == (const Heap<U>& lhs, const Heap<U>& rhs)
{
    if(lhs._how_many != rhs._how_many)//should be the same size
        return false;
    U* lWalker = lhs._heap;
    U* rWalker = rhs._heap;
    if(lWalker == rWalker)//_heap should not point at the same thing
        return false;
    for(int i = 0; i < lhs._how_many; i++, lWalker++, rWalker++)
    {
        if(*lWalker != *rWalker)
            return false;
    }
    return true;
}

template <typename U>
bool operator != (const Heap<U>& lhs, const Heap<U>& rhs)
{
    return !(lhs == rhs);
}
#endif