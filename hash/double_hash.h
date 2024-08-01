#ifndef DOUBLE_HASH_H
#define DOUBLE_HASH_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <assert.h>

using namespace std;

template <typename T>
class DoubleHash
{
public:
    static const int CAPACITY = TABLE_SIZE;        //size of the table
    DoubleHash();                      //CTOR

    bool insert(const T& entry);         //insert entry; false if overwriting.
    bool remove(int key);                //remove this key

    bool is_present(int key) const;      //is this key present?
    bool find(int key, T& result) const; //result <- record with this key
    int size() const;   //number of keys in this table
    
    long collisions() const;//number of collisions in this table
    long capacity() const;

    //print the entire talbe with keys, records, and hash values
    template<class TT>
    friend ostream& operator << (ostream& outs, const DoubleHash<TT>& h);
private:

    static const int NEVER_USED = -1;        //this cell has never had a value
    static const int PREVIOUSLY_USED = -2;   //this cell has previously held a value that has since been deleted.

    vector<T> _data;                          //table of records
    int used;                                //number of keys in the table
    long _collisions;

    int hash(int key) const;                //hash function
    int hash2(int key) const;               //hash2 function
    int next_index(int index, int key) const;       //wrap around index
    bool find_index(int key, int& index) const;     //find index of this key
    bool never_used(int index) const;      //is this cell NEVER_USED
    bool is_vacant(int index) const;       //is this cell available for insert
};

template <typename T>
DoubleHash<T>::DoubleHash(): used(0), _collisions(0)
{

    for(int i = 0; i < TABLE_SIZE; i++)
    {
        T item;
        item._key = NEVER_USED;
        _data.push_back(item);
    } 
}                      //CTOR

template <typename T>
bool DoubleHash<T>::insert(const T& entry)
{
    assert(entry._key > -1);
    bool found;
    int index;
    found = find_index(entry._key, index);
    if(!found)
    {
        assert(used < TABLE_SIZE);
        index = hash(entry._key);
        while(!is_vacant(index))
        {
            index = next_index(index, entry._key);
            _collisions++;
        }
        _data[index] = entry;
        used++;
        return true;
    }
    else
    {
        _data[index] = entry;
        return false;
    }   
}         //insert entry; false if overwriting.

template <typename T>
bool DoubleHash<T>::remove(int key)
{
    assert(key > -1);
    int index;
    int found;
    found = find_index(key, index);
    if(found)
    {
        T item;
        item._key = PREVIOUSLY_USED;
        _data[index] = item;
        used--;
    }
    return found;
}                //remove this key

template <typename T>
bool DoubleHash<T>::is_present(int key) const
{
    int index;
    return find_index(key, index);
}      //is this key present?

template <typename T>
bool DoubleHash<T>::find(int key, T& result) const
{
    bool found;
    int index;
    found = find_index(key, index);
    if(found)
        result = _data[index];
    return found;
} //result <- record with this key

template <typename T>
int DoubleHash<T>::size( ) const
{
    return used;
}   //number of keys in this table
                                        
template <typename T>
long DoubleHash<T>::collisions() const
{
    return _collisions;
}//number of collisions in this table

template <typename T>
long DoubleHash<T>::capacity() const
{
    return CAPACITY;
}

//print the entire talbe with keys, records, and hash values
template<class TT>
ostream& operator << (ostream& outs, const DoubleHash<TT>& h)
{
    for(int i = 0; i < TABLE_SIZE; i++)
        outs << h._data[i] << endl;
    return outs;
}

template <typename T>
int DoubleHash<T>::hash(int key) const
{
    return key % TABLE_SIZE;
}                //hash function

template <typename T>
int DoubleHash<T>::hash2(int key) const
{
    return 1 + (hash(key) % (TABLE_SIZE - 2));
}               //hash2 function

template <typename T>
int DoubleHash<T>::next_index(int index, int key) const
{
    return (index + hash2(key)) % TABLE_SIZE;
}       //wrap around index

template <typename T>
bool DoubleHash<T>::find_index(int key, int& index) const
{
    assert(key > -1);
    bool found;
    int count = 0;
    index = hash(key);
    while((count <= TABLE_SIZE) && (_data[index]._key != key) && (!never_used(index)))
    {
        index = next_index(index, key);
        count++;
    }
    found = (_data[index]._key == key);
    return found;
}     //find index of this key

template <typename T>
bool DoubleHash<T>::never_used(int index) const
{
    int key = _data[index]._key;
    return key == NEVER_USED;
}      //is this cell NEVER_USED

template <typename T>
bool DoubleHash<T>::is_vacant(int index) const
{
    int key = _data[index]._key;
    return key <= NEVER_USED;
}       //is this cell available for insert
#endif