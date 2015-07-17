#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <time.h>

#define NUMBER 5

int main(void)
{
    //Ask user for 5 names 
    //#define on line 5 allows you to change the number of names 
    //So you could ask the user for 10 or ect.
    
    string names[NUMBER];
    for (int i = 0; i < NUMBER; i++)
    
    {
    printf("Enter name: %d\n", i +1);
    names[i] = GetString();
    }
    
    // randomly chose and print out one of the names
    
    srand(time(NULL));
    int name = rand() % NUMBER;
    printf("This is your random name: 
    %s\n", names[name]);




}
