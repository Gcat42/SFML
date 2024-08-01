#include "token.h"

Token::Token(): _token(""), _type(TOKEN_UNKNOWN){}

Token::Token(const string& str, int type): _token(str), _type(type){}

void Token::print(ostream& outs) const
{
    if(type() != TOKEN_SPACE)
        outs << "|" << _token << "|";
    else
        outs << "| |";
}

ostream& operator <<(ostream& outs, const Token& t)
{
    t.print(outs);
    return outs;
}

int Token::get_precedence()
{
    cout << "SHOULD NOT BE F*&KING CALLED\n";
    return -1000;
}

int Token::type() const
{
    return _type;
}

string Token::type_string() const
{
    switch(_type)
    {
        case TOKEN_ALPHA:
            return "ALPHA";
        case TOKEN_INT:
            return "INT";
        case TOKEN_FLOAT:
            return "FLOAT";
        case TOKEN_SPACE:
            return "SPACE";
        case TOKEN_OPERATOR:
            return "OPERATOR";
        case TOKEN_RELATIONAL:
            return "RELATIONAL";
        case TOKEN_PUNC:
            return "PUNC";
        case TOKEN_LPAREN:
            return "LPAREN";
        case TOKEN_RPAREN:
            return "RPAREN";
        case TOKEN_UNKNOWN:
            return "UNKNOWN";
        case TOKEN_END:
            return "END";
        case QUOTE_SUCCESS:
            return "QUOTE_STRING";
        default:
            return "DEFAULT (SOMETHING IS EXTREMELY WRONG)";
    }
}

string Token::token_str() const
{
    return _token;
}

vectorlong Token::get_solution_vect() const
{
    cout << "SHOULD NEVER CALL THIS, SHOULD ONLY BE CALLED IN SOLUTION CLASS\n";
    vectorlong v = {-1000,42,-1000};
    return v;
}//FOR SOLUTION

int Token::op_type()
{
    cout << "SHOULD NEVER CALL THIS, SHOULD ONLY BE CALLED IN RELATIONAL CLASS\n";
    return -1000;
}

bool Token::is_usable() const
{
    switch(_type)
    {
        case TOKEN_PUNC:
            if(_token == "," || _token == "\"")
                return true;
            return false;
        case TOKEN_OPERATOR:
            if(_token == "=" || _token == "<=" || _token == ">=" || _token == "*")
                return true;
            return false;
        case TOKEN_RELATIONAL:
            return true;
        case TOKEN_ALPHA:
            return true;
        case TOKEN_INT:
            return true;
        case TOKEN_FLOAT:
            return true;
        case TOKEN_LPAREN:
            return true;
        case TOKEN_RPAREN:
            return true;
        case QUOTE_SUCCESS:
            return true;
        default:
            return false;
    }
}

void operator +=(vectorstr& v, const Token& t)
{
    if(t.is_usable())
        v.push_back(t._token);
}