#include "shunting_yard.h"

ShuntingYard::ShuntingYard(){}

ShuntingYard::ShuntingYard(const Queue<Token*>& infix): _infix(infix){}

ShuntingYard::ShuntingYard(const vectorstr& infix_vector)
{
    convert_infix(infix_vector);//will set _infix var
}

// ShuntingYard::~ShuntingYard()
// {

// }
//will deal with this one later, need to delete dynamic token vars

Queue<Token*> ShuntingYard::postfix()
{
    Queue<Token*> result;
    Stack<Token*> opStack;
    Token* qWalker;
    Token* topStack;
    int qPrec;
    typename Queue<Token*>::Iterator it;
    for(it = _infix.begin(); it != _infix.end(); ++it)
    {
        qWalker = *it;
        switch(qWalker->type())
        {
            case SYMBOL:
                // cout << "Symbol push\n";
                result.push(*it);
                break;
            case RELATIONAL:
                // cout << "Relational push\n";
                opStack.push(*it);//don't have to worry about relationals on top of relationals
                break;
            case LOGICAL://have to worry about precedence (and/or with relationals)
                // cout << "Logical push\n";
                qPrec = qWalker->get_precedence();
                while(!opStack.empty() && qPrec <= (opStack.top())->get_precedence())//if stack empty won't call get_prec
                    result.push(opStack.pop());
                opStack.push(qWalker);
                break;
            case LPAREN:
                // cout << "LPAREN push\n";
                opStack.push(qWalker);
                break;
            case RPAREN:
                // cout << "RPAREN MOMENT\n";
                topStack = opStack.top();
                int topStackPrec = topStack->get_precedence();
                while(topStackPrec != LPAREN)
                {
                    result.push(opStack.pop());
                    topStack = opStack.top();
                    topStackPrec = topStack->get_precedence();
                }
                opStack.pop();//popping lparen
                break;
        }
    }
    while(!opStack.empty())
        result.push(opStack.pop());
    // result.print_pointers();
    return result;
}
//will give postfix queue from _infix variable

Queue<Token*> ShuntingYard::postfix(const Queue<Token*>& infix)
{
    _infix = infix;
    return postfix();
}
//will translate infix queue to _infix and call empty postfix

Queue<Token*> ShuntingYard::postfix(const vectorstr& infix_vector)
{
    convert_infix(infix_vector);
    return postfix();
}
//will convert vectorstr to _infix and call empty postfix

void ShuntingYard::set_infix(const vectorstr& infix_vector)
{
    convert_infix(infix_vector);
}
//will change infix exp. for shuntingyard for outside purposes (abstraction)

void ShuntingYard::convert_infix(const vectorstr& infix_vector)
{
    Queue<Token*> infix_queue;
    Token* tokPtr;
    for(int i = 0; i < infix_vector.size(); i++)
    {
        tokPtr = string_to_token(infix_vector[i]);
        infix_queue.push(tokPtr);
    }
    //copy this queue to the _infix queue
    _infix = infix_queue;
}

Token* ShuntingYard::string_to_token(const string& str)
{
    int token_type = get_token_type(str);
    switch(token_type)
    {
        case RELATIONAL:
            return new Relational(str);
        case LOGICAL:
            return new Logical(str);
        case LPAREN:
            return new LParen();
        case RPAREN:
            return new RParen();
        case SYMBOL:
            return new TokenStr(str);
        default:
            cout << "Should not be ever called\n";
            return new Token(str, TOKEN_UNKNOWN);
    }
}

int ShuntingYard::get_token_type(const string& str)
{
    if(str == "=" || str == ">" || str == "<" || str == ">=" || str == "<=")
        return RELATIONAL;
    else if(str == "and" || str == "or")
        return LOGICAL;
    else if(str == "(")
        return LPAREN;
    else if(str == ")")
        return RPAREN;
    else
        return SYMBOL;
}

void ShuntingYard::print_infix()
{
    _infix.print_pointers();
}