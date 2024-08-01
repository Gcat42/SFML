#ifndef PAIR_H
#define PAIR_H

template <typename K, typename V>
struct Pair{
    K key;
    V value;

    Pair(const K& k=K(), const V& v=V());
    friend ostream& operator <<(ostream& outs, const Pair<K, V>& print_me)
    {
        outs << "|" << print_me.key << ": " << print_me.value << "|";
        return outs;
    }
    friend bool operator ==(const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key == rhs.key;
    }
    friend bool operator < (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return lhs.key < rhs.key;
    }
    friend bool operator > (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        
        return lhs.key > rhs.key;
    }
    friend bool operator <= (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return (lhs < rhs) || (lhs == rhs);
    }
    friend bool operator >= (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        return (lhs > rhs) || (lhs == rhs);
    }
    friend Pair<K, V> operator + (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        Pair<K,V> p;
        return p;
    }
};

template <typename K, typename V>
Pair<K,V>::Pair(const K& k, const V& v): key(k), value(v){}

#endif