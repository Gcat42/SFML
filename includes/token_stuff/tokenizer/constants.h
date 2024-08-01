#ifndef CONSTANTS_H
#define CONSTANTS_H

const int MAX_COLUMNS = 256;
const int MAX_ROWS = 100;
const int MAX_BUFFER = 200;

const char ALFA[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char DIGITS[] = "0123456789";
const char OPERATORS[] = "=!*+-%&|";
const char RELATIONALOPS[] = "><";
const char SPACES[] = {' ', '\t', '\n', '\0'};
const char PUNC[] = "?.,:;'`~!\"";
const int START_DOUBLE = 0;
const int START_SPACES = 4;
const int START_ALPHA = 6;
const int START_OPERATOR = 20;
const int START_PUNC = 10;

//token types:
const int TOKEN_ALPHA = 1;
const int TOKEN_INT = 2;
const int TOKEN_FLOAT = 4;
const int TOKEN_SPACE = 5;
const int TOKEN_PUNC = 6;
const int TOKEN_OPERATOR = 7;//=, >=, <=
const int TOKEN_RELATIONAL = 8;//<, >
const int TOKEN_LPAREN = 9;
const int TOKEN_RPAREN = 10;
const int TOKEN_QUOTE = 11;
const int QUOTE_SUCCESS = 12;

const int TOKEN_UNKNOWN = -1;
const int TOKEN_END = -2;

enum OP_TYPES {
    OP_EQ = 42,
    OP_NE,
    OP_GR, 
    OP_GE,
    OP_LS,
    OP_LE,
};

enum TOKEN_TYPES{
    SELECT = 1,
    INSERT,
    INTO,
    CREATE,
    TABLE,
    FROM,
    WHERE,
    FIELDS,
    VALUES,
    ALL,
    SYMBOL,
    COMMA,
    QUOTE,//will not use anymore
    LPAREN,//we do not want logical/relationals to cause lparens to pop
    RPAREN,
    LOGICAL,//two logical statement and/or both have diff prec.; used for token functions
    RELATIONAL = LOGICAL + 2,
    SOLUTION,
};

enum STATE_MACHINE{
    SELECT_FIELD = 5,
    SELECT_FIELD_COMMA,
    SELECT_FROM,
    SELECT_FROM_TABLE,
    SELECT_FROM_TABLE_WHERE,
    WHERE_FIELD,
    WHERE_FIELD_REL,
    WHERE_FIELD_REL_VAL,
    SELECT_ALL,
    INSERT_INTO_TABLE,
    INSERT_INTO_TABLE_VALUES,
    INSERT_VALUES_SYMBOL,
    MAKE_TABLE,
    MAKE_TABLE_NAME,
    MAKE_TABLE_FIELDS,
    MAKE_FIELDS_SYMBOL
};

#endif