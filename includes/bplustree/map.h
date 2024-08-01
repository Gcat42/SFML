#ifndef MAP_H
#define MAP_H
#include "pair.h"
#include "bplustree.h"

template <typename K, typename V>
class Map
{
public:
    typedef BPlusTree<Pair<K, V> > map_base;
    class Iterator{
    public:
        friend class Map;
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
        Pair<K, V> operator *()
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
    Map();
//  Iterators
    Iterator begin();
    Iterator end();

//  Capacity
    int size() const;
    bool empty() const;

//  Element Access
    V& operator[](const K& key);
    V& at(const K& key);
    const V& at(const K& key) const;


//  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();
    V get(const K& key);

//  Operations:
    Iterator find(const K& key);
    bool contains(const Pair<K, V>& target) const;

    // I have not writtent hese yet, but we will need them:
   int count(const K& key);
   Iterator lower_bound(const K& item);
   Iterator upper_bound(const K& item);
   bool equal_range();

   bool is_valid(){return map.is_valid();}

   friend ostream& operator<<(ostream& outs, const Map<K, V>& print_me)
   {
        outs<<print_me.map<<endl;
        return outs;
   }
private:
    int key_count;
    BPlusTree<Pair<K, V> > map;
};

template <typename K, typename V>
Map<K,V>::Map(): key_count(0){}

//  Iterators
template <typename K, typename V>
typename Map<K,V>::Iterator Map<K,V>::begin()
{
    typename Map<K,V>::Iterator it(map.begin());
    return it;
}

template <typename K, typename V>
typename Map<K,V>::Iterator Map<K,V>::end()
{
    typename Map<K,V>::Iterator it(map.end());
    return it;
}


//  Capacity
template <typename K, typename V>
int Map<K,V>::size() const
{
    return map.size();
}

template <typename K, typename V>
bool Map<K,V>::empty() const
{
    return map.empty();
}


//  Element Access
template <typename K, typename V>
V& Map<K,V>::operator[](const K& key)
{
    return at(key);
}

template <typename K, typename V>
V& Map<K,V>::at(const K& key)
{
    Pair<K,V> dummy(key);
    Pair<K,V>* p = &(map.get(dummy));
    return p->value;
}

template <typename K, typename V>
const V& Map<K,V>::at(const K& key) const
{
    Pair<K,V> dummy(key);
    Pair<K,V>* p = &(map.get(dummy));
    return p->value;
}



//  Modifiers
template <typename K, typename V>
void Map<K,V>::insert(const K& k, const V& v)
{
    Pair<K,V> insertThis(k, v);
    map.insert(insertThis);
    key_count++;
}

template <typename K, typename V>
void Map<K,V>::erase(const K& key)
{
    Pair<K,V> dummy(key, V());
    map.remove(dummy);
}

template <typename K, typename V>
void Map<K,V>::clear()
{
    map.clear_tree();
}

template <typename K, typename V>
V Map<K,V>::get(const K& key)
{
   return at(key);
}


//  Operations:
template <typename K, typename V>
typename Map<K,V>::Iterator Map<K,V>::find(const K& key)
{
    V dummy;//use this as dummy var for Pair object
    return map.find(Pair<K,V>(key, dummy));
}

template <typename K, typename V>
bool Map<K,V>::contains(const Pair<K, V>& target) const
{
    return map.contains(target);
}

template <typename K, typename V>
int count(const K& key)
{
    return 0;
}

template <typename K, typename V>
typename Map<K,V>::Iterator Map<K,V>::lower_bound(const K& item)
{
    Pair<K,V> holder(item);
    typename Map<K,V>::Iterator it(map.lower_bound(holder));
    return it;
}

template <typename K, typename V>
typename Map<K,V>::Iterator Map<K,V>::upper_bound(const K& item)
{
    Pair<K,V> holder(item);
    typename Map<K,V>::Iterator it(map.upper_bound(holder));
    return it;
}

template <typename K, typename V>
bool Map<K,V>::equal_range()
{
    return false;
}
#endif