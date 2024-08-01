#ifndef CHILD_TOKENS_H
#define CHILD_TOKENS_H
#include <iostream>
#include <string.h>
#include "token.h"
#include "../tokenizer/constants.h"
#include "../../table/typedefs.h"
#include "../../bplustree/btree_array_funcs.h"//for printing array
#include "../../bplustree/map.h"
#include "../../bplustree/multimap.h"
#include <assert.h>
#include "../../quick_sort/quick_sort.h"

using namespace std;

string to_lower(const string& str);

int first_ge(const vectorlong& v, long entry);
// vectorlong& operator +=(vectorlong& result, vectorlong& addMe);

class TokenStr: public Token
{
    public:
        TokenStr();
        TokenStr(const string& str);
        virtual int type() const;
        virtual int get_precedence();
        //print stuff
        virtual void print(ostream& outs) const;
        friend ostream& operator <<(ostream& outs, const TokenStr& t);
    private:
        TOKEN_TYPES calc_token_type();
        TOKEN_TYPES _token_type;
        int precedence;
};

class Relational: public Token
{
    public:
        Relational();
        Relational(const string& str);
        virtual int type() const;
        virtual int get_precedence();
        virtual int op_type();
        //print stuff
        virtual void print(ostream& outs) const;
        friend ostream& operator <<(ostream& outs, const Relational& t);
    private:
        OP_TYPES calc_op_type(const string& str);
        TOKEN_TYPES _token_type;
        int precedence;
        OP_TYPES _op_type;
};

class Logical : public Token
{
    public:
        Logical();
        Logical(const string& str);
        virtual int type() const;
        virtual int get_precedence();
        //print stuff
        virtual void print(ostream& outs) const;
        friend ostream& operator <<(ostream& outs, const Logical& t);
    private:
        int calc_precedence();
        TOKEN_TYPES _token_type;
        int precedence;
};

class LParen : public Token
{
    public:
        LParen();
        virtual int type() const;
        virtual int get_precedence();
        //print stuff
        virtual void print(ostream& outs) const;
        friend ostream& operator <<(ostream& outs, const LParen& t);
    private:
        TOKEN_TYPES _token_type;
        int precedence;
};

class RParen : public Token
{
    public:
        RParen();
        virtual int type() const;
        virtual int get_precedence();
        //print stuff
        virtual void print(ostream& outs) const;
        friend ostream& operator <<(ostream& outs, const RParen& t);
    private:
        TOKEN_TYPES _token_type;
        int precedence;
};

class Solution : public Token
{
    public:
        Solution();
        Solution(const vectorlong& v, regMap* map_ptr, vectormmap* mmap_ptr);//put this solution in, probably will not be used
        Solution(Token* left, Token* right, Token* op, regMap* map_ptr, vectormmap* mmap_ptr);//can be (tokenstr relational tokenstr) or (solution logical solution)
        virtual int type() const;
        virtual vectorlong get_solution_vect() const;
        // virtual int get_precedence();
        //print stuff
        virtual void print(ostream& outs) const;
        friend ostream& operator <<(ostream& outs, const Solution& t);
    private:
        vectorlong calc_solution(Token* left, Token* right, Token* op);
        void make_union(const vectorlong& other);
        void intersection(const vectorlong& other);
        void cond_eq(const string& left, const string& right);
        void cond_lt(const string& left, const string& right);
        void cond_gt(const string& left, const string& right);
        void cond_le(const string& left, const string& right);
        void cond_ge(const string& left, const string& right);
        vectorlong _solution;
        TOKEN_TYPES _token_type;
        vectormmap* _table_ptr;
        regMap* _field_map_ptr;
};

#endif