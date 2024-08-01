#include "matrix_functions.h"

//Fill all cells of the array with -1
void init_table(int _table[][MAX_COLUMNS])
{
    for(int i = 0; i < MAX_ROWS; i++)
    {
        for(int j = 0; j < MAX_COLUMNS; j++)
            _table[i][j] = -1;
    }
}


//Mark this state (row) with a 1 (success)
void mark_success(int _table[][MAX_COLUMNS], int state)
{
    _table[state][0] = 1;
}


//Mark this state (row) with a 0 (fail)
void mark_fail(int _table[][MAX_COLUMNS], int state)
{
    _table[state][0] = 0;
}


//true if state is a success state
bool is_success(int _table[][MAX_COLUMNS], int state)
{
    int stateVal = _table[state][0];
    assert(stateVal == 0 || stateVal == 1);
    return stateVal;
}


//Mark a range of cells in the array. 
void mark_cells(int row, int _table[][MAX_COLUMNS], int from, int to, int state)
{
    assert(row < MAX_ROWS && row >= 0);
    for(int i = from; i <= to; i++)
        _table[row][i] = state;
}


//Mark columns represented by the string columns[] for this row
void mark_cells(int row, int _table[][MAX_COLUMNS], const char columns[], int state)
{
    assert(row < MAX_ROWS && row >= 0);
    const char* walker = columns;
    while(*walker != '\0')
    {
        assert(*walker < MAX_COLUMNS && *walker >= 0);
        _table[row][*walker] = state;
        walker++;
    }
}


//Mark this row and column
void mark_cell(int row, int _table[][MAX_COLUMNS], int column, int state)
{
    assert(row < MAX_ROWS && row >= 0 && column < MAX_COLUMNS && column >= 0);
    _table[row][column] = state;
}


//This can realistically be used on a small table
void print_table(int _table[][MAX_COLUMNS])//32 - 126
{
    cout << left << setw(3) << " " << setw(3) << "~";
    char c;
    for(int i = 0; i <= 94; i++)
    {
        c = i + 32;
        if(i == 0)
            cout << left << setw(3) << "sp";
        else if(in_range(c))
            cout << setw(3) << c;
    }
    cout << endl;
    for(int i = 0; i < 10; i++)
    {
        cout << setw(3) << i;
        for(int j = -1; j <= 94; j++)
        {
            if(j == -1)
                cout << setw(3) << _table[i][0];
            else if(in_range(j + 32))
                cout << setw(3) << _table[i][j + 32];
        }
        cout << endl;
    }
    cout << endl;
}


//show string s and mark this position on the string:
//hello world   pos: 7
//       ^
void show_string(char s[], int _pos)
{
    assert(_pos >= 0);
    cout << s << "\tpos: " << _pos << endl;
    for(int i = 0; i < _pos; i++)
        cout << " ";
    cout << "^\n";
}

bool in_range(char c) //makes sure that c is not E-Z or e-z
{
    bool inRange = (c < 'E' || c > 'z') || (c > 'Z' && c < 'e');
    return inRange;
}
