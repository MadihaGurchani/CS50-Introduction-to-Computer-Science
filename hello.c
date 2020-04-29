#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Prompting user for name
    string name = get_string("Please enter your name.");
    //Printing hello, so-and-so
    printf("hello, %s\n", name);
}