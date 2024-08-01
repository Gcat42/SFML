#include "stokenize.h"

//static var _table
int STokenizer::_table[MAX_ROWS][MAX_COLUMNS];

STokenizer::STokenizer(): _pos(0)
{
    make_table(_table);
}

STokenizer::STokenizer(char str[]): _pos(0)
{
    char* walker = _buffer;
    char* strWalker = str;
    int size = 0;
    while(*strWalker != '\0' && size < MAX_BUFFER)
    {
        *walker = *strWalker;
        size++;
        walker++;
        strWalker++;
    }
    *walker = '\0';
    make_table(_table);
}

STokenizer::STokenizer(const string& str)
{
    char* walker = _buffer;
    int size = 0;
    for(int i = 0; i < str.length() && size < MAX_BUFFER; i++, walker++, size++)
        *walker = str[i];
    *walker = '\0';
    make_table(_table);
}

bool STokenizer::done()
{
    char* walker = _buffer + _pos;
    if(_pos == 0)
        return *walker == '\0';
    walker--;
    return *walker == '\0';
}
//true: there are no more tokens

bool STokenizer::more()
{
    return !done();
}
//true: there are more tokens

//
//---------------
//extract one token (very similar to the way cin >> works)
STokenizer& operator >> (STokenizer& s, Token& t)
{
    string tokenStr;
    int last_success_state;
    bool success = s.get_token(last_success_state, tokenStr);
    if(!success)
        t = Token(tokenStr, TOKEN_UNKNOWN);
    else
        t = Token(tokenStr, last_success_state);
    return s;
}


//set a new string as the input string
void STokenizer::set_string(char str[])
{
    char* walker = _buffer;
    char* strWalker = str;
    int size = 0;
    while(*strWalker != '\0' && size < MAX_BUFFER)
    {
        *walker = *strWalker;
        walker++;
        strWalker++;
    }
    *walker = '\0';
    _pos = 0;
}

//PRIVATE FUNCTIONS

//create table for all the tokens we will recognize
//                      (e.g. doubles, words, etc.)
void STokenizer::make_table(int _table[][MAX_COLUMNS])
{
    //making table
    init_table(_table);
    for(int i = 0; i <= 12; i++)
    {
        if(i == 0 || i == 3 || i == 11)//fail states
            mark_fail(_table, i);
        else//success states at 1, 2, 4, 5, 6, 7, 8, 9, 10
            mark_success(_table, i);
    }
    //state 0
    mark_cells(0, _table, ALFA, TOKEN_ALPHA);
    mark_cells(0, _table, DIGITS, TOKEN_INT);
    mark_cells(0, _table, SPACES, TOKEN_SPACE);
    mark_cells(0, _table, PUNC, TOKEN_PUNC);
    mark_cells(0, _table, OPERATORS, TOKEN_OPERATOR);
    mark_cells(0, _table, RELATIONALOPS, TOKEN_RELATIONAL);
    mark_cell(0, _table, '(', TOKEN_LPAREN);
    mark_cell(0, _table, ')', TOKEN_RPAREN);
    mark_cell(0, _table, '\"', TOKEN_QUOTE);
    //state 1
    mark_cells(1, _table, ALFA, TOKEN_ALPHA);
    //state 2
    mark_cells(2, _table, DIGITS, TOKEN_INT);
    mark_cell(2, _table, '.', 3);
    //state 3
    mark_cells(3, _table, DIGITS, TOKEN_FLOAT);
    //state 4
    mark_cells(4, _table, DIGITS, TOKEN_FLOAT);
    //state for relational
    mark_cell(8, _table, '=', TOKEN_OPERATOR);//takes back to operator, other wise stays in this success state
    //state for quotes
    mark_cells(TOKEN_QUOTE, _table, ALFA, TOKEN_QUOTE);
    mark_cells(TOKEN_QUOTE, _table, DIGITS, TOKEN_QUOTE);
    mark_cells(TOKEN_QUOTE, _table, OPERATORS, TOKEN_QUOTE);
    mark_cells(TOKEN_QUOTE, _table, RELATIONALOPS, TOKEN_QUOTE);
    mark_cells(TOKEN_QUOTE, _table, SPACES, TOKEN_QUOTE);
    mark_cells(TOKEN_QUOTE, _table, PUNC, TOKEN_QUOTE);
    mark_cells(TOKEN_QUOTE, _table, "()", TOKEN_QUOTE);
    mark_cell(TOKEN_QUOTE, _table, '\"', QUOTE_SUCCESS);

}

//extract the longest string that match
//     one of the acceptable token types
bool STokenizer::get_token(int& last_success_state, string& token)
{
    token = "";
    string holder;
    char* walker = _buffer + _pos;
    int posWalker = _pos;
    last_success_state = 0;
    int state = 0;
    while(*walker != '\0')
    {
        if(*walker != '\"')
            holder += *walker;
        if(*walker < 0)//special character
        {
            _pos = posWalker + 1;
            return last_success_state;
        }
        state = _table[state][*walker];
        if(state == -1)
        {
            // cout << "FAILED: " << last_success_state << endl;
            return last_success_state;
        }
        if(_table[state][0] == 1)
        {
            // cout << "Success state at state #" << state << endl;
            _pos = posWalker + 1;
            last_success_state = state;
            token += holder;
            holder = "";
        }
        walker++;
        posWalker++;
    }
    // cout << "LSS: " << last_success_state << endl;
    if(!last_success_state)
    {
        last_success_state = TOKEN_END;
        _pos++;//will put past null character
    }
    // cout << "LSS: " << last_success_state << endl;
    return last_success_state;//if last_success_state is 0, it means it failed at state 0, meaning it should be an unknown
}
