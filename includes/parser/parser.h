#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <iomanip>
#include <string.h>
#include <vector>
#include "../bplustree/multimap.h"
#include "../token_stuff/tokenizer/stokenize.h"
#include "../token_stuff/token/token.h"
#include "../token_stuff/token/child_tokens.h"
#include "../token_stuff/tokenizer/constants.h"
#include "typedefs.h"
#include "../stack_queue/queue/MyQueue.h"
#include "../token_stuff/matrix functions/matrix_functions.h"

using namespace std;

class Parser
{
    public:
        Parser();
        Parser(char inputStr[]);
        // Parser(const string& inputStr);
        mmap_ss parse_tree();
        void set_string(char str[]);

        void print_vect();
        bool is_valid();
    private:
        void make_input_vector();
        void make_table();
        TOKEN_TYPES get_enum_val(const string& str);
        bool insert_to_parse_tree(mmap_ss& parseTree, const string& str, TOKEN_TYPES type, int state);
        // bool insert_token_into_queue(const string& str, TOKEN_TYPES tokenType);
        string _input_str;
        vectorstr token_vect;
        //adjacency matrix
        STokenizer stk;
        static int _table[MAX_ROWS][MAX_COLUMNS];
        bool _is_valid;
};

#endif