#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
//ask user for a string

    printf("Hello mate! Give me a word to print:  \n");
    string s = GetString();
    
//print out each letter on a new line
    
    for (int i = 0, length = strlen(s); i < length; i++)
    {
        printf("%c\n", s[i]);    
    }
       
}
