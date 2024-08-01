#ifndef BTREE_ARRAY_FUNCS_H
#define BTREE_ARRAY_FUNCS_H
#include <iostream>
#include <iomanip>
#include <vector>
#include <assert.h>

using namespace std;

template <typename T>
T maximal(const T& a, const T& b);                      //return the larger of the two items

template <typename T>
void swap(T& a, T& b);  //swap the two items

template <typename T>
int index_of_maximal(T data[ ], int n);                 //return index of the largest item in data

template <typename T>
void ordered_insert(T data[ ], int& n, T entry);        //insert entry into the sorted array data with length n

template <typename T>
int first_ge(const T data[ ], int n, const T& entry);   //return the first element in data that is not less than entry

template <typename T>
void attach_item(T data[ ], int& n, const T& entry);    //append entry to the right of data

template <typename T>
void insert_item(T data[ ], int i, int& n, T entry);    //insert entry at index i in data

template <typename T>
void detach_item(T data[ ], int& n, T& entry);          //remove the last element in data and place it in entry

template <typename T>
void delete_item(T data[ ], int i, int& n, T& entry);   //delete item at index i and place it in entry

template <typename T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2);   //append data2 to the right of data1

template <typename T>
void split(T data1[ ], int& n1, T data2[ ], int& n2);   //move n/2 elements from the right of data1 and move to data2

template <typename T>
void copy_array(T dest[], const T src[], int& dest_size, int src_size);              //copy src[] into dest[]

template <typename T>
void print_array(const T data[], int n, int pos = -1);  //print array data

template <typename T>
bool is_gt(const T data[], int n, const T& item);       //item > all data[i]

template <typename T>
bool is_le(const T data[], int n, const T& item);       //item <= all data[i]



//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list); //print vector list

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme); //list.push_back addme

//
//
//FUNCTION DEFINITIONS
//
//

template <typename T>
T maximal(const T& a, const T& b)
{
    if(a > b)
        return a;
    else
        return b;
}                      
//return the larger of the two items

template <typename T>
void swap(T& a, T& b)
{
    T temp = a;
    b = a;
    a = b;
}
//swap the two items

template <typename T>
int index_of_maximal(T data[ ], int n)
{
    assert(n > -1);
    T* walker = data;
    T* maxVal = data;
    for(int i = 0; i < n; i++)
    {
        if(*walker > *maxVal)
            maxVal = walker;
    }
    return 0;
}
//return index of the largest item in data

template <typename T>
void ordered_insert(T data[ ], int& n, T entry)
{
    int index = first_ge(data, n, entry);
    T* walker = data + n;
    T* prev = walker - 1;
    if(index < n)//have to implement a shift_right
    {
        for(int i = n; i > index; i--, walker--, prev--)
            *walker = *prev;//shift everything to the right of index (including current element at index)
    }
    *walker = entry;//puts entry into the new open walker pos
    n++;
}
//insert entry into the sorted array data with length n

template <typename T>
int first_ge(const T data[ ], int n, const T& entry)
{
    for(int i = 0; i < n; i++)
    {
        if(entry <= data[i])
            return i;
    }
    return n;
}
//return the first element in data that is not less than entry

template <typename T>
void attach_item(T data[ ], int& n, const T& entry)
{
    T* walker = data + n;//LOL
    *walker = entry;
    n++;
}
//append entry to the right of data

template <typename T>
void insert_item(T data[ ], int i, int& n, T entry)
{
    assert(i > -1);
    T* walker = data + n;
    T* prev = walker - 1;
    if(i > n)//won't insert if i is out of bounds
    {
        cout << "I: " << i << " n: " << n << endl;
        cout << "NOT INSERTING VALUE: INSERT INDEX IS IN BOUNDS OF N (INCLUDING N)!\n";
        return;
    }
    else//have to implement a shift_right
    {
        for(int j = n; j > i; j--, walker--, prev--)
            *walker = *prev;//shift everything to the right of index (including current element at index)
    }
    *walker = entry;//puts entry into the new open walker pos
    n++;
}
//insert entry at index i in data

template <typename T>
void detach_item(T data[ ], int& n, T& entry)
{
    assert(n > 0);//need to assert that there is something to detach
    T* walker = data + n - 1;
    entry = *walker;
    n--;
}
//remove the last element in data and place it in entry

template <typename T>
void delete_item(T data[ ], int i, int& n, T& entry)
{
    assert(n > i && i > -1);
    T* walker = data + i;
    T* next;
    entry = *walker;//popped val
    //need to do a shift left from i
    for(int j = i; j < n - 1; j++, walker++)
    {
        next = walker + 1;
        *walker = *next;
    }
    n--;
}
//delete item at index i and place it in entry

template <typename T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2)
{
    T* d1Walker = data1 + n1;
    T* d2Walker = data2;
    for(int i = 0; i < n2; i++, d1Walker++, d2Walker++)
        *d1Walker = *d2Walker;
    n1 += n2;
    n2 = 0;
}
//append data2 to the right of data1

template <typename T>
void split(T data1[ ], int& n1, T data2[ ], int& n2)
{
    bool isOdd = n1 % 2;//will be 1 if odd, will be 0 if even
    int halfSize = (n1 / 2) + isOdd;//ex: you want half size to be 2 if n is 3, but also 2 if n is 4
    n2 = n1 - halfSize;
    T* d1Walker = data1 + halfSize;
    T* d2Walker = data2;
    for(int i = 0; i < n2; i++, d1Walker++, d2Walker++)
        *d2Walker = *d1Walker;
    n1 = halfSize;
}
//move n/2 elements from the right of data1 and move to data2

template <typename T>
void copy_array(T dest[], const T src[], int& dest_size, int src_size)
{
    T* destWalker = dest;
    const T* srcWalker = src;
    for(int i = 0; i < src_size; i++, destWalker++, srcWalker++)
        *destWalker = *srcWalker;
    dest_size = src_size;
}
//copy src[] into dest[]

template <typename T>
void print_array(const T data[], int n, int pos)
{
    if(n == 0)
    {
        cout << "EMPTY\n";
        return;
    }
    assert(pos < n);//can't print starting at index out of bounds
    const T* walker = data + pos;
    cout << "[ ";
    for(int i = 0; i < n; i++, walker++)
        cout << *walker << " ";
    cout << "]\n";
}
//print array data

template <typename T>
bool is_gt(const T data[], int n, const T& item)
{
    const T* walker = data;
    for(int i = 0; i < n; i++, walker++)
    {
        if(*walker > item)
            return false;
    }
    return true;
}
//item > all data[i]

template <typename T>
bool is_le(const T data[], int n, const T& item)
{
    const T* walker = data;
    for(int i = 0; i < n; i++, walker++)
    {
        if(*walker < item)
            return false;
    }
    return true;
    return false;
}
//item <= all data[i]

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list)
{
    outs << "[ ";
    for(int i = 0; i < list.size(); i++)
        outs << list[i] << " ";
    outs << "]\n";
    return outs;
}
//print vector list

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme)
{
    list.push_back(addme);
    return list;
}
//list.push_back addme
#endif