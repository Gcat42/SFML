#include "file_record.h"

long FileRecord::write(fstream &outs)
{
        //r.write(f); //take the Record r and write it into file f
        //  and return the record number of this Record

        //write to the end of the file.
    outs.seekg(0, outs.end);//retrieves the current position of the
                                    //      file pointer
    long pos = outs.tellp();
        //pay attention to this:
    outs.write(&_record[0][0], sizeof(_record));
    recno = pos/sizeof(_record);
    return recno;  //record number
}

long FileRecord::read(fstream &ins, long recno)
{
    //returns the number of bytes read.
    //    r.read(f, 6);
    //    cout<<r<<endl;
    long pos= recno * sizeof(_record);
    ins.seekg(pos, ios_base::beg);
    long bytesRead = 0;
    //ins.read(&_record[0], sizeof(_record))
    
    ins.read(&_record[0][0], sizeof(_record));

    // for(int i = 0; i < ROWS; i++)
    // {
    //     ins.read(_record[i], MAX + 1);
    //     _record[i][ins.gcount()] = '\0';
    //     bytesRead += ins.gcount();
    // }
    //don't you want to mark the end of  the cstring with null?
    //_record[] => [zero'\0'trash trash trash trash]
    //don't need the null character, but for those of us with OCD and PTSD:
    // cout << "Bytes read: " << ins.gcount() << endl;
    return ins.gcount();
}

ostream& operator<<(ostream& outs,  const FileRecord& r)
{
    for(int i = 0; i < r.ROWS; i++)
        outs << right << setw(25) << r._record[i];
    outs << endl;
    return outs;
}

