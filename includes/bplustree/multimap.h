#ifndef MULTIMAP_H
#define MULTIMAP_H
#include <iostream>
#include <string>
#include <vector>
#include "bplustree.h"
#include "mpair.h"

template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator{
    public:
        friend class MMap;
        Iterator(){}
        Iterator(typename map_base::Iterator it): _it(it){}
        Iterator operator ++(int unused)
        {
            return _it++;
        }
        Iterator operator ++()
        {
            return ++_it;
        }
        MPair<K, V> operator *()
        {
            return *_it;
        }

        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            return lhs._it == rhs._it;
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {
            return !(lhs == rhs);
        }

    private:
        typename map_base::Iterator _it;
    };

    MMap();

//  Iterators
    Iterator begin();
    Iterator end();

//  Capacity
    int size() const;
    bool empty() const;

//  Element Access
    const vector<V>& operator[](const K& key) const;
    vector<V>& operator[](const K& key);

//  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();

//  Operations:
    bool contains(const K& key) const ;
    vector<V>& get(const K& key);

    Iterator find(const K& key);
    int count(const K& key);
    // I have not writtent hese yet, but we will need them:
    Iterator lower_bound(const K& key);
    Iterator upper_bound(const K& key);
    bool equal_range();

    V& at(const K& key);
    const V& at(const K& key) const;

    bool is_valid();

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me)
    {
        outs<<print_me.mmap<<endl;
        return outs;
    }

    void print_lookup();

private:
    BPlusTree<MPair<K, V>> mmap;
};

template <typename K, typename V>
MMap<K, V>::MMap(): mmap(true){}

//  Iterators
template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::begin()
{
    typename MMap<K, V>::Iterator it(mmap.begin());
    return it;
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::end()
{
    typename MMap<K, V>::Iterator it;
    return it;
}

//  Capacity
template <typename K, typename V>
int MMap<K, V>::size() const
{
    return mmap.size();
}

template <typename K, typename V>
bool MMap<K, V>::empty() const
{
    return mmap.empty();
}

//  Element Access
template <typename K, typename V>
const vector<V>& MMap<K, V>::operator[](const K& key) const
{
    return get(key);
}

template <typename K, typename V>
vector<V>& MMap<K, V>::operator[](const K& key)
{
    return get(key);
}

//  Modifiers
template <typename K, typename V>
void MMap<K, V>::insert(const K& k, const V& v)
{
    MPair<K,V> mp(k, v);
    mmap.insert(mp);
}

template <typename K, typename V>
void MMap<K, V>::erase(const K& key)
{
    MPair<K,V> mp(key);
    mmap.remove(mp);
}

template <typename K, typename V>
void MMap<K, V>::clear()
{
    mmap.clear_tree();
}

//  Operations:
template <typename K, typename V>
bool MMap<K, V>::contains(const K& key) const 
{
    MPair<K,V> mp(key);
    return mmap.contains(mp);
}

template <typename K, typename V>
vector<V>& MMap<K, V>::get(const K& key)
{
    MPair<K,V> dummy(key);
    return mmap.get(dummy).value_list;
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::find(const K& key)
{
    typename MMap<K,V>::Iterator it;
    return it;
}

template <typename K, typename V>
int MMap<K, V>::count(const K& key)
{
    MPair<K,V> mp(key);
    return mmap.get(key).value_list.size();;
}
// I have not writtent hese yet, but we will need them:
//    int count(const K& key);
//    lower_bound
//    upper_bound
//    equal_range:

template <typename K, typename V>
bool MMap<K, V>::is_valid()
{
    return false;
}

template <typename K, typename V>
V& MMap<K,V>::at(const K& key)
{
    vector<V> v(get(key));
    return v[0];
}

template <typename K, typename V>
const V& MMap<K,V>::at(const K& key) const
{
    vector<V> v(get(key));
    return v[0];
}

template <typename K, typename V>
void MMap<K,V>::print_lookup()
{
    if(empty())
    {
        cout << "EMPTY\n";
        return;
    }
    typename MMap<K,V>::Iterator it;
    for(it = begin(); it != end(); ++it)
        cout << *it << endl;
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::lower_bound(const K& key)
{
    MPair<K,V> mp(key);
    typename MMap<K,V>::Iterator it(mmap.lower_bound(mp));
    return it;
}

template <typename K, typename V>
typename MMap<K, V>::Iterator MMap<K, V>::upper_bound(const K& key)
{
    MPair<K,V> mp(key);
    typename MMap<K,V>::Iterator it(mmap.upper_bound(mp));
    return it;
}

template <typename K, typename V>
bool equal_range()
{
    return false;
}

#endif