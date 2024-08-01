#include "quick_sort.h"

void quick_sort(vectorlong& v)//for calling
{
    quick_sort(v, 0, v.size() - 1);
}

void quick_sort(vectorlong& v, int start, int end)
{
    int size = end - start + 1;//since both indexes are inclusive need to add 1 (index 1 and 2 has size of 2!)
    int midIndex;
    if(size < 2)
        return;
    partition(v, start, end, midIndex);
    quick_sort(v, start, midIndex - 1);//sort left side
    quick_sort(v, midIndex + 1, end);
}
//for the actual sorting

void partition(vectorlong& v, int start, int end, int& midIndex)
{
    int firstBiggest = get_first_biggest(v, start, end);//get index of first element greater than beginning
    int firstSmallest = get_first_smallest(v, start, end);//get index of first element < beg. (starting from end)
    while(firstBiggest < firstSmallest)//as long as the bigger was found in front of smaller, switch
    {
        swap(v, firstBiggest, firstSmallest);//swap them johns
        firstBiggest = get_first_biggest(v, firstBiggest, end);
        firstSmallest = get_first_smallest(v, start, firstSmallest);
    }
    swap(v, start, firstSmallest);
    midIndex = firstSmallest;
}

void swap(vectorlong& v, int a, int b)
{
    long holder = v[a];
    v[a] = v[b];
    v[b] = holder;
}

int get_first_biggest(vectorlong& v, int start, int end)
{
    int firstBiggest = start + 1;
    while((firstBiggest <= end) && (v[start] >= v[firstBiggest]))
        firstBiggest++;
    return firstBiggest;
}
//goes from start
int get_first_smallest(vectorlong& v, int start, int end)
{
    int firstSmallest = end;
    while((firstSmallest > start) && (v[start] <= v[firstSmallest]))
        firstSmallest--;
    return firstSmallest;
}
//goes from end