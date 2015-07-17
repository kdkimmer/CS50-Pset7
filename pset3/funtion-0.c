#include <stdio.h>
#include <cs50.h>
//this is one way to do it but we like it better if the new function we created was placed when we would need it instead of about 
//int main(void) see next example
void PrintName(string name)
{
    printf("Hello, %s!\n", name);
}
int main(void)
{
    printf("Your name: ");
    string s =GetString();
    PrintName(s);
}
