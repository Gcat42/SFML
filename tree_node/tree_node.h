#ifndef TREE_NODE_H
#define TREE_NODE_H
#include <iostream>
#include <iomanip>
#include <string.h>

using namespace std;

template <typename T>
struct tree_node{
    T _item;
    tree_node<T>* _left;
    tree_node<T>* _right;
    int _height;

    int balance_factor();

    int height();

    int update_height();

    tree_node(T item=T(), tree_node* left=nullptr, tree_node* right=nullptr);

    string node_string();

    template <typename U>
    friend ostream& operator <<(ostream& outs, const tree_node<U>& t_node);
};

//balance factor = height of the left subtree 
//                        - the height of the right subtree
//a NULL child has a height of -1
//a leaf has a height of 0
template <typename T>
int tree_node<T>::balance_factor()
{
    int lHeight, rHeight;
    if(_left == nullptr)
        lHeight = -1;
    else
        lHeight = _left->_height;
    if(_right == nullptr)
        rHeight = -1;
    else
        rHeight = _right->_height;
    return lHeight - rHeight;
}

// Height of a node is 1 + height of the "taller" child
//A leaf node has a height of zero: 1 + max(-1,-1)
template <typename T>
int tree_node<T>::height()
{
    int lHeight, rHeight;
    if(_left == nullptr)
        lHeight = -1;
    else
        lHeight = _left->_height;
    if(_right == nullptr)
        rHeight = -1;
    else
        rHeight = _right->_height;
    return max(lHeight, rHeight) + 1;
}

//set the _height member variable (call height();)
template <typename T>
int tree_node<T>::update_height()
{
    _height = height();
    return _height;
}

//don't forget to set the _height.
template <typename T>
tree_node<T>::tree_node(T item, tree_node* left, tree_node* right): _item(item), _left(left), _right(right)
{
    update_height();
}

template <typename T>
string tree_node<T>::node_string()
{
    string str = "[";
    str += to_string(_item);
    str += "]";
    return str;
}

template <typename U>
ostream& operator <<(ostream& outs, const tree_node<U>& t_node)
{
    outs << "[" << t_node._item << "]";
    return outs;
}


#endif