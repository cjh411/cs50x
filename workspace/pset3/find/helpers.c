/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if(n < 0){
        return false;
    }else{
        int start = n / 2;
        int min;
        int max;
        if(values[start] == value){
            return true;
        }else if(values[start] < value){
            min = start +1;
            max = n;
        }else{
            min  = 0;
            max  = start;
        }
        
        for(int i = min; i < max;i++){
            if(values[i] == value){
                return true;
            }
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
   int mindex = 0;
   int min;
   for (int j = 0; j < n-1; j++){
       mindex = j;
       
       for (int i = j+1; i < n ; i++){
           if(values[i]<values[mindex]){
               mindex = i;
           }
       }
       min = values[mindex];
       values[mindex] = values[j];
       values[j] = min;
       
   }
    return;
}
