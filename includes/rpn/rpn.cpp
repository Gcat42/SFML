#include "rpn.h"

RPN::RPN(){}

RPN::RPN(regMap fieldMap, vectormmap table, Queue<Token*> postfix): _field_map(fieldMap), _table(table), _postfix(postfix){}

void RPN::set_postfix(Queue<Token*> postfix)
{
    _postfix = postfix;
}

void RPN::set_maps(regMap fieldMap, vectormmap table)
{
    _field_map = fieldMap;
    _table = table;
}

vectorlong RPN::operator()(bool unused)
{
    Token* qWalker;
    Token* popped1;
    Token* popped2;
    regMap* mapPtr = &(_field_map);
    vectormmap* mmapPtr = &(_table);
    Stack<Token*> rpn_stack;
    typename Queue<Token*>::Iterator it;
    for(it = _postfix.begin(); it != _postfix.end(); ++it)
    {
        qWalker = *it;
        switch(qWalker->type())
        {
            case SYMBOL:
                rpn_stack.push(*it);
                break;
            case RELATIONAL:
                // cout << "calling relational\n";
                popped1 = rpn_stack.pop();//popping tokenStr
                popped2 = rpn_stack.pop();
                // cout << "Yuh\n";
                assert(popped1->type() == SYMBOL && popped2->type() == SYMBOL);
                rpn_stack.push(new Solution(popped2, popped1, qWalker, mapPtr, mmapPtr));
                break;
            case LOGICAL:
                popped1 = rpn_stack.pop();//popping solutions
                popped2 = rpn_stack.pop();
                assert(popped1->type() == SOLUTION && popped2->type() == SOLUTION);
                rpn_stack.push(new Solution(popped2, popped1, qWalker, mapPtr, mmapPtr));
                break;
        }
    }
    //now final solution vector
    popped1 = rpn_stack.pop();
    assert(popped1->type() == SOLUTION);
    return popped1->get_solution_vect();
}

// Token* RPN::calc_solution(const Token* left, const Token* right, const Token* op)
// {

// }