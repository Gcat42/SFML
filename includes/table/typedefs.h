#ifndef TYPEDEFS_H
#define TYPEDEFS_H
#include <string.h>
#include <vector>
#include "../bplustree/multimap.h"
#include "../bplustree/map.h"
#include "../binary_files/file_record.h"

using namespace std;

typedef vector<string> vectorstr;
typedef Map<string, long> regMap;
typedef MMap<string, long> mmap;
typedef MMap<string, string> mmap_ss;
typedef vector<mmap> vectormmap;
typedef Map<string, string> map_ss;

typedef vector<FileRecord> vectorfilerec;
typedef vector<long> vectorlong;

#endif