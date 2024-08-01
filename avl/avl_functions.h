#ifndef AVL_FUNCTIONS_H
#define AVL_FUNCTIONS_H
#include <iostream>
#include <iomanip>
#include <string.h>
#include <assert.h>
#include <cmath>
#include "../tree_node/tree_node.h"

using namespace std;

template <typename T>
void tree_insert(tree_node<T>* &root, const T& insert_me);

template <typename T>
tree_node<T>* tree_search(tree_node<T>* root, const T& target);

template <typename T>
tree_node<T>* tree_search_nonrecursive(tree_node<T>* root, const T& target);

template <typename T>
bool tree_search(tree_node<T>* root, const T& target, tree_node<T>* &found_ptr);

template<typename T>
void tree_print(tree_node<T>* root, int depth=0, ostream& outs=cout);

template<typename T> //prints detailes info about each node
void tree_print_debug(tree_node<T>* root, int depth=0, ostream& outs=cout);

template <typename T> //clear the tree
void tree_clear(tree_node<T>* &root);

template <typename T> //erase target from the tree
bool tree_erase(tree_node<T>*& root, const T& target);

template <typename T> //erase rightmost node from the tree -> max_value
void tree_remove_max(tree_node<T>* &root, T& max_value);


template <typename T> //print in_order
void in_order(tree_node<T>* root,ostream& outs=cout);

template <typename T> //print pre_order
void  pre_order(tree_node<T>* root,ostream& outs=cout);

template <typename T> //print post_order
void  post_order(tree_node<T>* root,ostream& outs=cout);

template <typename T> //string in_order
string in_order_string(tree_node<T>* root);

template <typename T> //string pre_order
string pre_order_string(tree_node<T>* root);

template <typename T> //string post_order
string post_order_string(tree_node<T>* root);


template <typename T> //return copy of tree pointed to by root
tree_node<T>* tree_copy(tree_node<T>* root);

template <typename T> //Add tree src to dest
void tree_add(tree_node<T>* & dest, const tree_node<T>* src);

template <typename T> //sorted array of ints -> tree
tree_node<T>* tree_from_sorted_list(const T* a);

template <typename T> // sorted array -> tree
tree_node<T>* tree_from_sorted_list(const T* a, int size);

// ---------------- ROTATIONS --------------------------
template <typename T>
tree_node<T>* rotate_right(tree_node<T>* &root);

template <typename T>
tree_node<T>* rotate_left(tree_node<T>* &root);

template <typename T>
tree_node<T>* rotate(tree_node<T>* & root); //decide which rotate is needed based on balance factor


//
//
//FUNCTION DEFS
//
//
//

template <typename T>
void tree_insert(tree_node<T>* &root, const T& insert_me)
{
    int bFactor;
    if(root == nullptr)
    {
        root = new tree_node<T>(insert_me);
        return;
    }
    if(insert_me > root->_item)//no duplicates should go into avl, thus no equals case
        tree_insert(root->_right, insert_me);
    else if(insert_me < root->_item)
        tree_insert(root->_left, insert_me);
    //update height
    root->update_height();
    bFactor = abs(root->balance_factor());
    if(bFactor > 1)
        rotate(root);
}

template <typename T>
tree_node<T>* tree_search(tree_node<T>* root, const T& target)
{
    if(root == nullptr || target == root->_item)
        return root;
    if(target > root->_item)
        root = tree_search(root->_right, target);
    else
        root = tree_search(root->_left, target);
    return root;
}

template <typename T>
tree_node<T>* tree_search_nonrecursive(tree_node<T>* root, const T& target)
{
    tree_node<T>* left;
    tree_node<T>* right;
    while(root != nullptr)
    {
        left = root->_left;
        right = root->_right;
        if(root->_item == target)
            return root;
        else if(target > root->_item)
        {
            if(right == nullptr)
                return nullptr;
            else
                root = right;
        }
        else
        {
            if(left == nullptr)
                return nullptr;
            else
                root = left;
        }
    }
    return root;
}

template <typename T>
bool tree_search(tree_node<T>* root, const T& target, tree_node<T>* &found_ptr)
{
    if(root == nullptr  || root->_item == target)
    {
        found_ptr = root;
        return found_ptr != nullptr;
    }  
    if(target > root->_item)
        tree_search(root->_right, target, found_ptr);
    else
        tree_search(root->_left, target, found_ptr);
    return found_ptr != nullptr;
}

template<typename T>
void tree_print(tree_node<T>* root, int depth, ostream& outs)
{
    if(root == nullptr)
        return;
    tree_print(root->_right, depth + 1, outs);//increases spaces by one every recursice call
    outs <<  right << setw(depth  * 4) << *root << endl;
    tree_print(root->_left, depth + 1, outs);//increases spaces by one every recursice call
    return;
}

template<typename T> //prints detailes info about each node
void tree_print_debug(tree_node<T>* root, int depth, ostream& outs)
{
    if(root == nullptr)
        return;
    tree_print_debug(root->_right, depth + 1, outs);//increases spaces by one every recursive call
    for(int i = 0; i < depth; i++)//use tabs because setw is too weird for tree_debug
        outs << "\t";
    outs << "[" << root->_item << " : " << root->_height
    << " (" << root->balance_factor() << ")]\n";
    tree_print_debug(root->_left, depth + 1, outs);//increases spaces by one every recursive call
    return;
}

template <typename T> //clear the tree
void tree_clear(tree_node<T>* &root)
{
    if(root == nullptr)
        return;
    tree_clear(root->_right);//goes all the way to right most child
    tree_clear(root->_left);//goes down left most child from right most child node (node gotten from above)
    delete root;//deletes the node
    root = nullptr;//sets the arm to nullptr (just for when we delete everything and the top root should be nullptr)
}


template <typename T> //erase target from the tree
bool tree_erase(tree_node<T>*& root, const T& target)
{
    //use search_tree
    tree_node<T>* holder;
    bool erased = false;
    int bFactor;
    if(root == nullptr)//target not found
        return erased;
    if(target == root->_item)
    {
        if(root->_left == nullptr)
        {
            holder = root;//hold the node being pointed at
            root = root->_right;//the the arm no points at root's right
            delete holder;//deleting old root
        }
        else//if left arm exists
            tree_remove_max(root->_left, root->_item);//remove the maximum value left of the root
        if(root != nullptr)
        {
            root->update_height();//makes sure to update height, since I faced a bug in my testB
                                //remove_max does not update height, when changes from bottom should change the height of the top
            bFactor = abs(root->balance_factor());
            if(bFactor > 1)
                rotate(root);
        }
        return true;
    }
    else if(target > root->_item)
        erased = tree_erase(root->_right, target);//if the target is to the right, keep going right recursively
    else
        erased = tree_erase(root->_left, target);//if the target is to the left, keep going left reursively til you get to target
    root->update_height();
    bFactor = abs(root->balance_factor());
    if(bFactor > 1)
        rotate(root);
    return erased;
}

template <typename T> //erase rightmost node from the tree -> max_value
void tree_remove_max(tree_node<T>* &root, T& max_value)
{
    tree_node<T>* holder;
    int bFactor;
    assert(root != nullptr); //I don't know if I should assert or not
    // if(root == nullptr)
    //     return;
    if(root->_right == nullptr)
    {
        max_value = root->_item;
        holder = root;
        // delete root;
        if(root->_left != nullptr)
            root = root->_left;
        else
            root = nullptr;
        delete holder;
        return;
    }
    tree_remove_max(root->_right, max_value);
    root->update_height();
    bFactor = abs(root->balance_factor());
    if(bFactor > 1)
        rotate(root);
    return;
}


template <typename T> //print in_order
void in_order(tree_node<T>* root,ostream& outs)
{
    if(root == nullptr)
        return;
    in_order(root->_left, outs);
        outs << *root << " ";
    in_order(root->_right, outs);
    return;
}


template <typename T> //print pre_order
void  pre_order(tree_node<T>* root,ostream& outs)
{
    if(root == nullptr)
        return;
    outs << *root << " ";
    pre_order(root->_left, outs);
    pre_order(root->_right, outs);
    return;
}


template <typename T> //print post_order
void  post_order(tree_node<T>* root, ostream& outs)
{
    if(root == nullptr)
        return;
    post_order(root->_left, outs);
    post_order(root->_right, outs);
    outs << *root << " ";
    return;
}


template <typename T> //string in_order
string in_order_string(tree_node<T>* root)
{
    string str("");
    if(root == nullptr)
        return "";
    str += in_order_string(root->_left);
    str += root->node_string();
    str += in_order_string(root->_right);
    return str;
}


template <typename T> //string pre_order
string pre_order_string(tree_node<T>* root)
{
    string str("");
    if(root == nullptr)
        return "";
    str += root->node_string();
    str += pre_order_string(root->_left);
    str += pre_order_string(root->_right);
    return str;
}


template <typename T> //string post_order
string post_order_string(tree_node<T>* root)
{
    string str("");
    if(root == nullptr)
        return "";
    str += post_order_string(root->_left);
    str += post_order_string(root->_right);
    str += root->node_string();
    return str;
}



template <typename T> //return copy of tree pointed to by root
tree_node<T>* tree_copy(tree_node<T>* root)
{
    if(root == nullptr)//when we get to end of tree we need to start going back
        return root;//also makes the copied tree a nullptr if the root is a nullptr!
    return new tree_node<T>(root->_item, tree_copy(root->_left), tree_copy(root->_right));
    //we will go all the way to the left, then start going back up one by one, go to right, repeat process until we climb to the root
}


template <typename T> //Add tree src to dest
void tree_add(tree_node<T>* & dest, const tree_node<T>* src)
{
    if(src == nullptr)
        return;
    tree_insert(dest, src->_item);//does pre-order traversal through tree 2 and just adds each traversed item to tree 1
    tree_add(dest, src->_left);
    tree_add(dest, src->_right);
    return;
}


template <typename T> //sorted array of ints -> tree
tree_node<T>* tree_from_sorted_list(const T* a)//honestly don't know how to do this, becuase I don't know the end of the list
{

    return nullptr;
}


template <typename T> // sorted array -> tree
tree_node<T>* tree_from_sorted_list(const T* a, int size)
{
    tree_node<T>* root = nullptr;
    if(size < 1)//if size is 0 or negative, size shouldn't be negative
        return nullptr;
    int halfSize = size / 2;
    const T* midPoint = a + halfSize;
    root = new tree_node<T>(*midPoint, tree_from_sorted_list(a, halfSize), tree_from_sorted_list(midPoint + 1, size - halfSize - 1));
    root->update_height();
    return root;
}

template <typename T>
tree_node<T>* rotate_right(tree_node<T>* &root)
{
    tree_node<T>* left = root->_left;
    root->_left = left->_right;
    root->update_height();
    left->_right = root;
    root = left;
    root->update_height();
    return root;
}

template <typename T>
tree_node<T>* rotate_left(tree_node<T>* &root)
{
    tree_node<T>* right = root->_right;
    root->_right = right->_left;
    root->update_height();
    right->_left = root;
    root = right;
    root->update_height();
    return root;
}

template <typename T>
tree_node<T>* rotate(tree_node<T>* & root)
{
    int bFactor1 = root->balance_factor();
    int bFactor2;
    if(bFactor1 > 0)//leaning hard left
    {
        bFactor2 = root->_left->balance_factor();
        if(bFactor2 < 0)//leaning right
            rotate_left(root->_left);
        return rotate_right(root);
    }
    else//leaning hard right
    {
        bFactor2 = root->_right->balance_factor();
        if(bFactor2 > 0)//leaning left
            rotate_right(root->_right);
        return rotate_left(root);  
    }

} //decide which rotate is needed based on balance factor
#endif