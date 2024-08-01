#ifndef RPN_H
#define RPN_H
#include <iostream>
#include <string.h>
#include <vector>
#include "../table/typedefs.h"
#include "../bplustree/map.h"
#include "../bplustree/multimap.h"
#include "../token_stuff/token/token.h"
#include "../token_stuff/token/child_tokens.h"
#include "../stack_queue/queue/MyQueue.h"
#include "../stack_queue/stack/MyStack.h"

using namespace std;

class RPN
{
    public:
        RPN();
        RPN(regMap fieldMap, vectormmap table, Queue<Token*> postfix);

        //setter
        void set_postfix(Queue<Token*> postfix);
        void set_maps(regMap fieldMap, vectormmap table);
        //big boy functions (doing the actual work)
        vectorlong operator()(bool unused = false);
    private:
        // Token* calc_solution(const Token* left, const Token* right, const Token* op);
        Queue<Token*> _postfix;
        regMap _field_map;
        vectormmap _table;
};

#endif