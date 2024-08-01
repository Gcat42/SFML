#ifndef SQL_H
#define SQL_H
#include "../table/table.h"
#include "../table/typedefs.h"
#include "../parser/parser.h"
#include <vector>
#include <string.h>
#include "../token_stuff/tokenizer/constants.h"
using namespace std;

class SQL
{
    public:
        SQL();
        Table command(const string& str);
        vectorlong select_recnos();
        bool is_valid();
        TOKEN_TYPES get_command_type();
    private:
        void update_info(const string& str);
        void string_to_cstr(char cStr[], const string& str);//converts string and puts result into cStr, need cStr to be same size
        Table follow_instructions();
        Table call_select();
        Table call_make();
        Table call_insert();
        Parser psr;
        mmap_ss instruction;
        vectorlong selectmem;
        TOKEN_TYPES command_type;
};

#endif