#ifndef OPEN_HASH_H
#define OPEN_HASH_H
#include <iostream>
#include <iomanip>
#include <assert.h>
#include "constants.h"
#include "../array_functions/array_functions.h"


using namespace std;

template <typename T>
class OpenHash
{
    public:
        OpenHash();
        OpenHash(const OpenHash& copyMe);
        OpenHash& operator =(const OpenHash& rhs);
        ~OpenHash();
        //manipulators
        void insert(const T& entry);
        void remove(int key);
        //const member functions
        bool is_present(int key) const;
        void find(int key, bool& found, T& result) const;
        int size();
    private:
        T* _table;
        int _used;
        //helper functions
        int hash(int key) const;
        int next_index(int index) const;
        void find_index(int key, bool& found, int& index);
        bool never_used(int index) const;
        bool is_vacant(int index) const;
};

template <typename T>
OpenHash<T>::OpenHash(): _used(0)
{
    _table = allocate<T>(TABLE_SIZE);
    //need to turn all the keys to -1
    T* walker = _table;
    for(int i = 0; i < TABLE_SIZE; i++)
        walker->_key = NEVER_USED;//sets everything to -1
}

template <typename T>
OpenHash<T>::OpenHash(const OpenHash& copyMe): _used(0)
{
    _table = allocate<T>(TABLE_SIZE);
    copy_array(copyMe._table, _table, TABLE_SIZE);
    _used = copyMe._used;
}

template <typename T>
OpenHash<T>& OpenHash<T>::operator =(const OpenHash& rhs)
{
    if(&rhs == this)
        return *this;
    delete [] _table;
    _table = allocate<T>(TABLE_SIZE);
    copy_array(_table, rhs._table, TABLE_SIZE);
    _used = rhs._used;
    return *this;
}

template <typename T>
OpenHash<T>::~OpenHash()
{
    delete [] _table;
}

template <typename T>
void OpenHash<T>::insert(const T& entry)
{
    assert(entry._key > -1);
    bool found;
    int index;
    T* walker;
    find_index(entry._key, found, index);
    if(!found)
    {
        assert(_used < TABLE_SIZE);
        while(!is_vacant(index))
            index = next_index(index);
        walker = _table + index;
        *walker = entry;
        _used++;
    }
    else
    {
        walker = _table + index;
        *walker = entry;
    }   
}

template <typename T>
void OpenHash<T>::remove(int key)
{
    assert(key > -1);
    int index;
    int found;
    T* walker;
    find_index(key, found, index);
    if(found)
    {
        walker = _table + index;
        walker->_key = PREVIOUSLY_USED;
        _used--;
    }
}

template <typename T>
bool OpenHash<T>::is_present(int key) const
{
    assert(key > -1);
    bool found;
    int index;
    find_index(key, found, index);
    return found;
}

template <typename T>
void OpenHash<T>::find(int key, bool& found, T& result) const
{
    assert(key > -1);
    int index;
    T* walker;
    find_index(key, found, index);
    walker = _table + index;
    if(found)
        result = *walker;//need to reconsider changing later incase type T is dynamic
}

template <typename T>
int OpenHash<T>::size()
{
    return _used;
}

template <typename T>
int OpenHash<T>::hash(int key) const
{
    return key % TABLE_SIZE;
}

template <typename T>   
int OpenHash<T>::next_index(int index) const
{
    return (++index) % TABLE_SIZE; 
}

template <typename T>
void OpenHash<T>::find_index(int key, bool& found, int& index)
{
    assert(key > -1);
    int count = 0;
    index = hash(key);
    T* walker = _table + index;
    while((count <= TABLE_SIZE) && (walker->_key != key) && (!never_used(index)))
    {
        index = next_index(index);
        walker = _table + index;
        count++;
    }
    found = (walker->_key == key);
}

template <typename T>
bool OpenHash<T>::never_used(int index) const
{
    T* walker = _table + index;
    int key = walker->_key;
    return key == NEVER_USED;
}


template <typename T>
bool OpenHash<T>::is_vacant(int index) const
{
    T* walker = _table + index;
    return walker->_key <= NEVER_USED;
}

#endif