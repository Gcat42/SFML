#ifndef LINKEDLISTFUNCTIONSTEMPLATED_H
#define LINKEDLISTFUNCTIONSTEMPLATED_H
#include <iostream>
#include <assert.h>
#include "../node/node.h"
using namespace std;

//Linked List General Functions:
template <typename T>
void _print_list(node<T>* head);

//Linked List General Functions:
template <typename T>
ostream& _print_list(ostream& outs, node<T>* head);

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head);

//recursive fun! :)
template <typename T>
ostream& _print_list_backwards(ostream& outs, node<T>* head);

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key);


template <typename T>
node<T>* _insert_head(node<T> *&head, T insert_this);

//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this);

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T insert_this);

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this);

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this);

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head);

//duplicate the list, return pointer to last node in dest... 
//     use this function in your queue big three 
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src);



//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head);

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos);

template <typename T>
void _print_addresses(node<T>* head);

//
//
//IMPLEMENTED FUNCTIONS
//
//

template <typename T>
void _print_list(node<T>* head)
{
    node<T>* walker = head;
    if(head == nullptr)
        cout << "EMPTY LIST\n";
    while(walker != nullptr)
    {
        cout << "<-[" << walker->_item << "]-> ";
        walker = walker->_next;
    }
    cout << endl;
}

//recursive fun! :)
template <typename T>
void _print_list_backwards(node<T> *head)
{
    cout << "From back to front:\n";
    if(head == nullptr)
    {
        cout << "EMPTY LIST\n";
        return;
    }
    node<T>* walker = head;
    while(walker->_next != nullptr)
        walker = walker->_next;
    while(walker != nullptr)
    {
        cout << "<-["<< walker->_item << "]-> ";
        walker = walker->_prev;
    }
    cout << endl;
}

//return ptr to key or NULL
template <typename T>
node<T>* _search_list(node<T>* head, T key)
{
    node<T>* walker = head;
    while(walker != nullptr)
    {
        if(walker->_item == key)
            return walker;
        walker = walker->_next;
    }
    return nullptr;
}


template <typename T>
node<T>* _insert_head(node<T> *&head, T insert_this)
{
    node<T>* newHead = new node<T>(insert_this, head);
    if(head != nullptr)
        head->_prev = newHead;
    head = newHead;
    return head;
}

//insert after ptr: insert head if marker null
template <typename T>
node<T>* _insert_after(node<T>*& head, node<T> *after_this, T insert_this)
{
    if(head == nullptr)
        return _insert_head(head, insert_this);
    node<T>* walker = head;
    node<T>* nextNode;
    while(walker != after_this)//gets to after_this
    {
        assert(walker != nullptr);//if not found in linked list assert
        walker = walker->_next;
    }
    after_this->_next = new node<T>(insert_this, after_this->_next, after_this);
    walker = after_this->_next;//now becomes inserted node
    nextNode = walker->_next;
    if(nextNode != nullptr)
        nextNode->_prev = walker;
    return walker;
}

//insert before ptr: insert head if marker null
template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T insert_this)
{
    if(head == nullptr || head == before_this)
        return _insert_head(head, insert_this);
    node<T>* walker = head;
    node<T>* prevNode;
    while(walker != before_this)//gets to before this
    {
        assert(walker != nullptr);//if not found in linked list assert
        walker = walker->_next;
    }
    before_this->_prev = new node<T>(insert_this, before_this, before_this->_prev);
    walker = before_this->_prev;
    prevNode = walker->_prev;
    prevNode->_next = walker;
    return walker;
}

//ptr to previous node
template <typename T>
node<T>* _previous_node(node<T>* prev_to_this)
{
    assert(prev_to_this != nullptr);
    return prev_to_this->_prev;
}

//delete, return item
template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this)
{
    assert(head != nullptr || delete_this != nullptr);
    T item = delete_this->_item;
    node<T>* walker =  head;
    while(walker != delete_this)//checks if delete_this is in linked list
    {
        assert(walker != nullptr);
        walker = walker->_next;
    }
    node<T>* prevNode = delete_this->_prev;
    node<T>* afterNode = delete_this->_next;
    if(delete_this->_next != nullptr)//case when deleted node is not at end of linked list
    {
        afterNode->_prev = prevNode;
        if(head == delete_this)//if deleting head
            head = head->_next;//works for case when head is only node
        else
            prevNode->_next = afterNode;//if not, prevNode needs to point forwards at the deleted node's next
    }
    else
    {
        if(head == delete_this)
            head = nullptr;
        else
            prevNode->_next = afterNode;
    }
    delete delete_this;
    return item;
}

//duplicate the list...
template <typename T>
node<T>* _copy_list(node<T>* head)
{
    if(head == nullptr)
        return head;
    node<T>* newHead = nullptr;
    //getting two walkers; one for og list and one for new list
    node<T>* walker = head;//walks through og list
    node<T>* newWalker = newHead;//walks through duplicate list
    // do
    // {
    //     walker = walker->_next;//moves to the next item first since head was already copied
    //     newWalker = _insert_after(newHead, newWalker, walker->_item);//inserts after and moves walker to that inserted node
    // } while(walker != nullptr);
    while(walker != nullptr)
    {
        newWalker = _insert_after(newHead, newWalker, walker->_item);
        walker = walker->_next;
    }
    return newHead;
}

//duplicate the list, return pointer to last node in dest... 
//     use this function in your queue big three 
template <typename T>
node<T> *_copy_list(node<T> *&dest, node<T> *src)
{
    _clear_list(dest);//NO MALLOC ALLOWED
    node<T>* srcWalker = src;
    node<T>* destWalker = dest;
    if(srcWalker == nullptr)
    {
        destWalker = nullptr;
        return nullptr;
    }
    while(srcWalker != nullptr)
    {
        destWalker = _insert_after(dest, destWalker, srcWalker->_item);
        srcWalker = srcWalker->_next;
    }
    return destWalker;//this should be last node inserted
}



//delete all the nodes
template <typename T>
void _clear_list(node<T>*& head)
{
    while(head != nullptr)
        _delete_node(head, head);
    head = nullptr;
}

//_item at this position
template <typename T>
T& _at(node<T>* head, int pos)
{
    assert(head != nullptr);
    T* itemPtr;
    node<T>* walker = head;
    for(int i= 0; i < pos; i++)
    {
        assert(walker != nullptr);
        walker = walker->_next;
    }
    assert(walker != nullptr);
    itemPtr = &(walker->_item);
    return *itemPtr;
}

template <typename T>
void _print_addresses(node<T>* head)
{
    node<T>* walker = head;
    while(walker != nullptr)
    {
        cout << "[" << walker << "]-> ";
        walker = walker->_next;
    }
    cout << endl;
}

template <typename T>
ostream& _print_list(ostream& outs, node<T>* head)
{
    node<T>* walker = head;
    while(walker != nullptr)
    {
        outs << "<-[" << walker->_item << "]-> ";
        walker = walker->_next;
    }
    return outs;
}

template <typename T>
ostream& _print_list_backwards(ostream& outs, node<T>* head)
{
    node<T>* walker = head;
    while(walker->_next != nullptr)
        walker = walker->_next;
    while(walker != nullptr)
    {
        outs << "<-["<< walker->_item << "]-> ";
        walker = walker->_prev;
    }
    return outs;
}


#endif