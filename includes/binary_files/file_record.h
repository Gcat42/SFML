#ifndef FILE_RECORD_H
#define FILE_RECORD_H

#include <iostream>
#include <iomanip>
#include <string.h>
#include <vector>
#include "utilities.h"

using namespace std;

class FileRecord{
public:
    //when you construct a FileRecord, it's either empty or it
    //  contains a word
    static const int ROWS = 20;
    static const int MAX = 100;
    char _record[ROWS][MAX+1]; //NULL char
    
    FileRecord()
    {
        for(int i = 0; i < ROWS; i++)
            _record[i][0] = '\0';
        recno = -1;
        //['\0'|  | G | a | r | b | a   |  g  |  e |    ]
    }

    FileRecord(vector<string> rows)
    {
        for(int i = 0; i < ROWS; i++)
            _record[i][0] = '\0';
        for(int i = 0; i < rows.size() && i < ROWS; i++)
        {
            strcpy(_record[i], rows[i].c_str());
            // cout << _record[i];
        }
            

    }
    
    // FileRecord(vector<string> s)
    // {
    //     for(int i = 0; i < ROWS; i++)
    //         _record[i][0] = '\0';
    //     for(int i = 0; i < s.size(); i++)
    //     {
    //         strncpy(_record[i], s[i].c_str(), MAX);
    //         // cout << _record[i];
    //     }
    // }

    long write(fstream& outs);              //returns the record number
    long read(fstream& ins, long recno);    //returns the number of bytes
                                            //      read = MAX, or zero if
                                            //      read passed the end of file


    friend ostream& operator<<(ostream& outs, const FileRecord& r);


private:
    int recno;
    
};

#endif