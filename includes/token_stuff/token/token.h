#ifndef TOKEN_H
#define TOKEN_H
#include <iostream>
#include <assert.h>
#include <string>
#include "../tokenizer/constants.h"
#include "../../table/typedefs.h"

using namespace std;

class Token
{
public:
    Token();
    Token(const string& str, int type);
    virtual void print(ostream& outs) const;
    friend ostream& operator <<(ostream& outs, const Token& t);
    virtual int type() const;
    virtual int get_precedence();
    string type_string() const;
    string token_str() const;
    virtual vectorlong get_solution_vect() const;//FOR SOLUTION
    virtual int op_type();
    bool is_usable() const;
    friend void operator +=(vectorstr& v, const Token& t);
private:
    string _token;
    int _type;
};

#endif