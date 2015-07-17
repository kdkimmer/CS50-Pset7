#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])

{

    // checking the argument to make sure there are 2 if not prompt user
    if (argc != 2)
    {
        printf("Please enter an integer!:  \n");
        return 1;
    }

    // convert string to an int
    int k = atoi(argv[1]);
    
    // checking to make sure k is a non negative int 
    if (k < 0)         
    { 
        printf("Please enter an integer!:  \n");
        return 1;
    }
    
    if (k > 26)
    {
        k = k % 26;
    }
    
    // plain text- string to be encrypted 
    string p = GetString();
    int length = 0;
    length = strlen(p);
      
    // once you have both k and plaintext its time to rotate to encrypt
    int cipher = 0;
    for (int i = 0; i < length; i++)
    {
        // enter loop for upper and lower
        if (p[i] >= 65 && p[i] <= 90)
        {
            cipher = ((26 - (91 - p[i]) + k) % 26);
            p[i] = cipher + 'A';
            printf("%c", p[i]);
        }
    
        else if (p[i] >= 97 && p[i] <= 122)
        {
            cipher = ((26 - (123 - p[i]) + k) % 26);
            p[i] = cipher + 'a';
            printf("%c", p[i]);
        }
    
        else if (isprint(p[i]))
        {
            // prints as long as it is a printable character
            // not a control character
            printf("%c", p[i]);
        }   
            
    }
    printf("\n");
    return 0;
}
