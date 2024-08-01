#ifndef VECTOR_UTILITIES_H
#define VECTOR_UTILITIES_H
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
void operator+=(vector<T>& result, const vector<T>& addMe);

template <typename T>
void operator+=(vector<T>& result, const vector<T>& addMe)
{
    for(int i = 0; i < addMe.size(); i++)
        result.push_back(addMe[i]);
}

#endif