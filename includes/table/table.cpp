#include "table.h"

long Table::serial = 0;

//ctors
Table::Table(){}

Table::Table(const string& fileName, const vectorstr& fieldNames): field_names(fieldNames), table_name(fileName), lastRecno(-1)
{
    
    table_field_names = table_name + "_fields.bin";
    open_fileW(f, table_name + ".bin");
    for(int i = 0; i < fieldNames.size(); i++)//put into map
    {
        _field_map.insert(fieldNames[i], i);
        _table.push_back(mmap());
    }
    f.close();
    //open field names file
    FileRecord r(field_names);
    open_fileW(f, table_field_names);
    r.write(f);//writes fieldnames to file
    serial++;//one file created
    // f.close();
}

Table::Table(const string& fileName): table_name(fileName), lastRecno(-1)
{
    table_field_names = table_name + "_fields.bin";
    open_fileRW(f, table_field_names);//need to add to the vector
    //get field names
    FileRecord r;//empty file record
    r.read(f,0);//file names will be first index of file
    int index = 0;
    while(r._record[index][0] != '\0')
    {
        string converted = static_cast<string>(r._record[index]);
        field_names += converted;
        index++;
    }
    f.close();
    open_fileRW(f, table_name + ".bin");//now put stuff in the map
    for(int i = 0; i < field_names.size(); i++)//put into map
    {
        _field_map.insert(field_names[i], i);
        _table.push_back(mmap());
    }
    while(r.read(f, lastRecno + 1) > 0)//while there is stuff to read, put stuff into mmap
    {
        for(int i = 0; i < field_names.size(); i++)
            _table[i].insert(r._record[i], lastRecno + 1);
        lastRecno++;
    }

    // serial++;
    // f.close();
}

// BIG THREE
Table::Table(const Table& copyMe): table_name(copyMe.table_name),table_field_names(copyMe.table_field_names),
field_names(copyMe.field_names), _field_map(copyMe._field_map), _table(copyMe._table), lastRecno(copyMe.lastRecno){}

Table& Table::operator =(const Table& RHS)
{
    if(this == &RHS)
        return *this;
    table_name = RHS.table_name;
    field_names = RHS.field_names;
    _field_map = RHS._field_map;
    _table = RHS._table;
    lastRecno = RHS.lastRecno;
    return *this;
}

Table::~Table()
{
    f.close();
}

//


//insert
void Table::insert_into(const vectorstr& v)
{
    f.close();
    open_fileRW(f, table_name + ".bin");
    f.seekg(0, f.end);
    FileRecord r(v);//make a file record
    string key("");
    lastRecno = r.write(f);//gives you the record number
    r.read(f, lastRecno);//somehow fixes shit for printing
    //once written insert the john into mmap
    for(int i = 0; i < v.size(); i++)
    {
        key = r._record[i];
        // cout << "Inserting: " << key << " with recno: " << lastRecno << endl;
        // cout << "BRUH STR\n";
        _table[i].insert(key, lastRecno);//put recno corresponding with each field for the record inserted
        // cout << _table[i];
        // cout << "Index " << i << ":\n" << _table[i];
    }
    // cout << "Bruh 3\n";
    // f.close();
}

//prints
void Table::print_records(ostream& outs)
{
    f.close();
    open_fileRW(f, table_name + ".bin");
    FileRecord r;
    int i=0;
    int bytes = r.read(f, i);
    while (bytes>0){
        outs << right << setw(25) << i;
        for(int j = 0; j < field_names.size(); j++)
            outs << right << setw(25) << r._record[j];
        outs << endl;

        bytes = r.read(f, ++i);
    }
    
    // for(int i = 0; i <= lastRecno; i++)
    // {
    //     // assert(r.read(f, i)  > 0);
    //     r.read(f, i);
    //     for(int j = 0; j < field_names.size(); j++)
    //         outs << right << setw(25) << r._record[j];
    //     outs << endl;
    // }
    // f.close();
}

ostream& operator <<(ostream& outs, Table print_me)
{
    outs << "Table name: " << print_me.table_name << ", records: " << print_me.lastRecno + 1 << endl << right << setw(25) << "record";
    for(int i = 0; i < print_me.field_names.size(); i++)
        outs << right << setw(25) << print_me.field_names[i];//print the field names
    outs << endl << endl;
    print_me.print_records(outs);//print out each record
    return outs;
}

//selects

Table Table::select_all()
{
    return select_all(field_names);
}

Table Table::select_all(const vectorstr& fieldNames)
{
    mmap recno_map = _table[0];//getting all recnos
    vectorlong all_recnos;
    // typename mmap::Iterator it;
    // for(it = recno_map.begin(); it != recno_map.end(); ++it)
    //     all_recnos += (*it).value_list;
    // quick_sort(all_recnos);//sort recnos
    for(int i = 0; i <= lastRecno; i++)
        all_recnos.push_back(i);
    // cout << all_recnos;
    return make_temp_table(fieldNames, all_recnos);
}

Table Table::select(const vectorstr& fieldNames, const string& field, const string& op, const string& key)
{
    f.close();
    open_fileRW(f, table_name + ".bin");
    //turn expression to infix
    vectorstr infix_expr = {field, op, key};
    //turn to postfix
    ShuntingYard sy(infix_expr);
    Queue<Token*> postfix = sy.postfix();
    //rpn this john
    RPN rpn(_field_map, _table, postfix);
    vectorlong recnos = rpn();//should give the good stuff!
    return make_temp_table(fieldNames, recnos);
}

Table Table::select(const vectorstr& fieldNames, const Queue<Token*> post)//take post fix
{
    f.close();
    open_fileRW(f, table_name + ".bin");
    RPN rpn(_field_map, _table, post);
    vectorlong recnos = rpn();
    return make_temp_table(fieldNames, recnos);
}

Table Table::select(const vectorstr& fieldNames, const vectorstr& expression)
{
    f.close();
    open_fileRW(f, table_name + ".bin");
    ShuntingYard sy(expression);//making postfix expression
    Queue<Token*> postfix = sy.postfix();
    RPN rpn(_field_map, _table, postfix);
    vectorlong recnos = rpn();
    return make_temp_table(fieldNames, recnos);
}

vectorlong Table::select_recnos()
{
    return select_mem;
}

vectorstr Table::get_field_names()
{
    return field_names;
}

Table Table::make_temp_table(const vectorstr& fieldNames, const vectorlong& recnos)
{
    string tempFileName = table_name + to_string(serial);
    Table tempTable(tempFileName, fieldNames);
    FileRecord r;
    vectorlong field_insert_order = get_insert_order(fieldNames);
    // cout << v.size() << endl;
    // cout << fieldNames << endl;
    f.close();
    open_fileRW(f, table_name + ".bin");
    // cout << recnos;
    for(int i = 0; i < recnos.size(); i++)//i is a recno
    {
        vectorstr tempVect;
        // cout << "READ: " << 
        r.read(f, recnos[i]);//reads record at that recno
        // cout << endl;
        for(int j = 0; j < field_insert_order.size(); j++)//now we need to push in record with only given number of fields
            tempVect.push_back(r._record[field_insert_order[j]]);
        // cout << tempVect;
        tempTable.insert_into(tempVect);
    }
    select_mem = recnos;//put this in memory variable
    return tempTable;
}

vectorlong Table::get_insert_order(const vectorstr& fieldNames)
{
    // cout << "Yuh\n";
    vectorlong orderVect;
    long index;
    for(int i = 0; i < fieldNames.size(); i++)
    {
        index = _field_map[fieldNames[i]];//gives you index in _table mmap for fieldname at index i
        orderVect.push_back(index);
    }
    return orderVect;
}
//gives the indexes in order of fieldNames given in vect