#include "sql.h"

SQL::SQL(){}

Table SQL::command(const string& str)
{
    update_info(str);//updates Parser and Instruction info
    return follow_instructions();
}

vectorlong SQL::select_recnos()
{
    return selectmem;
}

bool SQL::is_valid()
{
    return psr.is_valid();
}

TOKEN_TYPES SQL::get_command_type()
{
    return command_type;
}

void SQL::update_info(const string& str)
{
    char temp[str.length() + 1];
    string_to_cstr(temp, str);
    //now changing parser string
    psr.set_string(temp);
    instruction = psr.parse_tree();//set new instructions
    // instruction.print_lookup();
}

void SQL::string_to_cstr(char cStr[], const string& str)
{
    char* walker = cStr;
    for(int i = 0; i < str.length(); i++, walker++)
        *walker = str[i];
    *walker = '\0';//putting null character at end
}

Table SQL::follow_instructions()
{
    // cout << "HUH\n";
    if(is_valid())
    {
        vectorstr v = instruction["command"];
        // cout << "HUH2\n";
        string command(v[0]);//get command
        if(command == "select")
        {
            // cout << "Calling select\n";
            command_type = SELECT;
            return call_select();
        }
        else if(command == "insert")
        {
            // cout << "Calling insert into\n";
            command_type = INSERT;
            return call_insert();
        }
        else if(command == "make")
        {
            // cout << "Calling make\n";
            command_type = CREATE;
            return call_make();
        }
    }
    // cout << "Should not be get here\n";
    command_type = SYMBOL;//should not matter
    return Table();
}

Table SQL::call_select()
{
    vectorstr v = instruction["table_name"];
    string table_name = v[0];
    vectorstr fields = instruction["fields"];
    bool where = instruction.contains("where");
    Table realTable(table_name);
    // cout << realTable;
    Table temp;
    if(fields[0] == "*")
        fields = realTable.get_field_names();
    // cout << fields;
    if(where)
    {
        vectorstr condition = instruction["condition"];
        cout << condition;
        temp = realTable.select(fields, condition);
    }
    else
    {
        // cout << "NO WHERE\n";
        cout << "There is no condition\n";
        temp = realTable.select_all(fields);
    }
    selectmem = realTable.select_recnos();
    return temp;
}

Table SQL::call_make()
{
    vectorstr v = instruction["table_name"];
    string table_name = v[0];
    vectorstr col = instruction["col"];
    Table realTable(table_name, col);
    return realTable;
}

Table SQL::call_insert()
{
    vectorstr v = instruction["table_name"];
    string table_name = v[0];
    vectorstr values = instruction["values"];
    Table realTable(table_name);
    realTable.insert_into(values);
    return realTable;
}
