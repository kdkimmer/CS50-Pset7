#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char *argv[])

{
    // making sure user gave us a keyword
    if (argc != 2)
    {
        printf("Please give one keyword:\n");
        return 1;     
    }
    // Geting the keyword from user
    string k = argv[1];
    // loop so i can index keyword and know the length of k
    for (int i = 0, n = strlen(argv[1]); i < n; i++) 
    {
        // Checks for numbers
        if (!isalpha (k[i])) 
        {
            printf("Enter a Keyword:\n");
            return 1;
        }
    }
      
    // pharse from user to encrypt
    string p = GetString();
    int length = 0;
    length = strlen(p);
     
    // once you have both k and plaintext its time to encrypt
    int i = 0;
    int kcipher = 0;
        
    for (i = 0, kcipher = 0; i < length; i++, kcipher++)
    {   
        // kciper resets if p[i] is longer then keyword so it can be used again
        if (kcipher > (strlen(k)) - 1)
        {
            kcipher = 0;
        }
            
        // enter loop for upper p[i] and k[kcipher]
        if (p[i] >= 65 && p[i] <= 90)
        {
            if (k[kcipher] >= 65 && k[kcipher] <= 90)
            {
                int pcipher = (((p[i] - 65) + (k[kcipher] - 65)) % 26) + 65;
                printf("%c", pcipher);
            }
            else
            {
                int pcipher = (((p[i] - 65) + (k[kcipher] - 97)) % 26) + 65;
                printf("%c", pcipher);
            }
        }
        // enter loop for lower of p[i] and k[kcipher]
        else if (p[i] >= 97 && p[i] <= 122)
        {
            if (k[kcipher] >= 97 && p[i] <= 122)
            {
                int pcipher = ((( p[i] - 97) + (k[kcipher] - 97)) % 26) + 97;
                printf("%c", pcipher);
            }
            else 
            {
                int pcipher = ((( p[i] - 97) + (k[kcipher] - 65)) % 26) + 97;
                printf("%c", pcipher);
            }
        }
        // print all other p[i] characters like space but do not advance kcipher
        else
        {
            printf("%c", p[i]);
            kcipher--;
        }       
    }
    printf("\n");
    return 0;
}
    

