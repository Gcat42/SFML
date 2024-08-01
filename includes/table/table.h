#ifndef TABLE_H
#define TABLE_H
#include <iostream>
#include <iomanip>
#include <string.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <assert.h>
#include "../binary_files/file_record.h"
#include "typedefs.h"
#include "../shunting_yard/shunting_yard.h"
#include "../rpn/rpn.h"
#include "../bplustree/map.h"
#include "../bplustree/multimap.h"
#include "../stack_queue/queue/MyQueue.h"
#include "../stack_queue/stack/MyStack.h"
#include "../token_stuff/token/token.h"
#include "../token_stuff/token/child_tokens.h"
#include "../token_stuff/tokenizer/constants.h"
#include "../stl_utils/vector_utilities.h"
using namespace std;

class Table
{
    public:
        Table();
        Table(const string& fileName, const vectorstr& fieldNames);
        Table(const string& fileName);
        //Big 3
        Table(const Table& copyMe);
        Table& operator =(const Table& RHS);
        ~Table();
        //insertion
        void insert_into(const vectorstr& v);

        //print functions
        void print_records(ostream& outs);
        friend ostream& operator <<(ostream& outs, Table print_me);
        //select functions
        Table select_all();
        Table select_all(const vectorstr& fieldNames);
        Table select(const vectorstr& fieldNames, const string& field, const string& op, const string& key);
        Table select(const vectorstr& fieldNames, const Queue<Token*> post);
        Table select(const vectorstr& fieldNames, const vectorstr& expression);
        vectorlong select_recnos();
        vectorstr get_field_names();
    private:
        //making temp table
        Table make_temp_table(const vectorstr& fieldNames, const vectorlong& recnos);//makes a table with given recnos and fieldnames
        vectorlong get_insert_order(const vectorstr& fieldNames);//gives the indexes in order of fieldNames given in vect
        //for data file
        static long serial;
        string table_name;
        //file for field names
        string table_field_names;
        vectorstr field_names;
        regMap _field_map;
        //holds all data (mmap)
        vectormmap _table;
        //fstream stuff
        fstream f;
        long lastRecno;
        //select stuff
        vectorlong select_mem;
};
#endif