#ifndef CHAINED_HASH_H
#define CHAINED_HASH_H
#include <iostream>
#include <iomanip>
#include <assert.h>
#include "../avl/avl.h"
#include "../tree_node/tree_node.h"
#include "constants.h"

using namespace std;

template <typename T>
class ChainedHash
{
public:
    ChainedHash();                              //CTOR

    bool insert(const T& entry);            //insert entry; false if overwriting.
    bool remove(int key);                   //remove this key

    bool find(int key, T& result) const;    //result <- record with key
    bool is_present(int key) const;         //is this key present in table?
    int size() const;//number of keys in the table
    long capacity();


    //print entire table with keys, etc.
    template<class TT>
    friend ostream& operator << (ostream& outs, const ChainedHash<TT>& h);

private:
    AVL<T> _data[TABLE_SIZE];               //table chains
    int total_records;                      //number of keys in the table

    tree_node<T>* find(int key);//will find a node in the AVL
    int hash(int key) const;                //hash function
};

template <typename T>
ChainedHash<T>::ChainedHash(): total_records(0)
{
    for(int i = 0; i < TABLE_SIZE; i++)
        _data[i] = AVL<T>();
}                              //CTOR

template <typename T>
bool ChainedHash<T>::insert(const T& entry)
{
    assert(entry._key > -1);
    int index = hash(entry._key);
    bool found;
    T result;
    // cout << "Before find\n";
    found = find(entry._key, result);
    // cout << "Past find\n";
    if(found)
    {
        tree_node<T>* foundPtr = (_data[index]).contains(result, found);
        *foundPtr = entry;
        return false;
    }
    _data[index].insert(entry);
    total_records++;
    return true;
}            //insert entry; false if overwriting.

template <typename T>
bool ChainedHash<T>::remove(int key)
{
    assert(key > -1);
    int index = hash(key);
    bool found;
    T result;
    found = find(key, result);
    if(!found)
        return false;
    _data[index].erase(result);
    total_records--;
    return true;
}                   //remove this key

template <typename T>
bool ChainedHash<T>::find(int key, T& result) const
{
    assert(key > -1);
    int index = hash(key);
    T item;
    item._key = key;//just needs the same key to search through avl, not the same actual value in the node
    bool found;
    // cout << "BEFORE CONTAINS\n";
    tree_node<T>* foundPtr = find(key);
    found = foundPtr != nullptr;
    // cout << "AFTER CONTAINS\n";
    if(found)
        result = foundPtr->_item;
    return found;
}    //result <- record with key

template <typename T>
bool ChainedHash<T>::is_present(int key) const
{
    T item;
    item._key = key;//acts as dummy variable
    return find(key, item);
}        //is this key present in table?

template <typename T>
int ChainedHash<T>::size( ) const
{
    return total_records; 
}  //number of keys in the table

template <typename T>
long ChainedHash<T>::capacity()
{
    long CAPACITY = TABLE_SIZE;
    return CAPACITY;
}

//print entire table with keys, etc.
template<class TT>
ostream& operator << (ostream& outs, const ChainedHash<TT>& h)
{
    // AVL<T>* walker = h._data;
    for(int i = 0; i < TABLE_SIZE; i++)
        outs << h._data[i];//prints each avl
    outs << endl;
    return outs;
}

template <typename T>
int ChainedHash<T>::hash(int key) const
{
    return key % TABLE_SIZE;
}

template <typename T>
tree_node<T>* find(int key)
{
    int index = hash(key);
    T dummy;//dummy variable
    dummy._key = key;
    bool found;
    return _data[index].contains(dummy, found);
}
#endif
