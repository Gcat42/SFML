#ifndef MPAIR_H
#define MPAIR_H
#include <iostream>
#include <iomanip>
#include <vector>
#include "btree_array_funcs.h"

template <typename K, typename V>
struct MPair{
    K key;
    vector<V> value_list;

    //--------------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a vector of values (to replace value_list)
     */
    //--------------------------------------------------------------------------------
    MPair(const K& k=K());
    MPair(const K& k, const V& v);
    MPair(const K& k, const vector<V>& vlist);
    //--------------------------------------------------------------------------------

    //You'll need to overlod << for your vector:
    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me)
    {
        outs << right << setw(11) << print_me.key << ":\t";
        for(int i = 0; i < print_me.value_list.size(); i++)
        {
            outs << print_me.value_list[i] << " ";
        }
        return outs;
    }
    
    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key == rhs.key;
    }
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key < rhs.key;
    }
    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return (lhs < rhs) || (lhs == rhs);
    }
    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        return lhs.key > rhs.key;
    }
    friend bool operator >=(const MPair<K,V>& lhs, const MPair<K,V>& rhs)
    {
        return (lhs > rhs) || (lhs == rhs);
    }
    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        assert(lhs.key == rhs.key);
        MPair<K,V> mp(lhs.key, lhs.value_list);
        for(int i = 0; i < rhs.value_list.size(); i++)
            mp.value_list += rhs.value_list[i];
        return mp;
    }
};

template <typename K, typename V>
MPair<K,V>::MPair(const K& k): key(k){}

template <typename K, typename V>
MPair<K,V>::MPair(const K& k, const V& v): key(k)
{
    value_list += v;
}

template <typename K, typename V>
MPair<K,V>::MPair(const K& k, const vector<V>& vlist): key(k), value_list(vlist){}

#endif