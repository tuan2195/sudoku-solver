//
//  sortHelper.h
//  Project3a
//
//  Created by Tuan Dao on 10/9/15.
//  Copyright (c) 2015 Tuan Dao. All rights reserved.
//

#ifndef Project3a_sortHelper_h
#define Project3a_sortHelper_h

// INSERTION SORT HELPER FUNCTIONS

// Simple insertion sort template for vectors
template <typename T> void insertionsorter(std::vector<T> &v, int size)
{
    int j;
    T temp;
    for (int i = 0; i < size; i++)
    {
        temp = v[i];
        for (j = i-1; j>=0 && v[j]>temp; j--)
            v[j+1] = v[j];
        v[j+1] = temp;
    }
}

// Interface
template <typename T> void insertionsort(std::vector<T> &v)
{
    insertionsorter<T>(v, (int)v.size());
}

// MERGESORT HELPER FUNCTIONS

// Merge function
template <typename T> void merge(std::vector<T> &v, int left, int mid, int right)
{
    int n1 = mid - left +1;
    int n2 = right - mid;
    std::vector<T> l, r;
    
    for (int i = 0; i < n1; ++i)
        l.push_back(v[left+i]);
    for (int i = 0; i < n2; ++i)
        r.push_back(v[mid+i+1]);
    
    int i = 0, j = 0, k = left;
    
    while (i<n1 && j<n2)
        if (l[i] < r[j])
            v[k++] = l[i++];
        else
            v[k++] = r[j++];
    
    while (i<n1)
        v[k++] = l[i++];
    while (j<n2)
        v[k++] = r[j++];
}

// Mergesort implement function
template <typename T> void mergesorter(std::vector<T> &v, int left, int right)
{
    if (left < right)
    {
        int mid = (left+right)/2;
        mergesorter<T>(v, left, mid);
        mergesorter<T>(v, mid+1, right);
        merge<T>(v, left, mid, right);
    }
}

// Interface
template <typename T> void mergesort(std::vector<T> &v)
{
    mergesorter<T>(v, 0, (int)v.size()-1);
}

// QUICKSORT HELPER FUNCTIONS

// Partition function
template <typename T> int partition(std::vector<T> &v, int p, int r)
{
    T pivot = v[r];
    T temp;
    int i = p-1;
    
    for (int j = p; j < r; ++j)
        if (v[j] < pivot)
        {
            i++;
            temp = v[i];
            v[i] = v[j];
            v[j] = temp;
        }
    
    i++;
    temp = v[i];
    v[i] = v[r];
    v[r] = temp;
    
    return i;
}

// Quicksort implement function
template <typename T> void quicksorter(std::vector<T> &v, int p, int r)
{
    if (p < r)
    {
        int q = partition(v, p, r);
        quicksorter(v, p, q-1);
        quicksorter(v, q+1, r);
    }
}

// Interface
template <typename T> void quicksort(std::vector<T> &v)
{
    quicksorter(v, 0, (int)v.size()-1);
}
/*
// HEAPSORT HELPER FUNCTION
template <typename T> void heapsort(std::vector<T> &v)
{
    heap<std::string> h;
    h.init(v);
    h.sort();
    int size = (int)v.size();
    for (int i = 0; i < size; i++) {
        v[i] = h.getItem(i);
    }
}
*/
#endif
