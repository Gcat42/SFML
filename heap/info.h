#ifndef INFO_H
#define INFO_H
#include <iostream>
#include <iomanip>

using namespace std;

template <typename T>
struct info{
    T item;
    int priority;
    int serial_num;

    info(): item(T()), priority(0), serial_num(0){}
    info(T i, int p, int serialNum): item(i), priority(p), serial_num(serialNum){}

    friend ostream& operator <<(ostream& outs, const info<T>& print_me){
        const bool tldr = false;
        outs << print_me.item;
        if(!tldr)
            outs << " : " << print_me.priority << " #" << print_me.serial_num;
        return outs;
    }

    friend bool operator <(const info<T>& lhs, const info<T>& rhs){
        if(lhs.priority != rhs.priority)
            return lhs.priority < rhs.priority;
        else//if priorities are the same
            return lhs.serial_num > rhs.serial_num;//if priorities the same, the smaller serial # is the bigger info obj
    }
    friend bool operator >(const info<T>& lhs, const info<T>& rhs){
        if(lhs.priority != rhs.priority)
            return lhs.priority > rhs.priority;
        else//if priorities are the same
            return lhs.serial_num < rhs.serial_num;//if priorities the same, the smaller serial # is the bigger info obj
    }

};

#endif