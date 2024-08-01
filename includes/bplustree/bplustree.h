#ifndef BPLUSTREE_H
#define BPLUSTREE_H
#include <iostream>
#include <iomanip>
#include <string>
#include <assert.h>
#include "btree_array_funcs.h"

using namespace std;

template <class T>
class BPlusTree
{
public:
    class Iterator{
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T>* _it = nullptr, int _key_ptr = 0): it(_it), key_ptr(_key_ptr)
        {
            while((it != nullptr) && (key_ptr > (it->data_count - 1)))//if key is out of bounds
            {
                key_ptr -= it->data_count;
                it = it->next;
            }
        }
        
        T operator *()
        {
            assert(it != nullptr);
            T* valPtr  = it->data + key_ptr;
            return *valPtr;
        }

        operator bool() const
        {
            return it;
        }

        Iterator operator++(int un_used)
        {
            Iterator holder(it, key_ptr++);
            if(key_ptr > (it->data_count - 1))
            {
                it = it->next;
                key_ptr = 0;
            }
            return holder;
        }
        Iterator operator++()
        {
            if(++key_ptr > (it->data_count - 1))
            {
                it = it->next;
                key_ptr = 0; 
            }
            Iterator _it(it, key_ptr);
            return _it;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            BPlusTree* lTree = lhs.it;
            BPlusTree* rTree = rhs.it;
            return (lTree == rTree) && (lhs.key_ptr == rhs.key_ptr);
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {
            return !(lhs == rhs);
        }
        void print_Iterator(){
            if (it){
                cout<<"iterator: ";
                print_array(it->data, it->data_count, key_ptr);
            }
            else{
                cout<<"iterator: NULL, key_ptr: "<<key_ptr<<endl;
            }
        }
        bool is_null()
        {
            return !it;
        }
        void info()
        {
            cout<<endl<<"Iterator info:"<<endl;
            cout<<"key_ptr: "<<key_ptr<<endl;
            cout<<"it: "<<*it<<endl;
        }

    private:
        BPlusTree<T>* it;
        int key_ptr;
    };

    BPlusTree(bool dups = false);
    BPlusTree(T *a, int size, bool dups = false);

    //big three:
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS);

    void copy_tree(const BPlusTree<T>& other);  //copy other into this object
    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node);

    T* insert(const T& entry);   //insert entry into the tree
    void remove(const T& entry);   //remove entry from the tree
    void clear_tree();             //clear this object (delete all nodes etc.)

    bool contains(const T& entry) const; //true if entry can be found
    T& get(const T& entry);              //return a reference to entry
    const T& get(const T& entry) const;   //return a reference to entry
    T& get_existing(const T& entry);     //return a reference to entry
    Iterator find(const T& key);         //return an iterator to this key.
                                         //     NULL if not there.
    Iterator lower_bound(const T& key);  //return first that goes NOT BEFORE
                                         // key entry or next if does not
                                         // exist: >= entry
    Iterator upper_bound(const T& key);  //return first that goes AFTER key
                                         //exist or not, the next entry  >entry

    int size() const;                    //count the number of elements

    bool empty() const;                  //true if the tree is empty

    void print_tree(int level = 0, ostream &outs=cout) const;

    friend ostream& operator<<(ostream& outs, const BPlusTree<T>& print_me)
    {
        print_me.print_tree(0, outs);
        return outs;
    }

    bool is_valid();
    string in_order();
    string pre_order();
    string post_order();

    string in_order_elements();

    Iterator begin();
    Iterator end() const;
    ostream& list_keys(Iterator from = NULL, Iterator to = NULL)
    {
        if (from == NULL) from = begin();
        if (to == NULL) to = end();
        for (Iterator it = from; it != to; it++)
            cout<<*it<<" ";
        return cout;

    }

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                        //true if duplicate keys are allowed
    int data_count;                      //number of data elements
    T data[MAXIMUM + 1];                 //holds the keys
    int child_count;                     //number of children
    BPlusTree* subset[MAXIMUM + 2];      //subtrees
    BPlusTree* next;
    bool is_leaf() const
    {
        return child_count==0;
    }             //true if this is a leaf node

    T* find_ptr(const T& entry);
    const T* find_ptr(const T& entry) const;         //return a pointer to this key.
                                         // NULL if not there.

    //insert element functions
    T* loose_insert(const T& entry);   //allows MAXIMUM+1 data elements in
                                         //   the root
    T* fix_excess(int i);              //fix excess in child i

    //remove element functions:
    void loose_remove(const T& entry);  //allows MINIMUM-1 data elements in the root

    BPlusTree<T>* fix_shortage(int i);  //fix shortage in child i
    // and return the smallest key in this subtree
    BPlusTree<T>* get_smallest_node();
    void get_smallest(T& entry);      //entry := leftmost leaf
    void get_biggest(T& entry);       //entry := rightmost leaf
    void remove_biggest(T& entry);    //remove the biggest child of tree->entry
    void transfer_left(int i);        //transfer one element LEFT from child i
    void transfer_right(int i);       //transfer one element RIGHT from child i
    BPlusTree<T> *merge_with_next_subset(int i); //merge subset i with  i+1

};

template <class T>
BPlusTree<T>::BPlusTree(bool dups): dups_ok(dups), data_count(0), child_count(0), next(nullptr){}

template <class T>
BPlusTree<T>::BPlusTree(T *a, int size, bool dups): dups_ok(dups), data_count(0), child_count(0), next(nullptr)
{
    T* walker = a;
    for(int i = 0; i < size; i++, walker++)
        insert(*walker);
}

//big three:
template <class T>
BPlusTree<T>::BPlusTree(const BPlusTree<T>& other): data_count(0), child_count(0)
{
    copy_tree(other);
}

template <class T>
BPlusTree<T>::~BPlusTree()
{
    clear_tree();
}

template <class T>
BPlusTree<T>& BPlusTree<T>::operator =(const BPlusTree<T>& RHS)
{
    if(this == &RHS)
        return *this;
    clear_tree();
    copy_tree(RHS);
    return *this;
}

template <class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other)
{
    BPlusTree<T>* last_node = nullptr;
    copy_tree(other, last_node);
}
//copy other into this object

template <class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node)
{
    dups_ok = other.dups_ok;
    copy_array(data, other.data, data_count, other.data_count);
    child_count = other.child_count;
    for(int i = child_count; i > 0;)//copy subsets starting right to left
    {
        // cout << "Copying child " << i << ":\n";
        subset[--i] = new BPlusTree<T>(other.dups_ok);
        BPlusTree<T>* otherSubset = other.subset[i];
        subset[i]->copy_tree(*otherSubset, last_node);
        if(otherSubset->is_leaf())//if the subtree is leaf, need to worry about next
        {
            subset[i]->next = last_node;
            last_node = subset[i];
        }
    }
}

template <class T>
T* BPlusTree<T>::insert(const T& entry)
{
    T* inserted = loose_insert(entry);//if not leaf, return this, if it is, loose_insert will either return nullptr or left tree ptr
    // cout << "WE GOOD\n";
    bool wasLeaf = is_leaf();
    bool wasExcess = data_count > MAXIMUM;
    if(wasExcess)
    {
        BPlusTree<T>* holder = new BPlusTree<T>(dups_ok);
        copy_array(holder->data, data, holder->data_count, data_count);
        copy_array(holder->subset, subset, holder->child_count, child_count);
        //making root "empty"
        data_count = 0;
        child_count = 1;
        subset[0] = holder;
        // cout << "CALLING FE FROM MAIN INSERT\n";
        fix_excess(0);//now going to fix excess of holder
    }
    if(wasExcess && wasLeaf && inserted == nullptr)
        inserted = subset[1]->find_ptr(entry);
    return inserted;
}
//insert entry into the tree

template <class T>
void BPlusTree<T>::remove(const T& entry)
{
    loose_remove(entry);
    if(data_count < MINIMUM && !empty())//if root is empty, but has children
    {
        BPlusTree<T>* subTree = subset[0];
        copy_array(data, subTree->data, data_count, subTree->data_count);//copy subtree's data
        copy_array(subset, subTree->subset, child_count, subTree->child_count);//copy subtree's children
        subTree->child_count = 0;
        delete subTree;//delete the in-between b+tree
    }
}
//remove entry from the tree

template <class T>
void BPlusTree<T>::clear_tree()
{
    for(int i = 0; i < child_count; i++)
    {
        subset[i]->clear_tree();
        delete subset[i];
    }
    data_count = 0;
    child_count = 0;
}
//clear this object (delete all nodes etc.)

template <class T>
bool BPlusTree<T>::contains(const T& entry) const
{
    const T* foundPtr = find_ptr(entry);
    return foundPtr != nullptr;
}
//true if entry can be found

template <class T>
T& BPlusTree<T>::get(const T& entry)
{
    T* itemPtr = find_ptr(entry);
    if(itemPtr == nullptr)
    {
        // cout << "NOT FOUND\n";
        return *(insert(entry));
    }
    return *itemPtr;
}
//return a reference to entry

template <class T>
const T& BPlusTree<T>::get(const T& entry) const
{
    T* itemPtr = find_ptr(entry);
    if(itemPtr == nullptr)
        insert_item(entry);
    return *itemPtr;
}
//return a reference to entry

template <class T>
T& BPlusTree<T>::get_existing(const T& entry)
{
    return get(entry);
}
//return a reference to entry

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T& key)
{
    int index = first_ge(data, data_count, key);
    bool isFound = (index < data_count) && (data[index] == key);
    if(is_leaf())
    {
        typename BPlusTree<T>::Iterator it(this, index);
        if(!isFound)
            return end();
        return it;
    }
    return subset[index + isFound]->find(key);
}
//return an iterator to this key. NULL if not there.

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::lower_bound(const T& key)
{
    // typename BPlusTree<T>::Iterator it;
    int index = first_ge(data, data_count, key);
    bool isFound = index < data_count && data[index] == key;
    if(is_leaf())//will give the iterator found or greater than found
        return BPlusTree<T>::Iterator(this, index);//if index == data_count, Iterator ctor will give the next leaf
    return subset[index + isFound]->lower_bound(key);
}
//return first that goes NOT BEFORE key entry or next if does not exist: >= entry

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::upper_bound(const T& key)
{
    // typename BPlusTree<T>::Iterator it;
    int index = first_ge(data, data_count, key);
    bool isFound = index < data_count && data[index] == key;
    if(is_leaf())
        return BPlusTree<T>::Iterator(this, index + isFound);//if found, will go to the next iterator
    return subset[index + isFound]->upper_bound(key);
}
//return first that goes AFTER key exist or not, the next entry  >entry

template <class T>
int BPlusTree<T>::size() const
{
    int size = data_count;
    for(int i = 0; i < child_count; i++)
        size += subset[i]->size();
    return size;
}
//count the number of elements

template <class T>
bool BPlusTree<T>::empty() const
{
    return data_count == 0 && child_count == 0;
}
//true if the tree is empty

template <class T>
void BPlusTree<T>::print_tree(int level, ostream &outs) const
{
    // cout << "CC: " << child_count << endl;
    if(is_leaf())//need to print entire data if leaf
    {
        // cout << "LEAF\n";
        for(int i = data_count; i > 0;)
            outs << right << setw(8 * level) << "|" << data[--i] << "|\n";
        return;
    }
    //print unwanted child first
    subset[data_count]->print_tree(level + 1, outs);
    //after right child printed need to print rest of subset (descending)
    for(int i = data_count; i > 0;)
    {   
        outs << right << setw(8 * level) << "|" << data[--i] << "|\n";
        subset[i]->print_tree(level + 1, outs);
    }
}

template <class T>
bool BPlusTree<T>::is_valid()
{
    return false;
}

template <class T>
string BPlusTree<T>::in_order()//will used linked-list-like property of B+ tree
{
    string str("");
    if(is_leaf())//leaf case
    {
        for(int i = 0; i < data_count; i++)
            str += to_string(data[i]) + "|";
        return str;
    }
    for(int i = 0; i < data_count; i++)//needs to go through data in subset of index before data of index at root
    {
        str += subset[i]->in_order();
        str += to_string(data[i]) + "|";
    }
    str += subset[data_count]->in_order();//prints the rightmost child
    return str;
}

template <class T>
string BPlusTree<T>::pre_order()
{
    string str("");
    if(is_leaf())
    {
        for(int i = 0; i < data_count; i++)
            str += to_string(data[i]) + "|";
        return str;
    }
    for(int i = 0; i < child_count; i++)
    {
        if(i < data_count)
            str += to_string(data[i]) + "|";
        str += subset[i]->pre_order();
    }
    // str += subset[data_count]->pre_order();
    return str;
}

template <class T>
string BPlusTree<T>::post_order()
{
    string str("");
    if(is_leaf())
    {
        for(int i = 0; i < data_count; i++)//print lowest data 
        str += to_string(data[i]) + "|";
    }
    for(int i = 0; i < child_count; i++)//go down to children
    {
        str += subset[i]->post_order();
        if(i > 0)
            str += to_string(data[i - 1]) + "|";//after going to right child, print parent to left
    } 
    return str;
}

template <class T>
string BPlusTree<T>::in_order_elements()
{
    string str("");
    typename BPlusTree<T>::Iterator it;
    for(it = begin(); it != end(); ++it)
        str += to_string(*it) + "|";
    return str;
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::begin()
{
    // BPlusTree<T>* walker = this;
    BPlusTree<T>* walker = get_smallest_node();
    typename BPlusTree<T>::Iterator it(walker, 0);
    return it;
}

template <class T>
typename BPlusTree<T>::Iterator BPlusTree<T>::end() const
{
    typename BPlusTree<T>::Iterator it;
    return it;
}

template <class T>
T* BPlusTree<T>::find_ptr(const T& entry)
{
    int index = first_ge(data, data_count, entry);
    bool isFound = index < data_count && data[index] == entry;
    T* walker = data + index;
    if(is_leaf())
    {
        if(!isFound)
        {
            // cout << "NOT FOUND\n";
            return nullptr;
        }
        return walker;
    }
    return subset[index + isFound]->find_ptr(entry);
}

template <class T>
 const T* BPlusTree<T>::find_ptr(const T& entry) const
{
    int index = first_ge(data, data_count, entry);
    bool isFound = index < data_count && data[index] == entry;
    const T* walker = data + index;
    if(is_leaf())
    {
        if(!isFound)
        {
            // cout << "NOT FOUND\n";
            return nullptr;
        }
        return walker;
    }
    return subset[index + isFound]->find_ptr(entry);
}
//return a pointer to this key. NULL if not there.
//insert element functions

template <class T>
T* BPlusTree<T>::loose_insert(const T& entry)
{
    T* holder = nullptr;
    int index = first_ge(data, data_count, entry);
    bool isFound = index < data_count && data[index] == entry;//will be 1 if first_ge gives a element in data which is equal to entry
    if(is_leaf())
    {
        if(index < data_count && data[index] == entry)
        {
            if(!dups_ok)
                data[index] = entry;//rewrite if dups not ok and a valid index in the array
            else
                data[index] = data[index] + entry;
        }
        else
            insert_item(data, index, data_count, entry);
        if(data_count > MAXIMUM && index >= (data_count / 2))//if inserted on left
            return nullptr;
        return data + index;
    }
    holder = subset[index + isFound]->loose_insert(entry);
    // if(holder == nullptr)
    //     cout << "Holder null\n";
    fix_excess(index + isFound);//need to fix excess in child we inserted in
    if(holder == nullptr)//would be on right tree
    {
        // cout << "DOING THE SHIT\n";
        BPlusTree<T>* subtree = subset[index + isFound + 1];//go to right tree
        holder = subtree->find_ptr(entry);
        if(holder == nullptr)
            cout << "SOMETHING WRONG\n";
    }
    return holder;
}
//allows MAXIMUM+1 data elements in the root

template <class T>
T* BPlusTree<T>::fix_excess(int i)
{
    BPlusTree<T>* subtree = subset[i];
    T detached;
    T* holder = nullptr;
    if(subtree->data_count > MAXIMUM)
    {
        // cout << "FE called\n";
        //make new tree
        BPlusTree<T>* newTree = new BPlusTree<T>(dups_ok);
        //splitting B+ tree
        split(subtree->data, subtree->data_count, newTree->data, newTree->data_count);//give half of data (not including mid) to new tree
        split(subtree->subset, subtree->child_count, newTree->subset, newTree->child_count);//give half of children to new tree
        detach_item(subtree->data, subtree->data_count, detached);//detachs the "old" middle value
        insert_item(data, i, data_count, detached);//puts detached into parent at approprite index of parent
        // print_array(data, data_count, 0);
        insert_item(subset, i + 1, child_count, newTree);//attaching new tree to parent
        // cout << "BRUH\n";
        if(subtree->is_leaf())//if we are fixing excess at leaf, we need to make sure the old and new leaf point to correct things
        {
            // cout << "BRUH2\n" << "CC: " << subtree->child_count << endl;
            insert_item(newTree->data, 0, newTree->data_count, detached);//puts detached into first index of newTree
            holder = newTree->data;
            newTree->next = subtree->next;//new leaf now points to what old leaf did
            subtree->next = newTree;//old leaf now points to new leaf 
        }
        // cout << "DONE\n";
    }
    return holder;//if fix excess not called, holder will be null, if it is holder gives u the ptr to val that move to front of newTree
}
//fix excess in child i

//remove element functions:

template <class T>
void BPlusTree<T>::loose_remove(const T& entry)
{
    T dummy;
    int index = first_ge(data, data_count, entry);
    bool isFound = index < data_count && data[index] == entry;
    if(is_leaf())
    {
        if(isFound)
            delete_item(data, index, data_count, dummy);
        else
            cout << "NOT FOUND\n";
        return;
    }
    if(isFound)
    {
        subset[index]->remove_biggest(data[index]);//will put the new jit into data[index]
        fix_shortage(index);
    }
    else
    {
        subset[index + isFound]->loose_remove(entry);
        fix_shortage(index + isFound);
    }
}
//allows MINIMUM-1 data elements in the root

template <class T>
BPlusTree<T>* BPlusTree<T>::fix_shortage(int i)
{
    BPlusTree<T>* subtree = subset[i];
    BPlusTree<T>* rSubtree = subset[i + 1];
    BPlusTree<T>* lSubtree = subset[i - 1];
    if(subtree->data_count < MINIMUM)
    {
        // cout << "CALLING FS\n";
        if(i < data_count && rSubtree->data_count > MINIMUM)
            transfer_left(i + 1);
        else if(i > 0 && lSubtree->data_count > MINIMUM)
            transfer_right(i - 1);
        else if(i < data_count)
        {
            cout << "Calling merge i\n";
            merge_with_next_subset(i);
        }
        else
        {
            cout << "Calling merge i - 1\n";
            merge_with_next_subset(i - 1);
        }
    }
    return subtree;
}
//fix shortage in child i
// and return the smallest key in this subtree

template <class T>
BPlusTree<T>* BPlusTree<T>::get_smallest_node()
{
    if(is_leaf())
        return this;
    return subset[0]->get_smallest_node();
}

template <class T>
void BPlusTree<T>::get_smallest(T& entry)
{
    BPlusTree<T>* smallestNode = get_smallest_node();//get leftmost node
    T* dataWalker = smallestNode->data;//get left most data from it
    entry = *dataWalker;
}
//entry := leftmost leaf

template <class T>
void BPlusTree<T>::get_biggest(T& entry)
{
    BPlusTree<T>* walker = this;
    while(!walker->is_leaf())
        walker = walker->subset[walker->data_count];//go to right most child
    T* dataWalker = data + data_count - 1;//right most data on right most leaf
    entry = *dataWalker;
}
//entry := rightmost leaf

template <class T>
void BPlusTree<T>::remove_biggest(T& entry)
{
    if(is_leaf())
    {
        detach_item(data, data_count, entry);
        // cout << "BRUH: " << data_count << endl;
        next->data[0] = entry;//giving the left most of next the detached data as well
        return;
    }
    subset[data_count]->remove_biggest(entry);//right subtree
    fix_shortage(data_count);
}
//remove the biggest child of tree->entry

template <class T>
void BPlusTree<T>::transfer_left(int i)
{
    // cout << "Calling TL:\n";
    T detached;
    BPlusTree<T>* detachedPtr;
    BPlusTree<T>* subTree = subset[i];
    BPlusTree<T>* lSubtree = subset[i - 1];
    attach_item(lSubtree->data, lSubtree->data_count, data[i - 1]);//take parent put to left
    // if(subTree->is_leaf())
    delete_item(subTree->data, 0, subTree->data_count, detached);
    data[i - 1] = subTree->data[0];
    if(!subTree->is_leaf())
    {
        delete_item(subTree->subset, 0, child_count, detachedPtr);
        attach_item(lSubtree->subset, lSubtree->child_count, detachedPtr);//take ptr from subtree and attach to end of left subtree
    }
}
//transfer one element LEFT from child i

template <class T>
void BPlusTree<T>::transfer_right(int i)
{
    // cout << "CALLING TR\n";
    T detached;
    BPlusTree<T>* detachedPtr;
    BPlusTree<T>* subTree = subset[i];
    BPlusTree<T>* rSubtree = subset[i + 1];
    // delete_item(data, i, data_count, detached);
    insert_item(rSubtree->data, 0 , rSubtree->data_count, data[i]);//moving parent down to right subtree
    detach_item(subTree->data, subTree->data_count, detached);
    data[i] = detached;
    detach_item(subTree->subset, subTree->child_count, detachedPtr);
    insert_item(rSubtree->subset, 0, rSubtree->child_count, detachedPtr);
}
//transfer one element RIGHT from child i

template <class T>
BPlusTree<T>* BPlusTree<T>::merge_with_next_subset(int i)
{
    T deleted;
    BPlusTree<T>* deletedPtr;
    BPlusTree<T>* subTree = subset[i];
    BPlusTree<T>* rSubtree = subset[i + 1];
    delete_item(data, i , data_count, deleted);//deleting from parent
    if(subTree->is_leaf())//if leaf only worry about nexts
        subTree->next = rSubtree->next;
    else
        attach_item(subTree->data, subTree->data_count, deleted);
    merge(subTree->data, subTree->data_count, rSubtree->data, rSubtree->data_count);
    merge(subTree->subset, subTree->child_count, rSubtree->subset, rSubtree->child_count);//merge subsets, only merges when child not leaf
    // delete_item(data, i , data_count, deleted);//deleting from parent
    delete_item(subset, i + 1, child_count, deletedPtr);//deleting rSubtree from subset
    delete deletedPtr;//freeing space, no need to make child_count 0 because merge already does that
    // cout << "\nAfter merge\n" << *this << endl;
    return subTree;
}
//merge subset i with  i+1

#endif