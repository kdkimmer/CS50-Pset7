#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    string s = GetString();
    //within in this loop we will interate over all the characters in string s
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        //within this loop we are checking to see if the ith character is a lowercase
        if (s[i] >= 'a' && s[i] <= 'z')
        {
            printf("%c", s[i] - ('a' - 'A'));
        }
        else
        {
            printf("%c", s[i]);
        }
        
    }
    printf("\n");
}

