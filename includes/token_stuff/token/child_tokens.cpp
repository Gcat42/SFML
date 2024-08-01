#include "child_tokens.h"

//helper function
string to_lower(const string& str)
{
    string lowerStr("");
    char c;
    for(int i = 0; i < str.length(); i++)
    {
        c = str[i];
        if(isalpha(c))
            c = tolower(c);
        lowerStr += c;
    }
    return lowerStr; 
}

int first_ge(const vectorlong& v, long entry)
{
    for(int i = 0; i < v.size(); i++)
    {
        if(entry <= v[i])
            return i;
    }
    return v.size();
}

// vectorlong& operator +=(vectorlong& result, vectorlong& addMe)
// {
//     for(int i = 0; i < addMe.size(); i++)
//         result += addMe[i];
//     return result;
// }

//tokenstr functions
TokenStr::TokenStr(): Token("*", TOKEN_ALPHA), _token_type(ALL), precedence(SYMBOL){}

TokenStr::TokenStr(const string& str): Token(str, TOKEN_ALPHA), precedence(SYMBOL)
{
    _token_type = calc_token_type();
}

TOKEN_TYPES TokenStr::calc_token_type()
{
    string str = to_lower(token_str());
    if(str == "select")
        return SELECT;
    else if(str == "where")
        return WHERE;
    else if(str == "insert")
        return INSERT;
    else if(str == "into")
        return INTO;
    else if(str == "from")
        return FROM;
    else if(str == "*")
        return ALL;
    else
        return SYMBOL;
}

int TokenStr::type() const
{
    return _token_type;
}

int TokenStr::get_precedence()
{
    return precedence;
}

void TokenStr::print(ostream& outs) const
{
    outs << "{ " << token_str() << " : " << precedence << " }";
}

ostream& operator <<(ostream& outs, const TokenStr& t)
{
    t.print(outs);
    return outs;
}


//Relational

Relational::Relational(): Token("=", TOKEN_OPERATOR), _token_type(RELATIONAL), precedence(RELATIONAL)
{
    _op_type = calc_op_type("=");
}

Relational::Relational(const string& str): Token(str, TOKEN_OPERATOR), _token_type(RELATIONAL), precedence(RELATIONAL)
{
    _op_type = calc_op_type(str);
}

int Relational::type() const
{
    return RELATIONAL;
}

int Relational::get_precedence()
{
    return precedence;
}

void Relational::print(ostream& outs) const
{
    outs << "{ " << token_str() << " : " << precedence << " }";
}

ostream& operator <<(ostream& outs, const Relational& t)
{
    t.print(outs);
    return outs;
}

int Relational::op_type()
{
    return _op_type;
}

OP_TYPES Relational::calc_op_type(const string& str)
{
    if(str == "<")
        return OP_LS;
    else if(str == ">")
        return OP_GR;
    else if(str == "<=")
        return OP_LE;
    else if(str == ">=")
        return OP_GE;
    else
        return OP_EQ;
}
//Logical

Logical::Logical(): Token("and", TOKEN_ALPHA), _token_type(LOGICAL)
{
    precedence = calc_precedence();
}

Logical::Logical(const string& str): Token(str, TOKEN_ALPHA), _token_type(LOGICAL)
{
    precedence = calc_precedence();
}

int Logical::type() const
{
    return LOGICAL;
}

int Logical::get_precedence()
{
    return precedence;
}

int Logical::calc_precedence()
{
    string str = to_lower(token_str());
    if(str == "or")
        return LOGICAL;
    return LOGICAL + 1;//and has more precedence
}

void Logical::print(ostream& outs) const
{
    outs << "{ " << token_str() << " : " << precedence << " }";
}

ostream& operator <<(ostream& outs, const Logical& t)
{
    t.print(outs);
    return outs;
}

//LParen

LParen::LParen(): Token("(", TOKEN_LPAREN), precedence(LPAREN), _token_type(LPAREN){}

int LParen::type() const
{
    return LPAREN;
}

int LParen::get_precedence()
{
    return precedence;
}

void LParen::print(ostream& outs) const
{
    outs << "{ ( : " << precedence << " }";
}

ostream& operator <<(ostream& outs, const LParen& t)
{
    t.print(outs);
    return outs;
}

//RParen

RParen::RParen(): Token(")", TOKEN_RPAREN), precedence(RPAREN), _token_type(RPAREN){}

int RParen::type() const
{
    return RPAREN;
}

int RParen::get_precedence()
{
    return precedence;
}

void RParen::print(ostream& outs) const
{
    outs << "{ ) : " << precedence << " }";
}

ostream& operator <<(ostream& outs, const RParen& t)
{
    t.print(outs);
    return outs;
}

//Solution

Solution::Solution(): Token(), _token_type(SOLUTION){}

Solution::Solution(const vectorlong& v, regMap* map_ptr, vectormmap* mmap_ptr): Token(), _solution(v), _token_type(SOLUTION),
_field_map_ptr(map_ptr), _table_ptr(mmap_ptr)
{
    quick_sort(_solution);
}
//put this solution in, probably will not be used

Solution::Solution(Token* left, Token* right, Token* op, regMap* map_ptr, vectormmap* mmap_ptr): Token(), _token_type(SOLUTION),
_field_map_ptr(map_ptr), _table_ptr(mmap_ptr)
{
    _solution = calc_solution(left, right, op);
}
//can be (tokenstr relational tokenstr) or (solution logical solution)

int Solution::type() const
{
    return _token_type;
}

vectorlong Solution::get_solution_vect() const
{
    return _solution;
}

//print stuff
void Solution::print(ostream& outs) const
{
    outs << "Solution vect: " << _solution << endl;
}

ostream& operator <<(ostream& outs, const Solution& t)
{
    t.print(outs);
    return outs;
}

//calculating solutions

vectorlong Solution::calc_solution(Token* left, Token* right, Token* op)
{
    int leftType = left->type();
    int rightType = right->type();
    int opType = op->type();//gives type of op
    assert(opType == LOGICAL || opType == RELATIONAL);
    assert(leftType == rightType);//should either both be solutions or tokenStr's
    if(opType == RELATIONAL)
    {
        // cout << "Relational moment\n";
        string leftStr = left->token_str();
        string rightStr = right->token_str();
        assert(leftType == SYMBOL);
        switch(op->op_type())
        {
            case OP_EQ:
                cond_eq(leftStr, rightStr);
                break;
            case OP_LS:
                cond_lt(leftStr, rightStr);
                break;
            case OP_GR:
                cond_gt(leftStr, rightStr);
                break;
            case OP_LE:
                cond_le(leftStr, rightStr);
                break;
            case OP_GE:
                cond_ge(leftStr, rightStr);
                break;
        }
        // cout << "RELATIONAL SOLUTION BEFORE SORT:\n" << _solution << endl;
        quick_sort(_solution);//sorts solution afterwards
        // cout << "RELATIONAL SOLUTION AFTER SORT:\n" << _solution << endl;
    }
    else
    {
        assert(leftType == SOLUTION);//all solutions will be sorted before hand
        _solution = left->get_solution_vect();
        if(op->get_precedence() == LOGICAL)
        {
            // cout << "CALLING UNION\n";
            make_union(right->get_solution_vect());
            // cout << "solution after union" << _solution << endl;
        }
        else
        {
            // cout << "CALLING INTERSECTION\n";
            intersection(right->get_solution_vect());
            // cout << "solution after intersection:\n" << _solution << endl;
        }  
    }
    return _solution;
}

void Solution::make_union(const vectorlong& other)
{
    int index;
    bool isFound;
    for(int i = 0; i < other.size(); i++)
    {
        if(_solution.empty())
            _solution.push_back(other[i]);
        else
        {
            index = first_ge(_solution, other[i]);
            isFound = other[i] == _solution[index];
            if(!isFound)
                _solution.insert(_solution.begin() + index, other[i]);
        }
    }
}

void Solution::intersection(const vectorlong& other)
{
    vectorlong v;
    int index;
    bool isFound;
    // cout << "other: " << other << endl;
    if(_solution.empty())
    {
        _solution = v;
        return;
    }
    for(int i = 0; i < other.size(); i++)
    {    
        index = first_ge(_solution, other[i]);
        isFound = other[i] == _solution[index];
        if(isFound)
            v.push_back(other[i]);
    }
    // cout << v << endl;
    _solution = v;
}

void Solution::cond_eq(const string& left, const string& right)
{
    int index = _field_map_ptr->at(left);
    _solution = (_table_ptr->at(index))[right];
}

void Solution::cond_lt(const string& left, const string& right)
{
    vectorlong v;
    int index = _field_map_ptr->at(left);
    mmap* field_mmap = &(_table_ptr->at(index));
    typename mmap::Iterator it;
    typename mmap::Iterator lb(field_mmap->lower_bound(right));
    for(it = field_mmap->begin(); it != lb; ++it)
    {
        for(int i = 0; i < (*it).value_list.size(); i++)
            v += (*it).value_list[i];
    } 
    _solution = v;
}

void Solution::cond_gt(const string& left, const string& right)
{
    vectorlong v;
    int index = _field_map_ptr->at(left);
    mmap* field_mmap = &(_table_ptr->at(index));
    typename mmap::Iterator it;
    for(it = field_mmap->upper_bound(right); it != field_mmap->end(); ++it)
    {
        for(int i = 0; i < (*it).value_list.size(); i++)
            v += (*it).value_list[i];
    } 
    _solution = v;
}

void Solution::cond_le(const string& left, const string& right)
{
    vectorlong v;
    int index = _field_map_ptr->at(left);
    mmap* field_mmap = &(_table_ptr->at(index));
    typename mmap::Iterator it;
    typename mmap::Iterator ub(field_mmap->upper_bound(right));
    // cout << "We good\n";
    for(it = field_mmap->begin(); it != ub; ++it)
    {
        
        for(int i = 0; i < (*it).value_list.size(); i++)
        {
            // cout << "Stuff\n";
            v += (*it).value_list[i];
        }
    } 
    _solution = v;
}

void Solution::cond_ge(const string& left, const string& right)
{
    vectorlong v;
    int index = _field_map_ptr->at(left);
    mmap* field_mmap = &(_table_ptr->at(index));
    typename mmap::Iterator it;
    for(it = field_mmap->lower_bound(right); it != field_mmap->end(); ++it)
    {
        for(int i = 0; i < (*it).value_list.size(); i++)
            v += (*it).value_list[i];
    } 
    _solution = v;
}

