#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)

//a string is a sequence of characters or an array of chars
//we can interate into a string by indexing into it by a new set of notations called square brackets[]
//we also added a line to this program for NULL either the string was to long or the user did not input anything and so we do not want
//the for loop to continue if s is NULL
{
    string s = GetString();
    if (s != NULL)
        
        for (int i = 0; i < strlen(s); i++)
        {
            printf("%c\n", s[i]);
        }
}
