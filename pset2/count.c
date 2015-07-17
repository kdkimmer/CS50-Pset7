#include <stdio.h>
#include <cs50.h>

int main(void)
{
//create an array with the int 1 through 5
//print out each int on a new line

int ages[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++)
    {
    
        printf("%i\n", ages[i]);
    }
}
