#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED
#include <iostream>
#include <vector>
#include "Integer.h"
using namespace std;

int GetDigit(Integer &x, int digit)     //return the number of x in digit-th location
{
    int size = x.GetSize();
    if(digit > size)
        return 0;
    else
        return x.GetOne(size-digit);
}

void MSD(vector<Integer> &arr, int start, int end, int digit)  //current digit-th
{
    const int radix = 10;   //0~10 bucket
    int cnt[radix], i, j;
    // 10 buckets
    for(i=0; i<radix; i++)
    {
        cnt[i] = 0;
    }
    Integer *bucket = new Integer[end-start+1];
    //calculate each bucket's number
    for(i=start; i<=end; i++)
    {
        cnt[GetDigit(arr[i], digit)]++;
    }
    //calculate bucket's edge index
    for(i=1; i<radix; i++)
    {
        cnt[i] = cnt[i]+cnt[i-1];
    }
    for(i=end; i>=start; i--)
    {
        j = GetDigit(arr[i], digit);
        bucket[cnt[j]-1] = arr[i];
        cnt[j]--;
    }
    //copy bucket to array.
    j = 0;
    for(i=start; i<=end; i++)
    {
        arr[i] = bucket[j++];
    }
    delete(bucket);
    //iteration in each bucket.
    for(i=0; i<radix; i++)
    {
        int p1, p2;
        p1 = start+cnt[i];
        if(i==radix-1)
            p2 = end-start;
        else
            p2 = start+cnt[i+1]-1;
        if(p1<p2 && digit>1)
        {
            MSD(arr, p1, p2, digit-1);
        }
    }
}

void LSD_(vector<Integer> &arr, int start, int end, int digit)  //current digit-th
{
    const int radix = 10;   //0~10 bucket
    int cnt[radix], i, j;
    // 10 buckets
    for(i=0; i<radix; i++)
    {
        cnt[i] = 0;
    }
    Integer *bucket = new Integer[end-start+1];
    //calculate each bucket's number
    for(i=start; i<=end; i++)
    {
        cnt[GetDigit(arr[i], digit)]++;
    }
    //calculate bucket's edge index
    for(i=1; i<radix; i++)
    {
        cnt[i] = cnt[i]+cnt[i-1];
    }
    for(i=end; i>=start; i--)
    {
        j = GetDigit(arr[i], digit);
        bucket[cnt[j]-1] = arr[i];
        cnt[j]--;
    }
    //copy bucket to array.
    j = 0;
    for(i=start; i<=end; i++)
    {
        arr[i] = bucket[j++];
    }
    delete(bucket);
}

void LSD(vector<Integer> &arr, int start, int end, int digit, int max_digit)
{
    while(digit <= max_digit)
    {
        LSD_(arr, start, end, digit);
        digit++;
    }
}

#endif // SORT_H_INCLUDED
