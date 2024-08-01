#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H
#include <iostream>
#include <string.h>
#include <vector>
#include "../token_stuff/token/token.h"
#include "../token_stuff/token/child_tokens.h"
#include "../token_stuff/tokenizer/constants.h"
#include "../table/typedefs.h"
#include "../stack_queue/queue/MyQueue.h"
#include "../stack_queue/stack/MyStack.h"

class ShuntingYard
{
    public:
        ShuntingYard();
        ShuntingYard(const Queue<Token*>& infix);
        ShuntingYard(const vectorstr& infix_vector);
        // ~ShuntingYard();//will deal with this one later, need to delete dynamic token vars
        Queue<Token*> postfix();//will give postfix queue from _infix variable
        Queue<Token*> postfix(const Queue<Token*>& infix);//will translate infix queue to _infix and call empty postfix
        Queue<Token*> postfix(const vectorstr& infix_vector);//will convert vectorstr to _infix and call empty postfix
        //setting infix
        void set_infix(const vectorstr& infix_vector);//will change infix exp. for shuntingyard for outside purposes (abstraction)
        void print_infix();
    private:
        void convert_infix(const vectorstr& infix_vector);
        Token* string_to_token(const string& str);
        int get_token_type(const string& str);
        Queue<Token*> _infix;
};


#endif