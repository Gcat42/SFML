#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <iomanip>
#include <string.h>
#include "avl_functions.h"

using namespace std;

template <typename T>
class AVL{
public:
    AVL();
    AVL(const T *sorted_list, int size = -1);
    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    AVL(const AVL<T> &copy_me);
    AVL<T> &operator=(const AVL<T> &rhs);
    ~AVL();
    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    bool insert(const T &insert_me);

    bool erase(const T &target);

    
    bool contains(const T &target)const;

    tree_node<T>* contains(const T& target, bool& found) const;

    void clear();
    void clear_all();
    bool empty()const;
    friend ostream &operator<<(ostream &outs, const AVL<T> &tree)
    {
        const bool debug = true;
        if (debug){
            cout<<"-------------------------------"<<endl;
            tree_print_debug(tree._root, 0, outs);
            cout<<". . . . . . . . . . . . . . . ."<<endl;
        }
        tree_print(tree._root, 0, outs);
        return outs;
    }
    AVL<T> operator+=(const AVL<T> &rhs);
    string pre_order();
    string in_order();
    string post_order();

private:
    tree_node<T>* _root;
};

template <typename T>
AVL<T>::AVL(): _root(nullptr){}

template <typename T>
AVL<T>::AVL(const T *sorted_list, int size): _root(nullptr)
{
    if(size > -1)
        _root = tree_from_sorted_list(sorted_list, size);
    else
        _root = tree_from_sorted_list(sorted_list);
}

template <typename T>
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
AVL<T>::AVL(const AVL<T> &copy_me): _root(nullptr)
{
    _root = tree_copy(copy_me._root);
}

template <typename T>
AVL<T>& AVL<T>::operator=(const AVL<T> &rhs)
{
    if(this == &rhs)
        return *this;
    tree_clear(_root);
    _root = tree_copy(rhs._root);
    return *this;
}

template <typename T>
AVL<T>::~AVL()
{
    tree_clear(_root);
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
template <typename T>
bool AVL<T>::insert(const T &insert_me)
{
    bool alreadyFound = tree_search(_root, insert_me);
    if(!alreadyFound)
        tree_insert(_root, insert_me);
    return !alreadyFound;//will return true if the inserted character was not initially found in the tree
}

template <typename T>
bool AVL<T>::erase(const T &target)
{
    return tree_erase(_root, target);
}

template <typename T>
bool AVL<T>::contains(const T &target)const
{
    return tree_search(_root, target);//if found, pointer will be returned this will return true
}

template <typename T>
tree_node<T>* AVL<T>::contains(const T& target, bool& found) const
{
    tree_node<T>* result = tree_search(_root, target);
    found = result != nullptr;
    return result;
}

template <typename T>
void AVL<T>::clear_all()
{
    tree_clear(_root);
}

template <typename T>
bool AVL<T>::empty()const
{
    return (_root == nullptr);
}

template <typename T>
AVL<T> AVL<T>::operator+=(const AVL<T> &rhs)
{
    AVL<T> tree(*this);//copies tree 1 to new tree
    tree_add(tree._root, rhs._root);//adds rhs tree to said tree
    return tree;
}

template <typename T>
string AVL<T>::pre_order()
{
    return pre_order_string(_root);
}

template <typename T>
string AVL<T>::in_order()
{
    return in_order_string(_root);
}

template <typename T>
string AVL<T>::post_order()
{
    return post_order_string(_root);
}

#endif