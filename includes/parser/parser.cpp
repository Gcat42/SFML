#include "parser.h"

int Parser::_table[MAX_ROWS][MAX_COLUMNS];

Parser::Parser()
{
    make_table();
}

Parser::Parser(char inputStr[])
{
    set_string(inputStr);
    // make_input_vector();
    make_table();
}

// Parser::Parser(const string& inputStr): _input_str(inputStr)
// {
//     stk.set_string();
//     make_input_vector();
//     make_table();
// }

mmap_ss Parser::parse_tree()
{
    mmap_ss parseTree;
    string tok;
    TOKEN_TYPES type;
    int state = 0;
    bool inserted;
    string holder("");
    for(int i = 0; i < token_vect.size(); i++)
    {
        string str("");
        tok = token_vect[i];
        holder += tok;
        type = get_enum_val(tok);
        // cout << state << " " << tok << endl;
        if(type != LPAREN && type != RPAREN)//just input parentheses
            state = _table[state][type];
        str = holder;
        if(state == -1)
        {
            cout << "ERROR OCCURRED for token " << tok << ", type: " << type << endl;
            _is_valid = false;
            return parseTree;
        }
        inserted = insert_to_parse_tree(parseTree, tok, type, state);
        if(!inserted)
            holder += " ";
        else
            holder = "";
    }
    _is_valid = is_success(_table, state);
    return parseTree;
}

void Parser::print_vect()
{
    // cout << "PRINTING\n" << token_vect.size() << endl;
    for(int i = 0; i < token_vect.size(); i++)
        cout << token_vect[i] << " ";
    cout << endl;
}

bool Parser::is_valid()
{
    return _is_valid;
}

void Parser::set_string(char str[])
{
    string newString("");
    char* walker = str;
    while(*walker != '\0')
    {
        newString += *walker;
        walker++;
    }
    _input_str = newString;
    stk.set_string(str);
    make_input_vector();
}

void Parser::make_input_vector()//will make vector of usable tokens
{
    bool debug = false;
    vectorstr v;
    Token t;
    // cout << _input_str << endl;
    stk >> t;
    while(!stk.done())
    {
        if(debug)
            cout << t << '\t' << t.type_string() << endl;
        v += t;//will put into v only usable tokens (non-spaces)
        stk >> t;
    }
    token_vect = v;
    // print_vect();
}


void Parser::make_table()
{
    init_table(_table);//makes default table
    //marking success states
    for(int i = 0; i <= 20; i++)
    {
        if(i == SELECT_FROM_TABLE || i == WHERE_FIELD_REL_VAL || i == INSERT_VALUES_SYMBOL || i == MAKE_FIELDS_SYMBOL)
            mark_success(_table, i);
        else
            mark_fail(_table, i);
    }
    //row 0 (3 different commands)
    mark_cell(0,_table, SELECT, SELECT);
    mark_cell(0, _table, INSERT, INSERT);
    mark_cell(0,_table, CREATE, CREATE);
    //row 1 (select FIELD_NAMES)
    mark_cell(SELECT, _table, SYMBOL, SELECT_FIELD);
    mark_cell(SELECT, _table, ALL, SELECT_ALL);
    //row 2 (insert INTO)
    mark_cell(INSERT, _table, INTO, INTO);
    //row 3 (insert into TABLE_NAME)
    mark_cell(INTO, _table, SYMBOL, INSERT_INTO_TABLE);
    //row 4 (create/make TABLE)
    mark_cell(CREATE, _table, TABLE, MAKE_TABLE);
    //row 5 (select fields COMMA)/(select fields FROM)
    mark_cell(SELECT_FIELD, _table, COMMA, SELECT_FIELD_COMMA);
    mark_cell(SELECT_FIELD, _table, FROM, SELECT_FROM);
    //row 6 (select field, FIELD[s])
    mark_cell(SELECT_FIELD_COMMA, _table, SYMBOL, SELECT_FIELD);
    //row 7 (select fields from TABLE_NAME)
    mark_cell(SELECT_FROM, _table, SYMBOL, SELECT_FROM_TABLE);
    //row 8 (select fields from table_name WHERE)
    mark_cell(SELECT_FROM_TABLE, _table, WHERE, SELECT_FROM_TABLE_WHERE);
    //row 9 (select fields from table_name where FIELD)
    mark_cell(SELECT_FROM_TABLE_WHERE, _table, SYMBOL, WHERE_FIELD);
    //row 10 (select fields from table_name where field RELATIONAL)
    mark_cell(WHERE_FIELD, _table, RELATIONAL, WHERE_FIELD_REL);
    //row 11 (select fields from table_name where field relational SYMBOL)
    mark_cell(WHERE_FIELD_REL, _table, SYMBOL, WHERE_FIELD_REL_VAL);
    //row 12 (select fields from table_name where field relational symbol LOGICAL [if needed])
    mark_cell(WHERE_FIELD_REL_VAL, _table, LOGICAL, SELECT_FROM_TABLE_WHERE);
    //row 13 (select ALL [*])
    mark_cell(SELECT_ALL, _table, FROM, SELECT_FROM);
    //row 14 (insert into table_name VALUES)
    mark_cell(INSERT_INTO_TABLE, _table, VALUES, INSERT_INTO_TABLE_VALUES);
    //row 15 (insert into table_name values SYMBOL[s])
    mark_cell(INSERT_INTO_TABLE_VALUES, _table, SYMBOL, INSERT_VALUES_SYMBOL);
    //row 16 (insert into table_name values value COMMA)
    mark_cell(INSERT_VALUES_SYMBOL, _table, COMMA, INSERT_INTO_TABLE_VALUES);
    //row 17 (make table TABLE_NAME)
    mark_cell(MAKE_TABLE, _table, SYMBOL, MAKE_TABLE_NAME);
    //row 18 (make table table_name FIELDS)
    mark_cell(MAKE_TABLE_NAME, _table, FIELDS, MAKE_TABLE_FIELDS);
    //row 19 (make table table_name fields SYMBOL[s])
    mark_cell(MAKE_TABLE_FIELDS, _table, SYMBOL, MAKE_FIELDS_SYMBOL);
    //row 20 (make table table_name fields fields[s] COMMA)
    mark_cell(MAKE_FIELDS_SYMBOL, _table, COMMA, MAKE_TABLE_FIELDS);
}

TOKEN_TYPES Parser::get_enum_val(const string& str)
{
    if(str == "select")
        return SELECT;
    else if(str == "insert")
        return INSERT;
    else if(str == "into")
        return INTO;
    else if(str == "create" || str == "make")
        return CREATE;
    else if(str == "table")
        return TABLE;
    else if(str == "from")
        return FROM;
    else if(str == "where")
        return WHERE;
    else if(str == "values")
        return VALUES;
    else if(str == "fields")
        return FIELDS;
    else if(str == ",")
        return COMMA;
    else if(str == "\"")
        return QUOTE;
    else if(str == "*")
        return ALL;
    else if(str == "=" || str == "<=" || str == ">=" || str == "<" || str == ">")
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

bool Parser::insert_to_parse_tree(mmap_ss& parseTree, const string& str, TOKEN_TYPES type, int state)
{//this assumes no false input
    switch(type)
    {
        case SELECT:
            // cout << "SELECT CALLED\n";
            parseTree.insert("command", str);
            return true;
        case INSERT://come back from INTO
            return false;
        case INTO:
            parseTree.insert("command", "insert");
            return true;
        case CREATE:
            // cout << "CREATE CALLED\n";
            return false;
        case TABLE:
            // cout << "TABLE CALLED\n";
            parseTree.insert("command", "make");
            return true;
        case FROM://does not really do anything
            return true;
        case WHERE:
            parseTree.insert("where", "yes");
            return true;
        case FIELDS://does not really do anything
            // cout << "FIELDS CALLED\n";
            return true;
        case VALUES://does not really do anything
            return true;
        case ALL:
            parseTree.insert("fields", str);
            return true;
        case SYMBOL:
            switch(state)
            {
                case SELECT_FIELD:
                    parseTree.insert("fields", str);
                    return true;
                case SELECT_FROM_TABLE:
                    parseTree.insert("table_name", str);
                    return true;
                case WHERE_FIELD:
                    parseTree.insert("condition", str);
                    return true; 
                case WHERE_FIELD_REL_VAL:
                    parseTree.insert("condition", str);
                    return true; 
                case INSERT_INTO_TABLE: 
                    parseTree.insert("table_name", str);
                    return true;
                case INSERT_VALUES_SYMBOL:
                    parseTree.insert("values", str);
                    return true;
                case MAKE_TABLE_NAME:
                    // cout << "MAKE TABLE_NAME CALLED\n";
                    parseTree.insert("table_name", str);
                    return true;
                case MAKE_FIELDS_SYMBOL:
                    parseTree.insert("col", str);
                    return true; 
            }
        case COMMA://not really used
            return true;
        case LPAREN://will only occur in select
            parseTree.insert("condition", str);
            return true;
        case RPAREN://same case for RPAREN
            parseTree.insert("condition", str);
            return true;
        case LOGICAL://all logical and relational operators will only be allowed in select
            parseTree.insert("condition", str);
            return true;
        case RELATIONAL:
            parseTree.insert("condition", str);
            return true;
    }
    cout << "SHOULD NEVER GO HERE\n";
    return false;
}