#include <stdio.h>
#include <cs50.h>
#include <stdbool.h>

//iterative binary search implementation

bool binary_search(int value, int values[], int n)
{
    int beginning = 0;
    int ending = n - 1;
    
    //while length of list> 0
    while (ending >= beginning)
    {
        //look at the middle first
        int middle = (beginning - ending) / 2;
        if (values[middle] == value)
        {
            //if numberfound, return true
            return true;
        }
        //else if middle higher, search left
        else if (values[middle] > value)
        {
            ending = middle - 1;
        }
        //else if middle lower, search right
        else
        {
            beginning = middle + 1;
        }
    }
//return false
return false;

}
