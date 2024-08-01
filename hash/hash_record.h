#ifndef HASH_RECORD_H
#define HASH_RECORD_H
#include <iostream>
#include <iomanip>
#include "constants.h"

using namespace std;

template <typename T>
struct HashRecord{
    int _key;
    T _item;
    HashRecord(int key = NEVER_USED, T item = T()):_key(key), _item(item){}
    friend ostream& operator <<(ostream& outs, const HashRecord& h){
        cout << "[" << h._key << ":" << h._item << "]";
        return outs;
    }
    friend bool operator < (const HashRecord& left, const HashRecord& right){
        return left._key < right._key;
    }
    friend bool operator > (const HashRecord& left, const HashRecord& right){
        return left._key > right._key;
    }
    friend bool operator == (const HashRecord& left, const HashRecord& right){
        return left._key == right._key;
    }

    friend string to_string(const HashRecord& h){
        return string(to_string(h._key) + " : " + h._item);
    }
};

#endif