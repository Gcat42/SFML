#include "ftokenize.h"

FTokenizer::FTokenizer(const char* fname): _pos(0), _blockPos(0), _more(1)
{
    // char fileName[MAX_BUFFER] = "C:\\Users\\alext\\OneDrive\\Desktop\\CS8_Projects\\";
    // fileName += fname;
    _f.open(fname);
    if(_f.fail())
    {
        cout << "File \"" << fname << "\" failed to open!\n"; 
        exit(2);
    }
    get_new_block();
}

// FTokenizer::~FTokenizer()
// {
//     _f.close();
// }

Token FTokenizer::next_token()
{
    Token t;
    if(!_stk.done())
    {
        // cout << "Pulling from stk\n";
        _stk >> t;
        _blockPos = _stk.get_pos();
        _pos += _blockPos;
    }   
    else if(!_f.eof())
    {
        get_new_block();
        _stk >> t;
        _blockPos = _stk.get_pos();
        _pos += _blockPos;
    }
    else
    {
        _more = false;
        t = Token("END OF FILE\n", TOKEN_END); 
        cout << "END OF FILE******\n";
        _f.close();
    }
    return t;
}

bool FTokenizer::more()
{
    return _more;
}
//returns the current value of _more

int FTokenizer::pos()
{
    return _pos;
}
//returns the value of _pos

int FTokenizer::block_pos()
{
    return _blockPos;
}
//returns the value of _blockPos

FTokenizer& operator >> (FTokenizer& f, Token& t)
{
    t = f.next_token();
    return f;
}

bool FTokenizer::get_new_block()
{
    _blockPos = 0;
    char str[MAX_BLOCK + 1];
    _f.read(str, MAX_BLOCK);
    int size = _f.gcount();
    cout << "GETTING NEW BLOCKED---------------------[" << size << " bytes]\n";
    str[size] = '\0';
    //print
    _stk.set_string(str);
    return size < MAX_BLOCK;//returns false if end of file reached
}
//gets the new block from the file

void print_part_block(char str[])
{
    cout << "PART OF NEW BLOCK: ";
    char* walker = str;
    for (int i = 0; i < 12; i++)
        cout << *walker;
    cout << endl;
}