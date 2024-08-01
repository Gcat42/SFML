#include <iostream>
#include <iomanip>
#include <fstream>
#include "includes/sql/sql.h"
#include "includes/table/table.h"
#include "includes/token_stuff/tokenizer/constants.h"

using namespace std;


int main(int argv, char** argc) {
    cout << "\n\n"
         << endl;
    const int BUFFER_SIZE = 200;
    bool showTable;
    SQL sql;
    Table t;
    char command[BUFFER_SIZE + 1];
    cout << "Hi, welcome to your favorite SQL database!\n";
    cout << "Would you like to output the tables? (Y for yes/N for no):";
    cin.getline(command, BUFFER_SIZE);
    if(tolower(command[0]) == 'y')
        showTable = true;
    else
        showTable = false;
    cout << ">";
    cin.getline(command, BUFFER_SIZE);//includes null character
    cout << command << endl;
    while(tolower(command[0]) != 'x')
    {
        t = sql.command(command);
        if(!sql.is_valid())
        {
            cout << "Invalid statement, please try again\n";
            cout << ">";
            cin.getline(command, BUFFER_SIZE);//includes null
            cout << command << endl;
            continue;
        }
        // cout << sql.get_command_type() << endl;
        if(showTable && (sql.get_command_type() == INSERT || sql.get_command_type() == CREATE))
            cout << t;
        else if(sql.get_command_type() == SELECT)
            cout << t;
        cout << ">";
        cin.getline(command, BUFFER_SIZE);
        cout << command << endl;
    }
    cout << "QUITTING PROGRAM, HAVE A NICE DAY\n";
    cout << "\n\n\n=====================" << endl;
    return 0;
}
