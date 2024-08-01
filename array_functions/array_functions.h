#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H
 
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
const int MINIMUM_CAPACITY = 3;
 
//function declarations
template<typename T>
T* allocate(int capacity= MINIMUM_CAPACITY);
/*
Precondition: You declared a pointer variable of the same type
Postcondition: You will get an address to a dynamic array of the given capacity (defaulted at 3)
Purpose: Allows you to create and get the pointer to a dynamic array of any type
Arguments: Capacity (int, defaulted at 3)
Return value: Returns address of dynamic array
*/
 
template<typename T>
T* reallocate(T* a, int size, int capacity);
/*
Precondition: Must declare pointer variable of same type, where capacity of new array is greater than size of old array
Postcondition: Address of new dynamic array is returned, in which dynamic array has all values of old array, but just more capacity
Old array will also be deleted
Purpose: You use this if you have an array and want to increase its capacity
Arguments: Pointer to old array, size of the old array (int), capacity of new array (int)
Return value: Returns pointer to new, bigger dynamic array with all the values of the old array
*/
 
template<typename T>
void print_array(T* a, int size, int capacity = 0);
/*
Precondition: Array must be declared before hand and size must be less than or equal to its actual capacity
Postcondition: Will print (cout) the size of the array [n] as well as all the elements contained in the array
Purpose: Can print the contents of an array as well as its size
Arguments: Pointer to array, size of the array (int), capacity of array (int)
Return value: No value returned
*/
 
template <typename T>
void print(T* a, unsigned int how_many);
/*
Precondition: Array must be declared beforehand and how_many must be less than or equal to the actual capacity of the array
Postcondition: Prints all the elements of the array with equal spacing
Purpose: Can print contents of array (used in print_array function)
Arguments: Pointer to array, how many elements to print (int, unsigned)
Return value: No value returned
*/
 
template<typename T>
T* search_entry(T* a, int size, const T& find_me);
/*
Precondition: Array is declared beforehand and size is NOT greater than actual capacity of array
Postcondition: The pointer of the first occurrence of the value in the array will be found (or not, if value is not there)
Purpose: Finds pointer for the first instance of the value in an array
Arguments: Pointer to array, size of array (int), value being searched
Return value: Returns the pointer to the found element in the array (returns nullpointer if not found)
*/
 
template <typename T>
int search(T* a, int size, const T& find_me);
/*
Precondition: Array is declared beforehand and size is NOT greater than actual capacity of array
Postcondition: The index of the first occurrence of the value in the array will be found (or not if value is not there)
Purpose: Finds the index of the first instance of the value in an array
Arguments: Pointer to array, array size (int), value being searched
Return value: Returns the index of first occurrence of value in array or -1 if not found
*/
 
template <typename T>
void shift_left(T* a, int& size, int shift_here);
/*
Precondition: Array is declared beforehand and size is NOT greater than actual capacity of array; shift_here must be index in array
Postcondition: The array will be appropriately shifted left from shift_here, size will be decreased by 1
Purpose: Shifts an array left from a specific index, ex: [4] 0 1 2 3 shifted left at index 1 becomes [3] 0 2 3
Arguments: Pointer to array, array size (int), index to shift at (int)
Return value: No value returned
*/
 
template <typename T>
void shift_left(T* a, int& size, T* shift_here);
/*
Precondition: Array is declared beforehand and size is NOT greater than actual capacity of array;
shift_here pointer must be appropriately pointing to index in the array
Postcondition: The array will be appropriately shifted left from index pointed to by shift_here, size will be decreased by 1
Purpose: Shifts an array left from a specific index, ex: [4] 0 1 2 3 shifted left at index 1 becomes [3] 0 2 3
Arguments: Pointer to array, array size (int), pointer to index to shift at
Return value: No value returned
*/
 
template <typename T>
void shift_right(T *a, int &size, int shift_here);
/*
Precondition: Array is declared beforehand and size is NOT greater than actual capacity of array; shift_here must be index in array
Postcondition: The array will be appropriately shifted right from shift_here, size will be increased by 1
Purpose: Shifts array to right at specific index, ex: [3] 0 1 2 shifted at index 1 becomes [4] 0 1 1 2
Arguments: Pointer to array, array size (int), index to shift at (int)
Return value: No value returned
*/
 
template <typename T>
void shift_right(T *a, int &size, T* shift_here);
//Precondition: Array is declared beforehand and size is NOT greater than actual capacity of array;
//shift_here pointer must be appropriately pointing to index in the array
//Postcondition: The array will be appropriately shifted right from shift_here, size will be increased by 1
//Purpose: Shifts array to right at specific index, ex: [3] 0 1 2 shifted at index 1 becomes [4] 0 1 1 2
//Arguments: Pointer to array, array size (int), pointer to index to shift at
//Return value: No value returned
 
template<typename T>
void copy_array(T *dest, const T* src, int many_to_copy);
//Precondition: Destination and source arrays are declared beforehand and many_to_copy is not greater than size of destination array
//Postcondition: Destination array will have the same contents as source array
//Purpose: To copy contents fron one array to another
//Arguments: Pointer to destination and source arrays, how many elements to copy (int)
//Return value: No value returned
 
template <typename T>
T* copy_array(const T *src, int size);
//Precondition: Source array must be declared and size must not be greater than the actual capacity of the source array
//Postcondition: Source array will be copied onto a dynamic array
//Purpose: Copies a source array into another dynamic array
//Arguments: Pointer to source array, size of array (int)
//Return value: Returns pointer to dynamic array with copied elements from source array
 
template <typename T>
string array_string(const T *a, int size);
//Precondition: Array must be declared and size must not be greater than the actual capacity of the source array
//Postcondition: String of containing all the elements in the array will be made (from left to right)
//Purpose: Turns array elements into a string
//Arguments: Pointer to array, array size (int)
//Return value: Returns string of elements of array

template <typename T>
void _append(T *a, int& size, const T& append_me);
/*
Precondition: Array must be declared and size must be less than the capacity of the array
Postcondition: The append_me value will be at the end of the array and the size will increase by 1
Purpose: Appends a val to the end of the array
Arguments: Pointer to array, array size (int), appending value
//Return value: No value returned
*/

/*
Seperation between funct. declarations and definitions
*/
 
//function definitions
template<typename T>
T* allocate(int capacity){
    return new T[capacity];//address of dynamic T array
}
 
template<typename T>
T* reallocate(T* a, int size, int capacity){
    T *newArray = allocate<T>(capacity);//allocates array of new size
    copy_array(newArray, a, size);//copies old one to it
    delete [] a;//deletes old array
    return newArray;//return address of new array
}
 
template<typename T>
void print_array(T* a, int size, int capacity){
    cout << "[" << size << " / "<< capacity << "]";
    print(a, size);
    cout << endl;
}

template<typename T>
void print(T* a, unsigned int how_many){
    //Lame person way of doing it
    T *p = a;
    for(int i = 0; i < how_many; i++)
    {
        cout << setw(4) << *p;
        p++;
    }
    //Cool person way of doing it
    // for(T *p = a; p - a < how_many; p++)
    //     cout << setw(4) << *p;
    cout << endl;
}
 
template<typename T>
T* search_entry(T* a, int size, const T& find_me){
    int index = search(a, size, find_me);
    T *p = a + index;//turns the found index int a pointer
    if(index == -1)//returns nullptr if the value is not found
        return nullptr;
    return p;
}
 
template <typename T>
int search(T* a, int size, const T& find_me){
    T *p = a;//pointer to start of array
    for(int i = 0; i < size; i++)
    {
        if(*p == find_me)//iterates throughout each element in array starting from left and returns index if found
            return i;
        p++;
    }
    return -1;//only returns -1 if the value is not found in the array
}
 
template <typename T>
void shift_left(T* a, int& size, int shift_here){
    shift_left(a, size, a + shift_here);
}
 
template <typename T>
void shift_left(T* a, int& size, T* shift_here){
    //Lame person way of doing this:
    int startingIndex = shift_here - a;//int index of shifting point
    T *p = shift_here;//pointer at shifting index
    for(int i = startingIndex; i < size - 1; i ++)//moves from left to right (starting from the shifting point)
    {
        T *next = p + 1;//The p gets the value of the element to the right of it
        *p = *next;
        p++;
    }
    //Cool person way of doing this:
    // T *startingPtr = shift_here;
    // T *end = a + size - 1;
    // for(T* p = startingPtr; p < end; p++)
    // {
    //     if(p - a == size - 1)
    //         break;
    //     T* next = p + 1;
    //     *p = *next;
    // }
    size --;
}
 
template <typename T>
void shift_right(T *a, int &size, int shift_here){
    int *shiftPtr = a + shift_here;
    shift_right(a, size, shiftPtr);
}
 
template <typename T>
void shift_right(T *a, int &size, T* shift_here){
    //Lame Way of Doing It
    int shiftingIndex = shift_here - a;//int index of where to shift
    T* p = a + size;
    T *prev;
    for(int i = size; i > shiftingIndex; i --)//we start editing the rightmost index(at size, meaning its empty)
    {
        prev = p - 1;//pointer one index to left of p
        *p = *prev;//setting right to value of left
        p--;//moving left in the array, this process moves right to left (opposite of shift_left)
    }
    // Cool way of Doing It
    // for(T *p = a + size; p > shift_here; p--)
    // {
    //     T* prev = p - 1;
    //     *p = *prev;
    // }
    size ++;
}
 
template<typename T>
void copy_array(T *dest, const T* src, int many_to_copy){
    for(int i = 0; i < many_to_copy; i++)
    {
        *dest = * src;
        dest++;
        src++;
    }
        
}
 
template <typename T>
T* copy_array(const T *src, int size){
    T *dest = allocate<T>(size);
    copy_array(dest, src, size);
    return dest;
}

template <typename T>
string array_string(const T *a, int size){
    string arrayString = "[";
    for(int i = 0; i < size - 1; i ++)//ends before size -1 because I don't want array to have space before closing bracket                                                            
    {                                 //ex: "[0 1 2 3 4 ]" is not what I eant
        arrayString += *a;
        arrayString += " ";
        a++;
    }
    arrayString += *a;
    arrayString += "]";
    return arrayString;
}

template <typename T>
void _append(T *a, int& size, const T& append_me)
{
    T *appendPtr = a + size;
    *appendPtr = append_me;
    size++;
}
#endif

